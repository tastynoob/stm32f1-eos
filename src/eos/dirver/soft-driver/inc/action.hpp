#pragma once


#include "dirver-define.hpp"
#include "tim.hpp"


typedef int byte32;


class EventTable {
public:
    EventTable();
    byte32* beingListener;
    byte32 triggerValue;
    Func func;
    bool Triggered;
};




class Trigger {
public:
    EventTable* events;
    uint32 maxlength;
    uint32 length ;
    
    Trigger(int maxListener,CTIM& tim);

    void Add(Func func,byte32& beingListener,byte32 triggerValue);
    
};












