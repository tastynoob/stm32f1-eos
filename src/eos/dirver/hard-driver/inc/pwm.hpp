#pragma once

#include "tim.hpp"



class CPWM {
public:
    CTIM* tim;
    CPWM(CTIM& tim);
    void Config(uint8 remapmod,bool oc1,bool oc2,bool oc3,bool oc4);
    void Run();
    void set(uint8 ocn, deci dc);
    deci get(uint8);
    
};



