#include "student2.h"

using namespace std;

void Student::setstudent(string sname)
{
    vector<course> tmp;
    course temp;
    temp.name=sname;
    tmp.push_back(temp);
    student.push_back(tmp);
}

void Student::setcourse(string name,float score)
{
    course tmp;
    tmp.name=name;
    tmp.score=score;
    student[student.size()-1].push_back(tmp);
    for(int i=0;i<cname.size();i++)
        if(cname[i]==name)return;//Prevent adding the same course
    cname.push_back(name);
}

void Student::print()
{
    float avr[student.size()]={0};
    cout << "no      name    ";
    for(int i=0;i<cname.size();i++)
        cout << setw(8) << left << cname[i];
    cout << "average" << endl;
    for(int i=0;i<student.size();i++)
    {
        cout << setw(8) << left << i+1 << setw(8) << left << student[i][0].name;
        for(int j=0;j<cname.size();j++)
        {
            for(int k=1;k<student[i].size();k++)//Check if the current student has taken the course
            {
                if(student[i][k].name==cname[j])//If yes, print the score
                {
                    avr[i]+=student[i][k].score;
                    cout << setw(8) << left << student[i][k].score;
                    break;
                }
                else if(k==student[i].size()-1)cout << "        ";//Else, print space to skip in the end of the loop
            }
        }
        avr[i]=avr[i]*1.0/(student[i].size()-1);
        cout << setw(8) << left << avr[i] << endl;
    }
    average();
    minmax();
}

void Student::average()
{
    cout << "        average ";
    float avr[cname.size()]={0};
    int count[cname.size()]={0};
    for(int i=0;i<cname.size();i++)
    {
        for(int j=0;j<student.size();j++)
        {
            for(int k=1;k<student[j].size();k++)
            if(student[j][k].name==cname[i])
            {
                avr[i]+=student[j][k].score;
                count[i]++;
            }
        }
        avr[i]/=count[i];
        cout << setw(8) << left << avr[i];
    }
    cout << endl;
}

void Student::minmax()
{
    float min[cname.size()],max[cname.size()]={0};
    for(int i=0;i<cname.size();i++)
    {
        int init=1;
        for(int j=0;j<student.size();j++)
        {
            for(int k=1;k<student[j].size();k++)
            if(student[j][k].name==cname[i])
            {
                if(min[i]>student[j][k].score||init)min[i]=student[j][k].score;
                if(max[i]<student[j][k].score)max[i]=student[j][k].score;
                init=0;
            }
        }
    }
    cout << "        min     ";
    for(int i=0;i<cname.size();i++)
        cout << setw(8) << left << min[i];
    cout << endl;
    cout << "        max     ";
    for(int i=0;i<cname.size();i++)
        cout << setw(8) << left << max[i];
    cout << endl;
}
