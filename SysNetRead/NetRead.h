#ifndef NETREAD_H
#define NETREAD_H

#include "../Tools/Tools.h"

typedef struct{
    char* name;
    long long int byte_in;
    long long int byte_out;

    long int packets_in;
    long int packets_out;

    long errs_in;
    long errs_out;

    long drop_in;
    long drop_out;
}interface;

typedef struct{
    long long int byte_in_tot;
    long long int byte_out_tot;
    int count;
    interface* interfaces;
}netinfo;

netinfo initNetinfo();
double byteConverter(long long int byte, sizeType type);
void freeNetinfo(netinfo net);

#endif
