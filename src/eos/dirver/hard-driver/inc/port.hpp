#pragma once

#include "gpio.hpp"

//总线，协议
namespace BUS
{
    //串口
    class Serial
{
        //总线各个端口对应的gpio
        CGPIO **gpios;
        //总线各个端口对应的引脚
        uint8 *pins;
        //修改指定类型端口的电平
        void Set(uint8 port,  voltage o);
        //读取指定类型端口的电平
        bool Get(uint8 pin);
        //设置所有端口的值
        Serial &operator<<(uint32 a);
        //时序控制
        Serial &operator<<(Serial &(*tickCtrl)(uint32 ticks));
        //读取所有端口的值
        Serial &operator>>(uint32 &a);
        //时序控制
        Serial &operator>>(Serial &(*tickCtrl)(uint32 ticks));
        ///总线时序控制
        static Serial &Delay(uint32 ticks);

        //写一个字节时序
        virtual void WriteByte(byte bt);
        //读一个字节时序
        virtual byte ReadByte();
    };

    //软驱I2C总线
    class SoftI2C : public Serial
    {
        SoftI2C(CGPIO &SDA, uint8 SDA_pin, CGPIO &SCK, uint8 SCK_pin);
    };
    //软驱SPI总线
    class SoftSPI : public Serial
    {

    };

    //自定义总线
    class CustomBus : public Serial
    {
        
    };

} // namespace BUS