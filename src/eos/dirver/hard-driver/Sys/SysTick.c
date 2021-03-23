#include "SysTick.h"

uint16_t _isTimeout;
uint32_t _loopMax, _loopCount, _val, _sysCLK = 72;
SysTickCallback _callback = 0x0;

#define true 1
#define false 0

#define SysTick_IsTimeout() _isTimeout

void SysTick_Init(uint32_t _sysClock)
{
    _sysCLK = _sysClock;
}

void _ReloadIf()
{
    _loopCount++;

    if (_loopCount < _loopMax)
    {
        if (_loopCount + 1 == _loopMax)
        {
            SysTick->LOAD = _val;
        }
        _isTimeout = false;
    }
    else
    {
        _isTimeout = true;
        _loopCount = 0;
    }
}

// void SysTick_Handler(void)
// {
//     _ReloadIf();

//     if (SysTick_IsTimeout() && _callback)
//     {
//         _callback();
//     }
// }

void SysTick_SetCallback(SysTickCallback _func)
{
    _callback = _func;
}

void _SetTimerVal(uint64_t val)
{
    _loopCount = 0;
    _loopMax = val / 0x1000000U + 1;
    _val = val % 0x1000000U;

    SysTick->VAL = 0;

    if (_loopMax > 1)
    {
        SysTick->LOAD = 0xFFFFFFU;
    }
    else
    {
        SysTick->LOAD = _val;
    }
}

void SysTick_SetTimeUs(uint32_t us)
{
    uint32_t _unit = (SysTick->CTRL & 0x00000004) ? (_sysCLK / AHB_PRESCALE)
                                                : ((_sysCLK / AHB_PRESCALE) / 8);
    _SetTimerVal(((uint64_t)_unit) * us - 1);
}

void SysTick_SetTime(uint32_t ms)
{
    uint32_t _unit = (SysTick->CTRL & 0x00000004) ? (_sysCLK * 1000 / AHB_PRESCALE)
                                                : ((_sysCLK * 1000 / AHB_PRESCALE) / 8);
    _SetTimerVal(((uint64_t)_unit) * ms - 1);
}

void SysTick_Enable(uint8_t _sysTick_status)
{
    switch (_sysTick_status)
    {
    case SYSTICK_START:
        SysTick->CTRL |= 0x03;
        break;
    default:
        SysTick->CTRL &= 0xFFFFFFFC;
        break;
    }
}

void SysTick_DelaySync(uint32_t ms)
{
    uint32_t flag;

    SysTick_SetTime(ms);

    SysTick->CTRL &= 0xFFFFFFFD;

    SysTick->CTRL |= 0x01;

    while (true)
    {
        flag = SysTick->CTRL;

        if ((flag & 0x00010000) != 0)
        {
            _ReloadIf();

            if (SysTick_IsTimeout())
            {
                break;
            }
        }
    }

    SysTick->CTRL &= 0xFFFFFFFC;
}

void SysTick_DelaySyncUs(uint32_t us)
{
    uint32_t flag;

    SysTick_SetTimeUs(us);

    SysTick->CTRL &= 0xFFFFFFFD;

    SysTick->CTRL |= 0x01;

    while (true)
    {
        flag = SysTick->CTRL;

        if ((flag & 0x00010000) != 0)
        {
            _ReloadIf();

            if (SysTick_IsTimeout())
            {
                break;
            }
        }
    }

    SysTick->CTRL &= 0xFFFFFFFC;
}
