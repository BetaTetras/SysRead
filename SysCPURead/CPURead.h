#ifndef CPUREAD_H
#define CPUREAD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../Tools/Tools.h"

typedef struct {
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal;
    unsigned long long guest;
    unsigned long long guest_nice;
} TimeCPU;

typedef struct{
    float tempCPU;
    float loadCPU;
}cpuinfo;

// Initialise la structure en lisant /proc/stat
TimeCPU TimeCpu();

cpuinfo initCPUinfo();

#endif
