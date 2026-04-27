#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "Tools.h"

typedef char* String;

String strbcpy(String str, int Start, int End){
    if(str == NULL || Start < 0 || End < Start){
        return NULL;
    }

    int len = strlen(str);
    String res = (String)calloc(End - Start + 2, sizeof(char));

    int x = 0;
    for(int i = Start; i <= End && i < len; i++){
        res[x++] = str[i];
    }
    res[x] = '\0';

    return res;
}

int StringToInt(String str){
    if(str == NULL){
        return 0;
    }
    int res = 0;
    int boolNeg = 0;
    int i = 0;
    int len = strlen(str);


    if(str[len-1] == '\n'){
        len--;
    } 

    if(str[0] == '-') {
        boolNeg = 1;
        i++;
    }

    for(; i < len; i++){
        if(str[i] < '0' || str[i] > '9') return 0; // caractère invalide
        res = res * 10 + (str[i] - '0');
    }

    return boolNeg ? -res : res;
}

long StringToLong(String str){
    if(str == NULL){
        return 0;
    }

    long res = 0;
    int boolNeg = 0;
    int i = 0;

    int len = strlen(str);
    if(len == 0){
        return 0;
    }

    if(str[len-1] == '\n'){
        len--;
    } 

    if(str[0] == '-') {
        boolNeg = 1;
        i++;
    }

    for(; i < len; i++){
        if(str[i] < '0' || str[i] > '9') return 0;
        res = res * 10 + (str[i] - '0');
    }

    return boolNeg ? -res : res;
}

long long int StringToLongLong(String str){
    if(str == NULL){
        return 0;
    }
    long long int res = 0;
    int boolNeg = 0;
    int i = 0;
    int len = strlen(str);

    if(str[len-1] == '\n') len--;

    if(str[0] == '-') {
        boolNeg = 1;
        i++;
    }

    for(; i < len; i++){
        if(str[i] < '0' || str[i] > '9') return 0;
        res = res * 10 + (str[i] - '0');
    }

    return boolNeg ? -res : res;
}


int _strchr(String Input,char Element){
    for(int i=0;i<(int)strlen(Input);i++){
        if(Input[i] == Element){
            return i;
        }
    }
    return -1;
}

char** explode(char* str, int* size, char** prev, int prevSize){
    if(str == NULL){
        return NULL;
    }

    if(prev != NULL){
        for(int i = 0; i < prevSize; i++) free(prev[i]);
        free(prev);
    }

    int len = strlen(str);
    char** lsOfElement = (char**)calloc(1, sizeof(char*));
    int _size = 0;

    for(int i = 0; i < len; i++){
        if(str[i] == ' ') continue;

        _size++;
        lsOfElement = realloc(lsOfElement, _size * sizeof(char*));
        lsOfElement[_size - 1] = (char*)calloc(256, sizeof(char));

        int index = 0;
        while(str[i] != ' ' && str[i] != '\0'){
            lsOfElement[_size - 1][index] = str[i];
            index++;
            i++;
        }
    }

    *size = _size;
    return lsOfElement;
}

double byteConverter(long long int byte, sizeType type){
    switch(type){
        case B:  return (double)byte;
        case kB: return (double)byte / 1024.0;
        case mB: return (double)byte / (1024.0 * 1024.0);
        case gB: return (double)byte / (1024.0 * 1024.0 * 1024.0);
        case tB: return (double)byte / (1024.0 * 1024.0 * 1024.0 * 1024.0);
        default: return (double)byte;
    }
}