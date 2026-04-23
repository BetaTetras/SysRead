#include "StoRead.h"
#include "../Tools/Tools.h"

unsigned long long getStoTotal(String PATH){
    struct statvfs buf;
    statvfs(PATH, &buf);

    return buf.f_blocks * buf.f_frsize;
}

unsigned long long getStoAvailable(String PATH){
    struct statvfs buf;
    statvfs(PATH, &buf);

    return buf.f_bfree * buf.f_frsize;
}

unsigned long long getUse(String PATH){
    return getStoTotal(PATH) - getStoAvailable(PATH);
}

stoinfo initStoinfo(String PATH, sizeType Type){
    stoinfo s;
    s.PATH = PATH;

    unsigned long long total = getStoTotal(PATH);
    unsigned long long use   = total - getStoAvailable(PATH);

    switch(Type){
        case B:
            s.StoTotal = (double) total;
            s.StoUse   = (double) use;
            s.Type = B;
            break;
        case kB:
            s.StoTotal = (double) total / 1024.0;
            s.StoUse   = (double) use   / 1024.0;
            s.Type = kB;
            break;
        case mB:
            s.StoTotal = (double) total / (1024.0 * 1024.0);
            s.StoUse   = (double) use   / (1024.0 * 1024.0);
            s.Type = mB;
            break;
        case gB:
            s.StoTotal = (double) total / (1024.0 * 1024.0 * 1024.0);
            s.StoUse   = (double) use   / (1024.0 * 1024.0 * 1024.0);
            s.Type = gB;
            break;
        case tB:
            s.StoTotal = (double) total / (1024.0 * 1024.0 * 1024.0 * 1024.0);
            s.StoUse   = (double) use   / (1024.0 * 1024.0 * 1024.0 * 1024.0);
            s.Type = tB;
            break;
        default:
            s.StoTotal = 0.0f;
            s.StoUse   = 0.0f;
            s.Type     = B;
            break;
    }

    return s;
}




