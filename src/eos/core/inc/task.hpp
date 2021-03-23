#pragma once

#include "defing.hpp"

#define maxTask 5




typedef struct {
    byte* stackHead;//指向栈区首地址
    uint32 sp;
    uint32 lr;
    char name[15];//用来保存任务的名称
    uint32 workms;//记录当前片段执行时间
}TaskTable;



class Task {
    uint32 length;
    TaskTable taskTable[maxTask];
public:
    Task();
    void Add(Func func, char name[15], uint32 stackSize);
    void TaskDelayms(uint32 ms);
    void Del(char name[15]);
    void Run();
};




