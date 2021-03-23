
#include "usart.hpp"
#include "tim.hpp"
#include "SysTick.h"
#include "powerMath.hpp"
#include "list"
#include "cstdarg"
#include "gpio.hpp"
#include "pwm.hpp"
#include "action.hpp"
#include "task.hpp"


#define dir 1
#define run 0


void step() {
    pa.Set(run, LOW);
    pa.Set(run, HIGH);
    SysTick_DelaySync(1);
    pa.Set(run, LOW);
}

  


int main() {
    pa.ClockOn();
    pa.PinConfig(run, OUT_PP, _50MHz);
    pa.PinConfig(dir, OUT_PP, _50MHz);
    pa.Set(run, LOW);
    pa.Set(dir, LOW);
    
    while (1) {
        step();
        Delayms(100);
    }




    
}
































































































