#include "basic.h"
#include "move.h"
void MoveBlock(int key,int event)
{
	if(Map[Bx][By]==TRP||Map[Bx][By]==TRP2)
		{
			life--;
			Bx-=trap[0];
			By-=trap[1];
		}
	switch(event){
		case KEY_DOWN:
			switch (key){
				case VK_UP:
					if(Map[Bx][By+1]!=BLK)//ÅÐ¶ÏÊÇ·ñÎªÇ½ 
						{
							if(Map[Bx][By+1]==TRP||Map[Bx][By+1]==TRP2)
							{
								By=By+1;
								trap[0]=0;
								trap[1]=1;
							}
							else 
							{
								trace[1][0]=trace[0][0];
								trace[1][1]=trace[0][1];
								trace[0][0]=0;
								trace[0][1]=1;
								By=By+1;
								if(Go)
								{
									DrawWall(Bx-trace[0][0],By-trace[0][1],0.3);
									Map[Bx-trace[0][0]][By-trace[0][1]]=BLK;
									if(trace[1][0]||trace[1][1])Map[Bx-trace[0][0]-trace[1][0]][By-trace[0][1]-trace[1][1]]=ACS;
								}
							
							}
						}
					break;
			    case VK_DOWN:
					if(Map[Bx][By-1]!=BLK)//ÅÐ¶ÏÊÇ·ñÎªÇ½
						{
							if(Map[Bx][By-1]==TRP||Map[Bx][By-1]==TRP2)
							{
								By=By-1;
								trap[0]=0;
								trap[1]=-1;
							}
							else 
							{
								trace[1][0]=trace[0][0];
								trace[1][1]=trace[0][1];
								trace[0][0]=0;
								trace[0][1]=-1;
								By=By-1;
								if(Go)
								{
									DrawWall(Bx-trace[0][0],By-trace[0][1],0.3);
									Map[Bx-trace[0][0]][By-trace[0][1]]=BLK;
									if(trace[1][0]||trace[1][1])Map[Bx-trace[0][0]-trace[1][0]][By-trace[0][1]-trace[1][1]]=ACS;
								}
							}
						}
					break;
				case VK_LEFT:
					if(Map[Bx-1][By]!=BLK)//ÅÐ¶ÏÊÇ·ñÎªÇ½
						{
							if(Map[Bx-1][By]==TRP||Map[Bx-1][By]==TRP2)
							{
								Bx=Bx-1;
								trap[0]=-1;
								trap[1]=0;
							}
							else
							{
								trace[1][0]=trace[0][0];
								trace[1][1]=trace[0][1];
								trace[0][0]=-1;
								trace[0][1]=0;
								Bx=Bx-1;
								if(Go)
								{
									DrawWall(Bx-trace[0][0],By-trace[0][1],0.3);
									Map[Bx-trace[0][0]][By-trace[0][1]]=BLK;
									if(trace[1][0]||trace[1][1])Map[Bx-trace[0][0]-trace[1][0]][By-trace[0][1]-trace[1][1]]=ACS;
								}
							}
								
						}
					break;	
				case VK_RIGHT:
					if(Map[Bx+1][By]!=BLK)//ÅÐ¶ÏÊÇ·ñÎªÇ½
						{
							if(Map[Bx+1][By]==TRP||Map[Bx+1][By]==TRP2)
							{
								Bx=Bx+1;
								trap[0]=1;
								trap[1]=0;
							}
							else
							{
								trace[1][0]=trace[0][0];
								trace[1][1]=trace[0][1];
								trace[0][0]=1;
								trace[0][1]=0;
								Bx=Bx+1;
								if(Go)
								{
									DrawWall(Bx-trace[0][0],By-trace[0][1],0.3);
									Map[Bx-trace[0][0]][By-trace[0][1]]=BLK;
									if(trace[1][0]||trace[1][1])Map[Bx-trace[0][0]-trace[1][0]][By-trace[0][1]-trace[1][1]]=ACS;
								}	
							}
						}			
					break;
			}
	}
	
}
