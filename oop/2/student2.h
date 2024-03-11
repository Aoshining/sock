#pragma once//header file protection

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Student{

private:
    struct course
    {
        string name;//the name of student or courses
        float score;//the scores of courses
    };
    vector<vector<course> > student;//the collection of students' information
    vector<string> cname;//the collection of courses
    void average();//print the average of courses relatively
    void minmax();//print the minimum and maximum scores of courses relatively

public:
    void setstudent(string sname);//input the name of student
    void setcourse(string cname,float score);//input the name and the score of the course
    void print();//print the chart
    
};
