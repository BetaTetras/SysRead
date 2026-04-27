#ifndef MEMREAD_H
#define MEMREAD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Tools/Tools.h"

typedef struct{
    double MemTotal;
    double MemUse;
    double MemAvail;
    sizeType Type;
}meminfo;

meminfo initMeminfo(sizeType type);

#endif