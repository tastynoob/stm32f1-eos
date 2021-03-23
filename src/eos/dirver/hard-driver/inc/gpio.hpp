#pragma once

#include "dirver-define.hpp"

enum GPIO_SPEED {
    _in_ = 0x0,
    _10MHz = 0x1,
    _2MHz = 0x2,
    _50MHz = 0x3,
};
enum GPIO_MODE {
    IN_ANALOG = 0x0,   //模拟输入
    IN_FLOATING = 0x4, //浮空输入
    IN_UORD = 0x8,     //上下拉输入
    OUT_PP = 0x0,      //推挽输出
    OUT_OD = 0x4,      //开漏输出
    AF_PP = 0x8,       //复用推挽输出
    AF_OD = 0xc,       //复用开漏输出
};



class CGPIO {
    private:
    __IO uint32 CRL;
    __IO uint32 CRH;
    __IO uint32 IDR;
    __IO uint32 ODR;
    __IO uint32 BSRR;
    __IO uint32 BRR;
    __IO uint32 LCKR;

    public:
    //初始化
    void ClockOn();
    //配置GPIO
    void PinConfig(uint32 pin, GPIO_MODE mode, GPIO_SPEED speed);
    //读取指定引脚
    voltage Get(uint32 pin);
    //设置引脚电平
    void Set(uint32 pin, voltage o);
    //翻转指定引脚的输出电平
    void Flip(uint32 pin);
    //设置输出寄存器的值
    CGPIO& operator<<(uint32 odr);
    //读取输入寄存器的值
    CGPIO& operator>>(uint32& idr);
};

#define PA_BASE 0x40010800
#define PB_BASE 0x40010C00
#define PC_BASE 0x40011000

#define pa (*(CGPIO *)PA_BASE)
#define pb (*(CGPIO *)PB_BASE)
#define pc (*(CGPIO *)PC_BASE)

#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x02000000U + ((addr & 0xFFFFF) << 5U) + ((bitnum) << 2U))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))
//IO口地址映射
#define GPIOA_ODR_Addr (GPIOA_BASE + 12)
#define GPIOB_ODR_Addr (GPIOB_BASE + 12)
#define GPIOC_ODR_Addr (GPIOC_BASE + 12)
//每个端口的输出输出
#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr, n) //输出
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr, n)  //输入
#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr, n)
#define PBin(n) BIT_ADDR(GPIOB_IDR_Addr, n)
#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr, n)
#define PCin(n) BIT_ADDR(GPIOC_IDR_Addr, n)
