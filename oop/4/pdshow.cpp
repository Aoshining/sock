#include "diary.h"
using namespace std;

int main(int argc,char* argv[])
{
	Diary d;
	if(argc==1)
		d.pdshow("");
	else 
		for(int i=1;i<argc;i++)
			d.pdshow(argv[i]);
	return 0;
}