#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "NetRead.h"
#include "../Tools/Tools.h"

netinfo initNetinfo(){
    FILE* f = fopen("/proc/net/dev", "r");
    netinfo net;
    if(f == NULL){
        net.interfaces = NULL;
        net.count = 0;
        return net;
    }

    net.interfaces = (interface*)calloc(1, sizeof(interface));
    char* line = (char*)calloc(256,sizeof(char));
    char** lsOfString = NULL;
    int NbOfStr = 0;
    net.count = 0;

    fgets(line, 256, f);
    fgets(line, 256, f);
    
    while(fgets(line, 256, f) != NULL){
        lsOfString = explode(line, &NbOfStr, lsOfString, NbOfStr);  
        net.count++ ;
        net.interfaces = (interface*)realloc(net.interfaces, net.count * sizeof(interface));

        interface inter;

        inter.name = (char*)calloc(strlen(lsOfString[0])+1, sizeof(char));
        strncpy(inter.name, lsOfString[0], strlen(lsOfString[0]) - 1);
        inter.name[strlen(lsOfString[0]) - 1] = '\0';
        inter.byte_in = StringToLongLong(lsOfString[1]);
        inter.packets_in = StringToLongLong(lsOfString[2]);
        inter.errs_in = StringToLongLong(lsOfString[3]);
        inter.drop_in = StringToLongLong(lsOfString[4]);

        inter.byte_out = StringToLongLong(lsOfString[9]);
        inter.packets_out = StringToLongLong(lsOfString[10]);
        inter.errs_out = StringToLongLong(lsOfString[11]);
        inter.drop_out = StringToLongLong(lsOfString[12]);
        net.interfaces[net.count - 1] = inter;

    }
    for(int j = 0; j < NbOfStr; j++){
        free(lsOfString[j]);
    } 
    free(lsOfString);
    free(line);
    fclose(f);
    
    long long int tot_in = 0;
    long long int tot_out = 0;
    for(int i=0;i<net.count;i++){
        tot_in += net.interfaces[i].byte_in;
        tot_out += net.interfaces[i].byte_out;
    }

    net.byte_in_tot = tot_in;
    net.byte_out_tot = tot_out;

    return net;
}

void freeNetinfo(netinfo net){
    for(int i = 0; i < net.count; i++){
        free(net.interfaces[i].name);
    }
    free(net.interfaces);
}
