#ifndef FILE_H
#define FILE_H


extern char CurrentFileName[MAX_PATH];//�����ļ���ز��������ļ��� 
extern int Bx,By;//�ƶ���ʵʱλ������ 
extern int Ex,Ey;//�������� 
extern int Map[L][L];//��¼�Թ���ͼ 

//��ȡ���ļ� 
void Open();
//��Ŀ���ļ� 
void Open_File(char *path);
//���뵱ǰ���� 
void Save();
//ѡ��Ŀ���ַ 
void Save_File(char *file);

#endif
