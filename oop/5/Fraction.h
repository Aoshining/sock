#ifndef FRACTION_H //header file protection
#define FRACTION_H

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

class Fraction{

	public:
		Fraction(){};//Default ctor
		Fraction(int numerator,int denominator);//Ctor1: Conversion from a fraction
		Fraction(string f);//Ctor2: Conversion from a finite decimal string
		Fraction(const Fraction& f);//Copy ctor
		//Arithmetical operating
		Fraction operator+(const Fraction& f);
		Fraction operator-(const Fraction& f);
		Fraction operator*(const Fraction& f);
		Fraction operator/(const Fraction& f);
		//Relational operating
		bool operator<(const Fraction& f);
		bool operator<=(const Fraction& f);
		bool operator==(const Fraction& f);
		bool operator!=(const Fraction& f);
		bool operator>=(const Fraction& f);
		bool operator>(const Fraction& f);
		//Inserter and extractor for streams
		friend istream& operator>>(istream& in,Fraction& f);
		friend ostream& operator<<(ostream& out,const Fraction& f);
		
	private:
		int num1,num2;//numerator, denominator
		string decf;//The decimal fraction
		int gcd(int a,int b);//The greatest common divisor
		double To_double(){return num1*1.0/num2;};//Typecast to double
		string To_string(double f){return to_string(f);};//To string
};

#endif