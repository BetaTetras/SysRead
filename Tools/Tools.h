#ifndef TOOLS_H
#define TOOLS_H

typedef char* String;

typedef enum{
    B,
    kB,
    mB,
    gB,
    tB
}sizeType;

int _strchr(String Input,char Element);
String strbcpy(String str,int Start,int End);
int StringToInt(String str);
long StringToLong(String str);
long long int StringToLongLong(String str);
char** explode(char* str, int* size);
double byteConverter(long long int byte, sizeType type);

#endif
