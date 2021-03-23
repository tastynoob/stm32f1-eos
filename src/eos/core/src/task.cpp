#include "task.hpp"
#include "string.h"



__asm void LoadTask(uint32 sp, uint32 lr) {
    mov sp, r0
        bx r1
}


Task::Task() {
    length = 0;
}

void Task::Add(Func func, char name[15], uint32 stackSize) {
    taskTable[length].stackHead = new byte[stackSize];
    memcpy(taskTable[length].name, name, strlen(name));
    taskTable[length].sp = (uint32)(taskTable[length].stackHead + stackSize);
    taskTable[length].lr = (uint32)func;
}


void Task::TaskDelayms(uint32 ms) {
   
}

void Task::Run() {
    while (1) {
        LoadTask(taskTable[0].sp, taskTable[0].lr);
    }
}
