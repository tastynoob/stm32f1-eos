#pragma once

#include "dirver-define.hpp"


void NullFunc();


extern Func TIM1_IRQ;
extern Func TIM2_IRQ;
extern Func TIM3_IRQ;
extern Func TIM4_IRQ;


class CTIM {
private:
    __IO uint16 CR1;
    uint16 RESERVED0;
    __IO uint16 CR2;
    uint16 RESERVED1;
    __IO uint16 SMCR;
    uint16 RESERVED2;
    __IO uint16 DIER;
    uint16 RESERVED3;

public:
    __IO uint16 SR;

private:
    uint16 RESERVED4;
    __IO uint16 EGR;
    uint16 RESERVED5;
public:
    __IO uint16 CCMR1;
private:
    uint16 RESERVED6;
public:
    __IO uint16 CCMR2;
private:
    uint16 RESERVED7;
    public:
        __IO uint16 CCER;
        private:
    uint16 RESERVED8;

public:
    __IO uint16 CNT;
private:
    uint16 RESERVED9;
    __IO uint16 PSC;
    uint16 RESERVED10;
public:
    __IO uint16 ARR;
private:
    uint16 RESERVED11;
    __IO uint16 RCR;
    uint16 RESERVED12;
public:
    __IO uint16 CCR1;
private:
    uint16 RESERVED13;
public:
    __IO uint16 CCR2;
private:
    uint16 RESERVED14;
public:
    __IO uint16 CCR3;
private:
    uint16 RESERVED15;
public:
    __IO uint16 CCR4;
private:
    uint16 RESERVED16;
    __IO uint16 BDTR;
    uint16 RESERVED17;
    __IO uint16 DCR;
    uint16 RESERVED18;
    __IO uint16 DMAR;
    uint16 RESERVED19;

public:
    //定时器初始化
    //关闭所有事件，开启预装载
    void ClockOn(uint16 arr, uint16 psc);
    //使能
    void Cmd(FUNCSTATUS status);
    //延迟n个tick,1tick的大小由arr和psc决定
    //此函数不会复原cnt,但是会重置中断标志位
    //1tick = 1中断时间
    void DelayTick(uint16 ntick);
    //启动定时器基本中断，输入中断函数地址
    void Interrupt(Func inter,Ptr ptrs, uint32 sub, uint32 pre);

};



#define TIM1_BASE 0x40012C00
#define TIM2_BASE 0x40000000
#define TIM3_BASE 0x40000400
#define TIM4_BASE 0x40000800

#define tim1 (*(CTIM *)TIM1_BASE)
#define tim2 (*(CTIM *)TIM2_BASE)
#define tim3 (*(CTIM *)TIM3_BASE)
#define tim4 (*(CTIM *)TIM4_BASE)