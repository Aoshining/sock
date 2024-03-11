#include"basic.h"
#include"help.h" 

#include"basic.h"
#include"help.h" 

void Help()
{
	
	MovePen(0,0);
	DefineColor("Dark5 Green",208.0/256,213.0/256,210.0/256);
	SetPenColor("Dark5 Green");
	StartFilledRegion(1);
	DrawLine(0,10);
	DrawLine(15,0);
	DrawLine(0,-10);
	DrawLine(-15,0);
	EndFilledRegion();
	SetPenColor("Black");
	
	MovePen(0,9.6);
	DrawTextString("「玩法介绍」"); 
	MovePen(0,9.2);
	DrawTextString("开始游戏前，你可以在设置中选择游戏的难度系数，游戏共分为四个模式"); 
	MovePen(0,8.8);
	DrawTextString("闯关模式：此模式以闯关的形式呈现，开始玩家位于迷宫的起点，迷宫终点在地图右上角某处，玩家需要操作上下左右键使蜘蛛侠顺利抵达终点处。");
	MovePen(0,8.5);
	DrawTextString("注意：在道路上存在“看不见”的陷阱（蜘蛛网），若踩到陷阱，玩家生命值将降低，生命值降为0即闯关失败；");
	MovePen(0,8.2);
	DrawTextString("            地图中的炸弹为道具，捡到它后，玩家可以使用它，一个炸药可以炸毁一块墙或陷阱；");
	MovePen(0,7.9);
	DrawTextString("            玩家可以在工具栏中点击寻路（寻找所有路径）或是提示（单步执行引路）进行迷宫求解；");
	MovePen(0,7.6);
	DrawTextString("            此外，玩家可以点击重新开始重新进行游戏，或者刷新进行新的游戏；");
	MovePen(0,7.3);
	DrawTextString("            如果玩家想暂离游戏，可以点击文件栏中的保存按钮（将当前地图保存到本地），下次再打开该文件即可继续进行游戏。");
	MovePen(0,6.8);
	DrawTextString("自定义模式：在此模式中，玩家可以自己动手设置一个迷宫。");
	MovePen(0,6.5);
	DrawTextString("注意：玩家可以在文件栏中点击保存按钮，将自己创造的地图保存到本地，以便下次可打开该地图；");
	MovePen(0,6.2);
	DrawTextString("            玩家可以点击工具栏中的刷新（创建新的地图）、寻找最短路径（进行迷宫求解）或是编辑（设置起点、终点和墙）。");
	MovePen(0,5.7);
	DrawTextString("迷雾模式：在此模式中，地图会闪烁呈现在玩家面前。");
	MovePen(0,5.4);
	DrawTextString("注意：玩家需点击工具栏中的开启迷雾从而开始移动。游戏会进行计时，玩家可以在上方的排名查看当前最快通关时间及玩家名称。") ;
	MovePen(0,5.1);
	DrawTextString("            此外，玩家可以点击工具栏中的寻路进行迷宫求解（打开寻路前需先关闭迷雾）。");
	MovePen(0,4.6);
	DrawTextString("一往无前模式：在此模式中，玩家不能走“回头路”，每移动一次，后路就会被封死。") ;
	MovePen(0,4.3);
	DrawTextString("注意：在道路上存在“看不见”的陷阱（蜘蛛网），若踩到陷阱，玩家生命值将降低，生命值降为0即闯关失败。");
	MovePen(0,4);
	DrawTextString("            玩家可以在工具栏中点击寻路（寻找所有路径）或是提示（单步执行引路）进行迷宫求解；");
	MovePen(0,3.7);
	DrawTextString("            此外，玩家可以点击重新开始重新进行游戏，或者刷新进行新的游戏。");
	MovePen(6,2);
	DrawTextString("祝您游戏愉快（按任意键退出介绍）");
	
}
