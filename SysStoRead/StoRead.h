#ifndef STOREAD_H
#define STOREAD_H

#include <stdio.h>
#include <sys/statvfs.h>
#include "../Tools/Tools.h"   // Pour String et sizeType

// Structure contenant les infos de stockage
typedef struct {
    String PATH;      // Chemin de la partition
    double StoTotal;  // Taille totale
    double StoUse;    // Taille utilisée
    double StoAvail;  // Taille libre
    sizeType Type;    // Unité utilisée (B, kB, mB, gB, tB)
} stoinfo;


// Initialisation de la structure stoinfo
stoinfo initStoinfo(String PATH, sizeType Type);

#endif
