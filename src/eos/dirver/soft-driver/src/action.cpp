#include "action.hpp"


#include "usart.hpp"


EventTable::EventTable() {
    this->func = 0;
    this->beingListener = 0;
    this->triggerValue = 0;
    Triggered = false;
}



void StartListening(Ptr trigger) {
    Trigger* t = (Trigger*)trigger;
    for (int i = 0;i < t->length;i++) {
        if (t->events[i].beingListener[0] == t->events[i].triggerValue) {
            if (!t->events[i].Triggered) {
                t->events[i].Triggered = true;
                t->events[i].func(&(t->events[i]));
            }
        }
    }
}


Trigger::Trigger(int maxListener, CTIM& tim) {
    maxlength = maxListener;
    length = 0;
    this->events = new EventTable[maxlength];
    tim.Interrupt(StartListening, this, 0, 0);
}


void Trigger::Add(Func func, byte32& beingListener, byte32 triggerValue) {
    if (length < maxlength) {
        events[length].func = func;
        events[length].beingListener = &beingListener;
        events[length].triggerValue = triggerValue;
        length++;
    }
}



























