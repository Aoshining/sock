#include "basic.h"
#include"file.h"






void Open()
{
	typedef struct{
		int bx;int by;
		int ex;int ey;
		int map[L][L];
	}Data;  
	Data *mp=(Data *)malloc(sizeof(Data));//定义结构体指针，暂存读入的数据 
	FILE *fp;
	if((fp=fopen(CurrentFileName,"r"))==NULL)
	{
		MovePen(12,5);
		DrawTextString("打开失败");
	}
		
	rewind(fp);
	if(fscanf(fp,"%d %d ",&(mp->bx),&(mp->by))!=2)
	{
		MovePen(12,5);
		DrawTextString("格式错误");
		return ;
	}
	if(fscanf(fp,"%d %d ",&(mp->ex),&(mp->ey))!=2)
	{
		MovePen(12,5);
		DrawTextString("格式错误");
		return ;
	}
	int i,j;
	for(i=0;i<L;i++)
		for(j=0;j<L;j++)
		if(fscanf(fp,"%d ",&(mp->map[i][j]))!=1)
		{
			MovePen(12,5);
			DrawTextString("格式错误");
			return ;
		}
	//数据无误则将指针中的数据存入相应变量 
	Bx=mp->bx;By=mp->by;
	Ex=mp->ex;Ey=mp->ey;
	for(i=0;i<L;i++)
		for(j=0;j<L;j++)Map[i][j]=mp->map[i][j];
	free(mp);
	mp=NULL;
	fclose(fp);
	fp=NULL;
}

void Open_File(char *path)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn,sizeof(ofn));
	memset(path,0,sizeof(char)*MAX_PATH);
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.lpstrFile=path;
	ofn.nMaxFile=MAX_PATH;
	ofn.lpstrFilter="文件(*.txt)\0*.txt\0";
	ofn.Flags=OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
	GetOpenFileName(&ofn);
	Open();
}

void Save()
{
	FILE *fp;
	if((fp=fopen(CurrentFileName,"w"))==NULL)
	{
		MovePen(12,5);
		DrawTextString("保存失败");
	}
		
	rewind(fp);
	fprintf(fp,"%d %d ",Bx,By);
	fprintf(fp,"%d %d ",Ex,Ey);
	int i,j;
	for(i=0;i<L;i++)
		for(j=0;j<L;j++)
			fprintf(fp,"%d ",Map[i][j]);
	fclose(fp);
	fp=NULL;
}

void Save_File(char *file)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn,sizeof(ofn));
	memset(file,0,sizeof(char)*MAX_PATH);
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.lpstrFile=file;
	ofn.nMaxFile=MAX_PATH;
	ofn.lpstrFilter="文件(*.txt)\0*.txt\0";
	ofn.Flags=OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
	GetSaveFileName(&ofn);
	//保证用户命名文件的后缀一定为.txt 
	int l=strlen(file);
	if(strcmp(file+l-4,".txt"))
		strcpy(CurrentFileName,strcat(file,".txt"));
	else
		strcpy(CurrentFileName,file);
	Save();
}
