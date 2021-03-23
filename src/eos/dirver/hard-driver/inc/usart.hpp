#pragma once

#include "powerMath.hpp"
#include "dirver-define.hpp"




class Formatter {

    void Run();
};


class CUSART {
private:
    __IO uint16 SR;
    uint16 RESERVED0;
    __IO uint16 DR;
    uint16 RESERVED1;
    __IO uint16 BRR;
    uint16 RESERVED2;
    __IO uint16 CR1;
    uint16 RESERVED3;
    __IO uint16 CR2;
    uint16 RESERVED4;
    __IO uint16 CR3;
    uint16 RESERVED5;
    __IO uint16 GTPR;
    uint16 RESERVED6;

public:
    //初始化串口,GPIO并使能
    //默认波特率为115200
    void ClockOn();
    bool Available();
    // //配置波特率
    // void Config(uint32 baud);


    //输出
    CUSART& operator<<(const char* str);
    //输出
    CUSART& operator<<(int a);
    //输出
    CUSART& operator<<(float a);
    //输出
    CUSART& operator<<(byte a);
    CUSART& operator<<(Formatter& formatter);
    //输入,遇到换行符结束
    CUSART& operator>>(char* buff);

    void Any();


};



#define USART1_BASE 0x40013800
#define USART2_BASE 0x40004400
#define USART3_BASE 0x40004800

#define usart1 (*(CUSART *)USART1_BASE)
#define usart2 (*(CUSART *)USART2_BASE)
#define usart3 (*(CUSART *)USART3_BASE)






