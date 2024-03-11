#include "student2.h"

using namespace std;

int main()
{
    string name;
    float score;
    Student a;
    cout << "(Input EOF to end input)" << endl; 
    while(1)//input data until input "EOF"
    {
        cin >> name;
        if(name=="EOF")break;
        a.setstudent(name);
        while(cin.get()!='\n'&&cin >> name)
        {   
            if(name=="EOF")break;
            cin >> score;
            a.setcourse(name,score);
        }
        if(name=="EOF")break;
    }
    a.print();
    return 0;
}
