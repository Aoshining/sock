#pragma once//header file protection

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Diary{

public:
	Diary();
	~Diary();
	void pdadd();
	void pdlist(string date1,string date2);
	void pdshow(string date);
	void pdremove(string date);

private:
	ifstream ifile;
	vector<string> diarylist;
	int Isdate(string date);
};