#include "gpio.hpp"
#include "rcc.hpp"

void CGPIO::ClockOn() {
    switch ((int)this) {
        case PA_BASE:
            rcc.APB2Cmd(_IOA, ENABLE);
            //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE0);
            break;
        case PB_BASE:
            rcc.APB2Cmd(_IOB, ENABLE);
            //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE0);
            break;
        case PC_BASE:
            rcc.APB2Cmd(_IOC, ENABLE);
            //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE0);
            break;
    }
}

void CGPIO::PinConfig(uint32 pin, GPIO_MODE mode, GPIO_SPEED speed) {
    uint32 ms = mode + speed;
    if (pin > 7) {
        pin = (pin - 8) * 4;
        ms <<= pin;
        CRH &= ~((0x0000000f) << (pin));
        CRH |= ms;
    }
    else {
        ms <<= (pin *= 4);
        CRL &= ~((0x0000000f) << (pin));
        CRL |= ms;
    }
}

voltage CGPIO::Get(uint32 pin) {
    return (voltage)(IDR >> pin);
}

void CGPIO::Set(uint32 pin, voltage o) {
    BitSet(BSRR, o ? pin : pin + 16);
}

void CGPIO::Flip(uint32 pin) {
    if (ODR & (1 << pin)) {
        BitSet(BSRR, pin + 16);
    }
    else {
        BitSet(BSRR, pin);
    }
}

CGPIO& CGPIO::operator<<(uint32 odr) {
    ODR = (0x0000ffff & odr);
    return *this;
}

CGPIO& CGPIO::operator>>(uint32& idr) {
    idr = IDR;
    return *this;
}