#ifndef MEMREAD_H
#define MEMREAD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Tools/Tools.h"

typedef struct{
    float MemTotal;
    float MemUse;
    sizeType Type;
}meminfo;

int getMemTotal();
int getMemAvailable();
int getMemUse();
meminfo initMeminfo(sizeType type);

#endif