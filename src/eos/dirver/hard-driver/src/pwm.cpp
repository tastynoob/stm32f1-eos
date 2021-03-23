#include "pwm.hpp"
#include "rcc.hpp"
#include "gpio.hpp"
#include "math.h"


CPWM::CPWM(CTIM& tim) {
    this->tim = &tim;
    rcc.APB2Cmd(_AFIO, ENABLE);
}

//有问题
void CPWM::Config(uint8 remapmod, bool oc1, bool oc2, bool oc3, bool oc4) {
    switch ((int)this->tim) {
        //默认：1.pa0,2.pa1,3.pa2,4.pa3
        case TIM2_BASE:
            pa.ClockOn();
            if (oc1) {
                pa.PinConfig(0, AF_PP, _50MHz);
            }
            if (oc2) {
                pa.PinConfig(1, AF_PP, _50MHz);
            }
            if (oc3) {
                pa.PinConfig(2, AF_PP, _50MHz);
            }
            if (oc4) {
                pa.PinConfig(3, AF_PP, _50MHz);
            }
            break;
            //pa6,pa7,pb0,pb1
        case TIM3_BASE:
            pa.ClockOn();
            pb.ClockOn();
            if (oc1) {
                pa.PinConfig(6, AF_PP, _50MHz);
            }
            if (oc2) {
                pa.PinConfig(7, AF_PP, _50MHz);
            }
            if (oc3) {
                pb.PinConfig(0, AF_PP, _50MHz);
            }
            if (oc4) {
                pb.PinConfig(1, AF_PP, _50MHz);
            }

            break;
            //pb6,pb7,pb8,pb9   
        case TIM4_BASE:
            pb.ClockOn();
            if (oc1) {
                pb.PinConfig(6, AF_PP, _50MHz);
            }
            if (oc2) {
                pb.PinConfig(7, AF_PP, _50MHz);
            }
            if (oc3) {
                pb.PinConfig(8, AF_PP, _50MHz);
            }
            if (oc4) {
                pb.PinConfig(9, AF_PP, _50MHz);
            }
            break;
    }

    if (oc1) {
        pa.PinConfig(0, AF_PP, _50MHz);
        tim->CCMR1 &= 0xff00;
        tim->CCMR1 |= 0x007c;
        tim->CCER |= 0x0003;
    }
    if (oc2) {
        pa.PinConfig(1, AF_PP, _50MHz);
        tim->CCMR1 &= 0x00ff;
        tim->CCMR1 |= 0x7c00;
        tim->CCER |= 0x0030;
    }
    if (oc3) {
        pa.PinConfig(2, AF_PP, _50MHz);
        tim->CCMR2 &= 0xff00;
        tim->CCMR2 |= 0x007c;
        tim->CCER |= 0x0300;
    }
    if (oc4) {
        pa.PinConfig(3, AF_PP, _50MHz);
        tim->CCMR2 &= 0x00ff;
        tim->CCMR2 |= 0x7c00;
        tim->CCER |= 0x3000;
    }
}


inline void CPWM::Run() {
    this->tim->Cmd(ENABLE);
}


void CPWM::set(uint8 ocn, deci dc) {
    uint16 rdc = (int)(dc * tim->ARR);
    switch (ocn) {
        case 1:
            tim->CCR1 = rdc;
            return;
        case 2:
            tim->CCR2 = rdc;
            return;
        case 3:
            tim->CCR3 = rdc;
            return;
        case 4:
            tim->CCR4 = rdc;
            return;

        default:
            return;
    }
}


deci CPWM::get(uint8 ocn) {
    switch (ocn) {
        case 1:

            return tim->CCR1;
        case 2:

            return tim->CCR2;
        case 3:

            return tim->CCR3;
        case 4:

            return tim->CCR4;
        default:
            return 0;
    }
}