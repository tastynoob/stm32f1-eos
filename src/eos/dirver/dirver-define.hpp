#pragma once


#include"defing.hpp"



#define __IO volatile
#define __IM volatile const     
#define __OM volatile            
#define __IOM volatile



#define call(f) f()


#define BitSet(num, n) ((num) |= 1 << (n))
#define BitReset(num, n) ((num) &= ~(1 << (n)))
#define BitGet(num, n) (((num) & (1 << n)) != 0)

enum FUNCSTATUS {
    DISABLE,
    ENABLE,
};


enum voltage {
    LOW,
    HIGH
};