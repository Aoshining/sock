#include "Fraction.h"

using namespace std;

int Fraction::gcd(int a,int b)
{
	return (b==0) ? a : gcd(b,a%b);
}

Fraction::Fraction(int numerator,int denominator):num1(numerator),num2(denominator)//Initialize and simpify
{
	int g=gcd(num1,num2);
	if(g)//Neither numerator nor denominator is 0
	{
		num1/=g;
		num2/=g;
	}
	else if(num1==0&&num2!=0)num2=1;//The value of fraction is 0
	if(num2==0)decf="NaN";//The denominator is 0
	else
	{
		double ans=num1*1.0/num2;
		decf=to_string(ans);
	}
}

Fraction::Fraction(string f)
{
	decf=f;
	int i;
	if((i=f.find('.'))!=string::npos)
	{
		num1=stoi(f.substr(0,i)+f.substr(i+1));
		num2=pow(10,f.length()-1-i);
		int g=gcd(num1,num2);
		num1/=g;
		num2/=g;
	}
	else
	{
		num1=stoi(f);
		num2=1;
	}
}

Fraction::Fraction(const Fraction& f)
{
	num1=f.num1;
	num2=f.num2;
	decf=f.decf;
}

//Overload operators
Fraction Fraction::operator+(const Fraction& f)
{
	int numerator,denominator;
	numerator=num1*f.num2+num2*f.num1;
	denominator=num2*f.num2;
	Fraction temp(numerator,denominator);
	return temp;
}

Fraction Fraction::operator-(const Fraction& f)
{
	int numerator,denominator;
	numerator=num1*f.num2-num2*f.num1;
	denominator=num2*f.num2;
	Fraction temp(numerator,denominator);
	return temp;
}

Fraction Fraction::operator*(const Fraction& f)
{
	int numerator,denominator;
	numerator=num1*f.num1;
	denominator=num2*f.num2;
	Fraction temp(numerator,denominator);
	return temp;
}

Fraction Fraction::operator/(const Fraction& f)
{
	int numerator,denominator;
	numerator=num1*f.num2;
	denominator=num2*f.num1;
	Fraction temp(numerator,denominator);
	return temp;
}

bool Fraction::operator<(const Fraction& f)
{
	double double1=stod(decf);
	double double2=stod(f.decf);
	if(double1<double2)return true;
	else return false;
}

bool Fraction::operator<=(const Fraction& f)
{
	double double1=stod(decf);
	double double2=stod(f.decf);
	if(double1<=double2)return true;
	else return false;
}

bool Fraction::operator==(const Fraction& f)
{
	if(decf==f.decf)return true;
	else return false;
}

bool Fraction::operator!=(const Fraction& f)
{
	if(*this==f)return false;
	else return true;
}

bool Fraction::operator>=(const Fraction& f)
{
	if(*this<f)return false;
	else return true;
}

bool Fraction::operator>(const Fraction& f)
{
	if(*this<=f)return false;
	else return true;
}

//Overload i/ostream
istream& operator>>(istream& in,Fraction& f)
{
	string fraction;
	in >> fraction;
	int i;
	if((i=fraction.find('/'))!=string::npos)//Determine whether the input from terminal is a fraction or a decmical string
	{
		int num1,num2;
		num1=stoi(fraction.substr(0,i));
		num2=stoi(fraction.substr(i+1));
		f=Fraction(num1,num2);
	}
	else f=Fraction(fraction);
	return in;
}

ostream& operator<<(ostream& out,const Fraction& f)
{
	string fraction;
	string decf="("+f.decf+")";
	if(f.decf!="NaN")//Determine if denominator is 0
	{
		if(f.decf[0]=='-')//Determine if fraction is negative
			fraction="-"+to_string(abs(f.num1))+"/"+to_string(abs(f.num2));
		else
			fraction=to_string(abs(f.num1))+"/"+to_string(abs(f.num2));
			out << setw(8) << left << fraction << decf;
	}
	else out << decf;
	return out;
}