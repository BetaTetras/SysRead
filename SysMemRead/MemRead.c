#include "MemRead.h"
#include "../Tools/Tools.h"


meminfo initMeminfo(sizeType type){
    meminfo m;
    long total      = 0;
    long available  = 0; 
    long use        = 0;

    FILE *meminfo = fopen("/proc/meminfo","r");
    if(meminfo == NULL){
        m.MemTotal = -1.0;
        m.MemUse   = -1.0;
        m.MemAvail = -1.0;
        m.Type     = B;
        return m;
    }

    char* line = (char*)calloc(256,sizeof(char));
    char** lsOfElement = NULL;
    int nbOfElement = 0;
    while(fgets(line, 256, meminfo) != NULL){
        lsOfElement = explode(line,&nbOfElement,lsOfElement,nbOfElement);
        if(strcmp(lsOfElement[0],"MemAvailable:") == 0){
            available = StringToLong(lsOfElement[1]);
        }else if(strcmp(lsOfElement[0],"MemTotal:") == 0){
            total = StringToLong(lsOfElement[1]);
        }
        if(available > 0 && total > 0){
            break;
        }
    }

    use = total - available;

    m.MemTotal = byteConverter(total,type);
    m.MemUse   = byteConverter(use,type);
    m.MemAvail = byteConverter(available,type);
    m.Type     = type;

    fclose(meminfo);
    
    for(int i = 0;i<nbOfElement;i++){
        free(lsOfElement[i]);
    }
    free(lsOfElement);
    free(line);
    return m;
}


