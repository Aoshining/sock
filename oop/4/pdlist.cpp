#include "diary.h"
using namespace std;

int main(int argc,char* argv[])
{
	Diary d;
	if(argc==1)
	{
		cout << "The list of all diaries is shown below:" << endl;
		d.pdlist("","9");
	}
	else if(argc==2)
	{
		cout << "The list of diaries from " << argv[1] << " to the present is shown below:" << endl;
		d.pdlist(argv[1],"9");
	}
	else
	{
		cout << "The list of diaries from " << argv[1] << " to " << argv[2] << " is shown below:" << endl;
		d.pdlist(argv[1],argv[2]);
	} 
	return 0;
}