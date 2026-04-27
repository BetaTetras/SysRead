# SysRead — Bibliothèque de monitoring système Linux

Bibliothèque C pour lire les informations système en temps réel : CPU, RAM, réseau et stockage, directement depuis le noyau Linux (`/proc`, `/sys`).

---

## Structure du projet

```
.
├── Tools/
│   ├── Tools.h
│   └── Tools.c         # Utilitaires : explode, byteConverter, StringTo*
├── CPURead/
│   ├── CPURead.h
│   └── CPURead.c       # Température et charge CPU
├── MemRead/
│   ├── MemRead.h
│   └── MemRead.c       # Mémoire totale, utilisée, disponible
├── NetRead/
│   ├── NetRead.h
│   └── NetRead.c       # Statistiques réseau par interface
└── StoRead/
    ├── StoRead.h
    └── StoRead.c       # Espace disque total, utilisé, disponible
```

---

## Types communs

### `sizeType`
Unité de conversion pour les tailles :

| Valeur | Description |
|--------|-------------|
| `B`    | Octets      |
| `kB`   | Kilooctets  |
| `mB`   | Mégaoctets  |
| `gB`   | Gigaoctets  |
| `tB`   | Téraoctets  |

---

## Modules

### CPU — `CPURead.h`

Lit `/proc/stat` et `/sys/class/thermal/thermal_zone0/temp`.

#### Structures

```c
typedef struct {
    unsigned long long user, nice, system, idle;
    unsigned long long iowait, irq, softirq, steal;
    unsigned long long guest, guest_nice;
} TimeCPU;

typedef struct {
    float tempCPU;   // Température en °C
    float loadCPU;   // Charge en %
} cpuinfo;
```

#### Fonctions

```c
cpuinfo initCPUinfo();
```
Retourne la température et la charge CPU. Effectue deux lectures de `/proc/stat` avec `sleep(1)` entre les deux pour calculer le delta.

> ⚠️ Bloque le thread appelant pendant **1 seconde**.

```c
TimeCPU TimeCpu();
```
Retourne un snapshot brut des compteurs CPU depuis `/proc/stat`.

#### Exemple

```c
cpuinfo cpu = initCPUinfo();
printf("Température : %.1f°C\n", cpu.tempCPU);
printf("Charge      : %.1f%%\n", cpu.loadCPU);
```

---

### RAM — `MemRead.h`

Lit `/proc/meminfo`.

#### Structure

```c
typedef struct {
    double MemTotal;   // Mémoire totale
    double MemUse;     // Mémoire utilisée
    double MemAvail;   // Mémoire disponible
    sizeType Type;     // Unité utilisée
} meminfo;
```

#### Fonction

```c
meminfo initMeminfo(sizeType type);
```
Retourne `-1.0` sur tous les champs en cas d'erreur de lecture.

#### Exemple

```c
meminfo mem = initMeminfo(mB);
printf("Total     : %.1f MB\n", mem.MemTotal);
printf("Utilisée  : %.1f MB\n", mem.MemUse);
printf("Disponible: %.1f MB\n", mem.MemAvail);
```

---

### Réseau — `NetRead.h`

Lit `/proc/net/dev`.

#### Structures

```c
typedef struct {
    char* name;                          // Nom de l'interface (ex: "eth0")
    long long int byte_in, packets_in;
    long long int errs_in, drop_in;
    long long int byte_out, packets_out;
    long long int errs_out, drop_out;
} interface;

typedef struct {
    interface* interfaces;               // Tableau de toutes les interfaces
    int count;                           // Nombre d'interfaces
    long long int byte_in_tot;           // Total octets reçus
    long long int byte_out_tot;          // Total octets envoyés
} netinfo;
```

> Les valeurs sont des **compteurs cumulés** depuis le démarrage, en octets. Pour obtenir un débit, effectuer deux lectures et calculer le delta.

#### Fonctions

```c
netinfo initNetinfo();
void freeNetinfo(netinfo net);
```

> ⚠️ Toujours appeler `freeNetinfo()` après utilisation pour libérer la mémoire.

#### Exemple

```c
netinfo net = initNetinfo();
for (int i = 0; i < net.count; i++) {
    printf("%s — reçu: %lld B, envoyé: %lld B\n",
        net.interfaces[i].name,
        net.interfaces[i].byte_in,
        net.interfaces[i].byte_out);
}
freeNetinfo(net);
```

---

### Stockage — `StoRead.h`

Utilise `statvfs()` sur le chemin fourni.

#### Structure

```c
typedef struct {
    double StoTotal;   // Espace total
    double StoUse;     // Espace utilisé
    double StoAvail;   // Espace libre (incluant réserve root)
    String PATH;       // Chemin analysé
    sizeType Type;     // Unité utilisée
} stoinfo;
```

#### Fonction

```c
stoinfo initStoinfo(String PATH, sizeType Type);
```
Retourne `-1.0` sur tous les champs si `PATH` est `NULL` ou si `statvfs` échoue.

> `StoAvail` utilise `f_bfree` (espace physiquement libre, réserve root incluse).

#### Exemple

```c
stoinfo sto = initStoinfo("/", gB);
printf("Total     : %.2f GB\n", sto.StoTotal);
printf("Utilisé   : %.2f GB\n", sto.StoUse);
printf("Disponible: %.2f GB\n", sto.StoAvail);
```

---

## Utilitaires — `Tools.h`

### Conversion

```c
double byteConverter(long long int byte, sizeType type);
```
Convertit un nombre d'octets dans l'unité demandée.

### Parsing de chaînes

```c
int    StringToInt(String str);
long   StringToLong(String str);
long long int StringToLongLong(String str);
String strbcpy(String str, int Start, int End);
```

### Tokenisation

```c
char** explode(char* str, int* size, char** prev, int prevSize);
```
Découpe `str` par espaces. Si `prev` est non-`NULL`, libère l'ancien tableau avant d'allouer le nouveau.

> Toujours libérer le dernier résultat manuellement :
> ```c
> for (int i = 0; i < size; i++) free(tokens[i]);
> free(tokens);
> ```

---

## Compilation

```bash
gcc -o main main.c Tools/Tools.c CPURead/CPURead.c MemRead/MemRead.c NetRead/NetRead.c StoRead/StoRead.c
```

---

## Compatibilité

- Linux uniquement (dépend de `/proc` et `/sys`)
- Testé sur noyau 5.x+
- Aucune dépendance externe

## Credits

Conçue et développée par BetaTetras.
Corrections de code, résolution de fuites mémoire et rédaction du README par Claude.