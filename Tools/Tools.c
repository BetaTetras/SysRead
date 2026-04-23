#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "Tools.h"

typedef char* String;

String strbcpy(String str,int Start,int End){
    String res = (String)calloc(End - Start +1,sizeof(char));

    int x =0;
    for(int i=0;i<(int)strlen(str);i++){
        if(i>= Start && i<= End){
            res[x] = str[i];
            x++;
        }
    }
    res[x] = '\0';

    return res;
}

int StringToInt(String str){
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

long long int StringToLongLong(String str){
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

char** explode(char* str, int* size){
    int len = strlen(str);
    char** lsOfElement = (char**)calloc(1,sizeof(char*));
    int _size = 0;

    int index = 0;
    for(int i=0;i<len;i++){
        if(str[i] == ' '){
            continue;
        }else{
        _size++;
        lsOfElement = realloc(lsOfElement,_size * sizeof(char*));
        lsOfElement[_size - 1] = (char*)calloc(256, sizeof(char));
        index = 0;
            while(str[i] != ' ' && str[i] != '\0'){
                lsOfElement[_size - 1][index] = str[i];
                index++;
                i++;
            }
        }

    }
    *size = _size;
    return lsOfElement;
}
