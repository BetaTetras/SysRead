#include "MemRead.h"
#include "../Tools/Tools.h"

int getMemTotal(){
    FILE *meminfo = fopen("/proc/meminfo","r");
    String line = (String)calloc(30,sizeof(char));
    String stringValue = (String)calloc(8,sizeof(char));
    int intValue;

        while(fgets(line,30,meminfo) != NULL){
        String tmp1 = strbcpy(line,0,7);
        if(strcmp(tmp1,"MemTotal") == 0){
            String tmp2 = strbcpy(line,17,23);
            strcpy(stringValue, tmp2);
            free(tmp2);
        }
        free(tmp1);
    }
    intValue = StringToInt(stringValue);
    fclose(meminfo);
    free(line);
    free(stringValue);
    return intValue;
}

int getMemAvailable(){
    FILE *meminfo = fopen("/proc/meminfo","r");
    String line = (String)calloc(30,sizeof(char));
    String stringValue = (String)calloc(8,sizeof(char));
    int intValue;

    while(fgets(line,30,meminfo) != NULL){
        String tmp1 = strbcpy(line,0,11);
        if(strcmp(tmp1,"MemAvailable") == 0){
            String tmp2 = strbcpy(line,17,23);
            strcpy(stringValue, tmp2);
            free(tmp2);
        }
        free(tmp1);
    }
    intValue = StringToInt(stringValue);
    fclose(meminfo);
    free(line);
    free(stringValue);
    return intValue;
}

int getMemUse(){
    return getMemTotal() - getMemAvailable();
}

meminfo initMeminfo(sizeType type){
    meminfo m;

    int total = getMemTotal();
    int use = total - getMemAvailable();

    if(type == kB){
        m.MemTotal = (float) total;
        m.MemUse = (float) use;
        m.Type = kB;
    } else if(type == mB){
        m.MemTotal = (float) total / 1024.0f;
        m.MemUse = (float) use / 1024.0f;
        m.Type = mB;
    } else if(type == gB){
        m.MemTotal = (float) total / (1024.0f * 1024.0f);
        m.MemUse = (float) use / (1024.0f * 1024.0f);
        m.Type = gB;
    } else if(type == tB){
        m.MemTotal = (float) total / (1024.0f * 1024.0f * 1024.0f);
        m.MemUse = (float) use / (1024.0f * 1024.0f * 1024.0f);
        m.Type = tB;
    } else {
        m.MemTotal = 0.0f;
        m.MemUse = 0.0f;
        m.Type = kB;
    }

    return m;
}


