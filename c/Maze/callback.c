#include "basic.h"
#include "callback.h"
//���̻ص� 
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); 
	
	if(Timer1==0&&Timer2==0)//��Ѱ·��δ��������ʧ�ܡ�ʤ��ʱ�޷������������� 
	{
		if((Button_Start||Enter!=3)&&!lose&&!heat)MoveBlock(key,event);
		display();
		if(Enter==3)Display();
	}
	help=0;
	if(Enter==5)Enter=0;
}
//���ص� 
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event);
	Cx=ScaleXInches(x);Cy=ScaleYInches(y);Cevent=event; 
	if(Timer1==0&&Timer2==0&&Timer33==0)//��Ѱ·ʱ�޷�������������
	display(); 
	if(Timer33==1&&event!=MOUSEMOVE&&Timer1==0&&Timer2==0)
	{
		display();
		Display();
	}
	
}
//�ַ��ص�
void CharEventProcess(char ch)
{
	uiGetChar(ch);
	if((ch=='\n'||ch=='\r')&&Winer==1)
		winer=1;
	if(Winer==1)
	{
		display(); 
	}
	
    
}

//��ʱ�� 
void TimerEventProcess(int timerID)
{
		   if(timerID==TIMER_BLINK500)
			{
				if(Time_i<step)
		   		{
		   			Block(road[Time_i][0],road[Time_i][1],0,0.2);
					Time_i++;
					
		   		}
		   		else{
		   			Timer1=0;//��ʱ��ֹͣ 
		   			cancelTimer(TIMER_BLINK500);
		   			Time_i=0;//ȷ����ť�����ظ����ʹ�� 
		   		}
		   		
			}
			else if(timerID==TIMER_BLINK1000)
			{
				if(Time_j<All_step)
				{
					if(All_way_visit[All_the_way[Time_j][0]][All_the_way[Time_j][1]]==0)
					{
						Block(All_the_way[Time_j][0],All_the_way[Time_j][1],5,0.2);
						All_way_visit[All_the_way[Time_j][0]][All_the_way[Time_j][1]]=1;//��¼�߹��õ�Ĵ�����ȷ����Ⱦ����ɫ����Ϊ�߹� 
						Time_j++;
						
					
					}
					else
					{
						SetEraseMode(TRUE);
						Block(All_the_way[Time_j][0],All_the_way[Time_j][1],8,0.2);
						SetEraseMode(FALSE);
						block(All_the_way[Time_j][0],All_the_way[Time_j][1],8,0.2);
						All_way_visit[All_the_way[Time_j][0]][All_the_way[Time_j][1]]=0;//���õ�״̬��Ϊδ�߹� 
						Time_j++;
					}	
				}
				else
				{
					Timer2=0;//��ʱ��ֹͣ 
					cancelTimer(TIMER_BLINK1000);
					Time_j=0;//ȷ����ť�����ظ����ʹ��
				}
			}
			else if(timerID==TIMER_BLINK1500)
			{
				Time++;
				if(Timer3==0)
				Timer3++;
				else if(Timer3==1)
				Timer3--;
		        Display();
			}
}
