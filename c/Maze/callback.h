#ifndef CALLBACK_H
#define CALLBACK_H

#include "button.h"
#include "basic.h"
//���̻ص� 
void KeyboardEventProcess(int key, int event);
//���ص� 
void MouseEventProcess(int x, int y, int button, int event);
//�ַ��ص�
void CharEventProcess(char ch); 
//��ʱ�� 
void TimerEventProcess(int timerID);

#endif
