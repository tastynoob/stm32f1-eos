#pragma once


#include "dirver-define.hpp"


enum APB1 {
    _TIM2 = 0,
    _TIM3,
    _TIM4,
    _TIM5,
    _TIM6,
    _TIM7 = 5,
    _WWDG = 11,
    _SPI2 = 14,
    _SPI3 = 15,
    _USART2 = 17,
    _USART3,
    _USART4,
    _USART5 = 20,
    _I2C1 = 21,
    _I2C2,
    _CAN1 = 25,
    _CAN2,
    _BKP,
    _PWR,
    _DAC,
};

enum APB2 {
    _AFIO = 0,
    _IOA = 2,
    _IOB,
    _IOC,
    _IOD,
    _IOE,
    _ADC1 = 9,
    _ADC2,
    _TIM1,
    _SPI1,
    _USART1 = 14
};


typedef struct {
    uint32 SYSCLK_Frequency;  /*!< returns SYSCLK clock frequency expressed in Hz */
    uint32 HCLK_Frequency;    /*!< returns HCLK clock frequency expressed in Hz */
    uint32 PCLK1_Frequency;   /*!< returns PCLK1 clock frequency expressed in Hz */
    uint32 PCLK2_Frequency;   /*!< returns PCLK2 clock frequency expressed in Hz */
    uint32 ADCCLK_Frequency;  /*!< returns ADCCLK clock frequency expressed in Hz */
}RCC_ClocksTypeDef;



class CRCC {
public:
    __IO uint32 CR;
    __IO uint32 CFGR;
    __IO uint32 CIR;
    __IO uint32 APB2RSTR;
    __IO uint32 APB1RSTR;
    __IO uint32 AHBENR;
    __IO uint32 APB2ENR;
    __IO uint32 APB1ENR;
    __IO uint32 BDCR;
    __IO uint32 CSR;
    
#ifdef STM32F10X_CL
    __IO uint32_t AHBRSTR;
    __IO uint32_t CFGR2;
#endif /* STM32F10X_CL */
#if defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL)
    uint32_t RESERVED0;
    __IO uint32_t CFGR2;
#endif /* STM32F10X_LD_VL || STM32F10X_MD_VL || STM32F10X_HD_VL */


    void APB1Cmd(APB1 apb1, FUNCSTATUS statu);
    void APB2Cmd(APB2 apb2, FUNCSTATUS statu);
    void APB1Reset(APB1 apb1);
    void APB2Reset(APB2 apb2);
    uint32 GetAPB1Clock();
    uint32 GetAPB2Clock();
    
    
};




#define RCC_BASE0 0x40021000
#define rcc (*(CRCC*)RCC_BASE0)