#include "StoRead.h"
#include "../Tools/Tools.h"


stoinfo initStoinfo(String PATH, sizeType Type){
    stoinfo s;

    if(PATH == NULL){
        s.StoTotal = -1.0;
        s.StoUse   = -1.0;
        s.StoAvail = -1.0;
        s.Type     = B;
        return s;
    }

    s.PATH = PATH;

    struct statvfs buf;
    if(statvfs(PATH, &buf) != 0){
        s.StoTotal = -1.0;
        s.StoUse   = -1.0;
        s.StoAvail = -1.0;
        s.Type     = B;
        return s;
    }

    unsigned long long total     = buf.f_blocks * buf.f_frsize;
    unsigned long long available = buf.f_bfree * buf.f_frsize;
    unsigned long long use       = total - available;

    s.StoTotal = byteConverter(total,     Type);
    s.StoUse   = byteConverter(use,       Type);
    s.StoAvail = byteConverter(available, Type);
    s.Type     = Type;

    return s;
}




