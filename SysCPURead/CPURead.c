#include "CPURead.h"
#include "../Tools/Tools.h"

TimeCPU TimeCpu(){
    TimeCPU t = {0};

    FILE *cpuStat = fopen("/proc/stat","r");
    if(!cpuStat) {
        return t;
    }

    // cpu  user  nice  system  idle  iowait  irq  softirq  steal  guest  guest_nice
    fscanf(cpuStat,"cpu  %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
                    &t.user,&t.nice,&t.system,&t.idle,
                    &t.iowait,&t.irq,&t.softirq,&t.steal,
                    &t.guest,&t.guest_nice);

    fclose(cpuStat);
    return t;
}

cpuinfo initCPUinfo(){
    cpuinfo cpu;

    FILE *temp = fopen("/sys/class/thermal/thermal_zone0/temp","r");
    if(temp == NULL){
        cpu.loadCPU = 0.0;
        cpu.tempCPU = 0.0;
        return cpu;
    }   
    String ligne = (String)calloc(10,sizeof(char));
    fgets(ligne,10,temp);
    fclose(temp);
    cpu.tempCPU = (float)(StringToLong(ligne) / 1000.0f);

    TimeCPU t1 = TimeCpu();
    sleep(1);
    TimeCPU t2 = TimeCpu();

    if(t1.user == 0 || t2.user == 0){
        free(ligne); 
        cpu.loadCPU = 0.0;
        cpu.tempCPU = 0.0;
        return cpu;
    }

    unsigned long long idle1 = t1.idle + t1.iowait;
    unsigned long long idle2 = t2.idle + t2.iowait;

    unsigned long long total1 = idle1 + t1.user + t1.nice + t1.system + t1.irq + t1.softirq + t1.steal;
    unsigned long long total2 = idle2 + t2.user + t2.nice + t2.system + t2.irq + t2.softirq + t2.steal;

    unsigned long long totalDelta = total2 - total1;
    unsigned long long idleDelta = idle2 - idle1;

    if(totalDelta == 0){
        cpu.loadCPU = 0.0;
    } else {
        cpu.loadCPU = (float)(totalDelta - idleDelta) / totalDelta * 100.0f;
    }

    free(ligne);
    return cpu;
}




