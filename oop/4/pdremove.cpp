#include "diary.h"
using namespace std;

int main(int argc,char* argv[])
{
	Diary d;
	if(argc==1)
	{
		cout << "Invalid input. You need to specify a date." << endl;
		return 0;
	}
	for(int i=1;i<argc;i++)
	{
		d.pdremove(argv[i]);
		cout << "The diary in the date " << argv[i] << " has been removed." << endl;
	}
	return 0;
}