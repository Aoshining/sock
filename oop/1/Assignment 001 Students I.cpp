#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

int main()
{
    string name[10];//the names of students
    int sc1[10],sc2[10],sc3[10];//the scores of students for three courses
    float avr[10];//the average scores of students relatively
    int max[3] = {0}, min[3];//the maximum and minimum scores of three courses relatively
    float average[3] = {0.0};//the average scores of three courses relatively
    for(int i = 0; i < 10; i++)
    {
        cin >> name[i] >> sc1[i] >> sc2[i] >> sc3[i];//input record
        if(sc1[i] >= max[0])
            max[0] = sc1[i];
        if(sc1[i] <= min[0]||i == 0)//when i=0, initialize the min[]
            min[0] = sc1[i];
        if(sc2[i] >= max[1])
            max[1] = sc2[i];
        if(sc2[i] <= min[1]||i == 0)
            min[1] = sc2[i];
        if(sc2[i] >= max[2])
            max[2] = sc3[i];
        if(sc2[i] <= min[2]||i == 0)
            min[2] = sc3[i];
        avr[i] = 1.0 * (sc1[i] + sc2[i] + sc3[i]) / 3;//compute the average score of each student
        average[0] += sc1[i];//Firstly, compute the sum score of every course in the loops
        average[1] += sc2[i];
        average[2] += sc3[i];
    }
    average[0] = average[0] * 1.0 / 10;//Then compute the average score of every course
    average[1] = average[1] * 1.0 / 10;
    average[2] = average[2] * 1.0 / 10;
    cout << "no      name    score1  score2  score3  average" << endl;
    for(int i = 0; i < 10; i++)
        cout << setw(8) << left << i+1 << setw(8) << left << name[i] << setw(8) << left << sc1[i] << setw(8) << left << sc2[i] << setw(8) <<left << sc3[i] << avr[i] << endl;//Ensure the output list is left-aligned and occupies 8 characters by "<< setw(8) << left"
    cout << "        average " << setw(8) << left << average[0] << setw(8) << left << average[1] << setw(8) << left << average[2] << endl;
    cout << "        min     " << setw(8) << left << min[0] << setw(8) << left << min[1] << setw(8) << left << min[2] << endl;
    cout << "        max     " << setw(8) << left << max[0] << setw(8) << left << max[1] << setw(8) << left << max[2] << endl;
    return 0;
}