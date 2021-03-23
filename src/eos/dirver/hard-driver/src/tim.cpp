#include "tim.hpp"
#include "rcc.hpp"
#include "system.hpp"

void NullFunc(Ptr ptr) {}

Ptr ptr1;
Ptr ptr2;
Ptr ptr3;
Ptr ptr4;

Func TIM1_IRQ = NullFunc;
Func TIM2_IRQ = NullFunc;
Func TIM3_IRQ = NullFunc;
Func TIM4_IRQ = NullFunc;



extern "C" {
    void TIM1_IRQHandler() {
        TIM1_IRQ(ptr1);
        BitReset(tim1.SR, 0);
    }
    void TIM2_IRQHandler() {
        TIM2_IRQ(ptr2);
        BitReset(tim2.SR, 0);
    }
    void TIM3_IRQHandler() {
        TIM3_IRQ(ptr3);
        BitReset(tim3.SR, 0);
    }
    void TIM4_IRQHandler() {
        TIM4_IRQ(ptr4);
        BitReset(tim4.SR, 0);
    }
}




void CTIM::ClockOn(uint16 arr, uint16 psc) {
    switch ((int)this) {
        case TIM1_BASE:
            rcc.APB2Cmd(_TIM1, ENABLE);
            rcc.APB2Reset(_TIM1);
            break;
        case TIM2_BASE:
            rcc.APB1Cmd(_TIM2, ENABLE);
            rcc.APB1Reset(_TIM2);
            break;
        case TIM3_BASE:
            rcc.APB1Cmd(_TIM3, ENABLE);
            rcc.APB1Reset(_TIM3);
            break;
        case TIM4_BASE:
            rcc.APB1Cmd(_TIM3, ENABLE);
            rcc.APB1Reset(_TIM3);
            break;
    }
    CR1 = 0x0000;
    //关闭自动重装模式
    BitSet(CR1, 7);

    PSC = psc - 1; //预分屏
    ARR = arr - 1; //重装载值

    EGR = 0x0001; //重新初始化定时器
    BitReset(SR, 0);
}

void CTIM::Cmd(FUNCSTATUS status) {
    if (status == ENABLE) {
        BitSet(CR1, 0); //使能
    }
    else {
        BitReset(CR1, 0);
    }
}


void CTIM::DelayTick(uint16 ntick) {
    BitReset(SR, 0);
    while (ntick) {
        if (BitGet(SR, 0) == 1) {
            BitReset(SR, 0);
            ntick--;
        }
    }
}




void CTIM::Interrupt(Func inter,Ptr args, uint32 sub, uint32 pre) {

    switch ((int)this) {
        case TIM1_BASE:
            TIM1_IRQ = inter;
            ptr1 = args;
            break;
        case TIM2_BASE:
            TIM2_IRQ = inter;
            ptr2 = args;
            break;
        case TIM3_BASE:
            TIM3_IRQ = inter;
            ptr3 = args;
            break;
        case TIM4_BASE:
            TIM4_IRQ = inter;
            ptr4 = args;
            break;
    }
    BitSet(DIER, 0);
    SCB->AIRCR = (0x05FA0000 | 0x700);

    {
        int tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700)) >> 0x08;
        int tmppre = (0x4 - tmppriority);
        int tmpsub = tmpsub >> tmppriority;
        tmppriority = pre << tmppre;
        tmppriority |= sub & tmpsub;
        tmppriority = tmppriority << 0x04;
        switch ((int)this) {
            case TIM1_BASE:
                TIM1_IRQ = inter;
                break;
            case TIM2_BASE:
                NVIC->IP[28] = tmppriority;
                NVIC->ISER[28 >> 0x05] = (uint32_t)0x01 << (28 & (uint8_t)0x1F);
                break;
            case TIM3_BASE:
                NVIC->IP[29] = tmppriority;
                NVIC->ISER[29 >> 0x05] = (uint32_t)0x01 << (29 & (uint8_t)0x1F);
                break;
            case TIM4_BASE:
                NVIC->IP[30] = tmppriority;
                NVIC->ISER[30 >> 0x05] = (uint32_t)0x01 << (30 & (uint8_t)0x1F);
                break;
        }
    }
}