#include "diary.h"
using namespace std;

int Diary::Isdate(string date)//Determine if the input string is a pure number
{
	for(int i=0;i<date.length();i++)
		if(date[i]<'0'||date[i]>'9')
			return 0;
	return 1;
}

Diary::Diary()//Pre-read all dates
{
	ifile.open("diary.txt");
	string content;
	while(getline(ifile,content))
	{
		diarylist.push_back(content);
		while(getline(ifile,content)&&content.length()!=1);
	}
	sort(diarylist.begin(),diarylist.end());//Sort existing dates
}

Diary::~Diary()//Close read file
{
	ifile.close();
}

void Diary::pdadd()
{
	string date;
	getline(cin,date);
	string tmp="";
	if(!Isdate(date))//If the user does not enter a date, the current date is automatically saved.
	{
		tmp=date;
		time_t nowtime;
		struct tm* p;
		time(&nowtime);
		p = localtime(&nowtime);
		date="";
		date+=to_string(p->tm_year+1900);
		if(to_string(p->tm_mon+1).length()==1)date+="0";
		date+=to_string(p->tm_mon+1);
		if(to_string(p->tm_mday).length()==1)date+="0";
		date+=to_string(p->tm_mday);
	}
	string content;
	vector<string>::iterator iter=std::find(diarylist.begin(),diarylist.end(),date);//Determine if a diary already exists with the same date
	if(iter!=diarylist.end())pdremove(date);

	ofstream ofile("diary.txt",ios::app);
	ofile << date << endl;
	if(tmp!="")ofile << tmp << endl;
	while(getline(cin,content))
	{
		ofile << content<< endl;
		if(content.length()==1)break;
	}
	if(cin.eof())ofile << " " << endl;
	ofile.close();
}

void Diary::pdlist(string date1,string date2)
{
	string date;
	int begin=0,end=diarylist.size()-1;
	int bflag=0,eflag=0;//Determines if a saved date boundary has been found for the given range.
	for(int i=0;i<diarylist.size();i++)
	{
		if(date1<=diarylist[i]&&!bflag)
		{
			begin=i;
			bflag=1;
		}
		if(date2>=diarylist[diarylist.size()-1-i]&&!eflag)
		{
			end=diarylist.size()-1-i;
			eflag=1;
		}
		if(bflag&&eflag)break;
	}
	for(int i=begin;i<=end;i++)
		cout << diarylist[i] <<endl;
}

void Diary::pdshow(string date)
{
	ifile.clear();
	ifile.seekg(0,ios::beg);
	string content;
	if(date=="")//If no date is specified, all diaries are output.
	{
		for(int i=0;i<diarylist.size();i++)
			pdshow(diarylist[i]);
	}
	else
	{
		while(getline(ifile,content))
		{
			if(content==date)
			{
				cout << "The content of diary in the date " << content << " is listed as follows." << endl;
				while(getline(ifile,content)&&content.length()!=1)
					cout << content << endl;
				return;
			}
		}
		cout << "No diary in the date " << date << "." << endl;
	}
	
}

void Diary::pdremove(string date)
{
	ifile.clear();
	ifile.seekg(0,ios::beg);
	ofstream ofile("temp.txt");
	string content;
	while(getline(ifile,content))
	{
		if(content==date)
		{	
			while(getline(ifile,content)&&content.length()!=1);
			continue;
		}
		ofile << content << endl;
	}
	ofile.close();

	ifstream infile("temp.txt");
	ofstream outfile("diary.txt");
	while(getline(infile,content))
		outfile << content << endl;
	infile.close();
	outfile.close();
	remove("temp.txt");
}