#include "rcc.hpp"



void CRCC::APB1Cmd(APB1 apb1, FUNCSTATUS statu) {
    if(statu==ENABLE)
        BitSet(APB1ENR, apb1);
    else
        BitReset(APB1ENR, apb1);
}



void CRCC::APB2Cmd(APB2 apb2, FUNCSTATUS statu) {
    if (statu == ENABLE)
        BitSet(APB2ENR,apb2);
    else
        BitReset(APB2ENR, apb2);
}

void CRCC::APB1Reset(APB1 apb1) {
    BitSet(APB1RSTR, apb1);
    BitReset(APB1RSTR, apb1);
}

void CRCC::APB2Reset(APB2 apb2) {
    BitSet(APB2RSTR, apb2);
    BitReset(APB2RSTR, apb2);
}



