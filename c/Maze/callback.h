#ifndef CALLBACK_H
#define CALLBACK_H

#include "button.h"
#include "basic.h"
//键盘回调 
void KeyboardEventProcess(int key, int event);
//鼠标回调 
void MouseEventProcess(int x, int y, int button, int event);
//字符回调
void CharEventProcess(char ch); 
//计时器 
void TimerEventProcess(int timerID);

#endif
