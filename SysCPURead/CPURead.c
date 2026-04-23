#include "CPURead.h"
#include "../Tools/Tools.h"

TimeCPU initTimeCpu(){
    TimeCPU t;

    FILE *cpuStat = fopen("/proc/stat","r");
    if(!cpuStat) {
        perror("fopen");
        exit(1);
    }

    // cpu  user  nice  system  idle  iowait  irq  softirq  steal  guest  guest_nice
    fscanf(cpuStat,"cpu  %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
                    &t.user,&t.nice,&t.system,&t.idle,
                    &t.iowait,&t.irq,&t.softirq,&t.steal,
                    &t.guest,&t.guest_nice);

    fclose(cpuStat);
    return t;
}

float loadCPU(){
    TimeCPU t1 = initTimeCpu();
    sleep(1);
    TimeCPU t2 = initTimeCpu();

    unsigned long long idle1 = t1.idle + t1.iowait;
    unsigned long long idle2 = t2.idle + t2.iowait;

    unsigned long long nonIdle1 = t1.user + t1.nice + t1.system +
                             t1.irq + t1.softirq + t1.steal;

    unsigned long long nonIdle2 = t2.user + t2.nice + t2.system +
                             t2.irq + t2.softirq + t2.steal;

    unsigned long long total1 = idle1 + nonIdle1;
    unsigned long long total2 = idle2 + nonIdle2;

    unsigned long long totalDelta = total2 - total1;
    unsigned long long idleDelta = idle2 - idle1;

    float CPU_Percentage = (float)(totalDelta - idleDelta) / totalDelta * 100.0f;
    return CPU_Percentage;
}


float tempCPU(){
    FILE *temp = fopen("/sys/class/thermal/thermal_zone0/temp","r");
    String ligne = (String)calloc(10,sizeof(char));
    fgets(ligne,10,temp);
    fclose(temp);
    float result = (float)(StringToInt(ligne) / 1000.0f);
    free(ligne);
    return result;
}


