#include <iostream>
#include <cstdio> 
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

class Num{
	public:
		static string Int(char *number,int source,int target,int expand);
		static string Float(char *number,int source);
		static string Double(char *number,int source);
		static string Dec(char *number,char* source);
		static string IntCompute(char* number1, char* number2, int source, int target, int expand, int compute);
		static string DecCompute(char* number1, char* number2, char* source, int compute);
		static string FloatCompute(char* number1, char* number2, int source, int compute);
		static string DoubleCompute(char* number1, char* number2, int source, int compute);
};


// class INT{
	
// 	public:
// 		INT(char *s):num(s){}
// 		friend string Shift(char *number,int sourse,int target,int expand);

// 	private:
// 		char *num;
// };

string Num::Int(char *number,int source,int target,int expand)//number：待转换的数字 source：原进制 target：目标进制 expand：拓展至expand位（填0则不拓展）
{
	char *stop;
	int i=strtol(number, &stop, source);
	if(*stop!='\0')
	{
		return "Not a valid integer.";
	}
	char integer[100]={0};
	itoa(i,integer,target);
	string tnum=integer;
	if(expand)
	{
		if(tnum.length()<expand)
			tnum.insert(0,expand-tnum.length(),'0');
		else if(tnum.length()>expand)
			tnum.erase(0,tnum.length()-expand);
	}
	//cout << tnum << endl;	
	return tnum;
}

// class FP{
	
// 	public:
// 		FP(char *s):num(s){}
// 		friend string Shift(char *number,int sourse,int target,int expand);
// 		string Float(char *number,int source);
// 		string Double(char *number,int source);

// 	private:
// 		char *num;
// };

string Num::Dec(char *number,char *source)//转为十进制浮点数
{
	string fp;
	if(strcmp(source,"float")==0)
	{
		if(strlen(number)!=32)
		{
			fp="Not a valid float number.";
			return fp;
		}
		string num=number;
		double decfp=1;
		int exp=strtol(num.substr(1,8).c_str(),NULL,2)-127;
		for(int i=9;i<=31;i++)
			decfp+=(num[i]-'0')*pow(2,-i+8);
		if(num[0]=='1')decfp*=-1;
		decfp*=pow(2,exp);
		char ans[100];
		sprintf(ans,"%lf",decfp);
		fp=ans;
		return fp;
	}
	else if(strcmp(source,"double")==0)
	{
		if(strlen(number)!=64)
		{
			fp="Not a valid double number.";
			return fp;
		}
		string num=number;
		double decfp=1;
		int exp=strtol(num.substr(1,11).c_str(),NULL,2)-1023;
		for(int i=12;i<=63;i++)
			decfp+=(num[i]-'0')*pow(2,-i+11);
		if(num[0]=='1')decfp*=-1;
		decfp*=pow(2,exp);
		char ans[100];
		sprintf(ans,"%lf",decfp);
		fp=ans;
		return fp;
	}
	else
	{
		char *stop;
		int nsource=strtol(source, &stop, 10);
		if(*stop!='\0')
		{
			fp="Not a valid source.";
			return fp;
		}
		Num n;
		string num=n.Float(number,nsource);
		double decfp=1;
		int exp=strtol(num.substr(1,8).c_str(),NULL,2)-127;
		for(int i=9;i<=31;i++)
			decfp+=(num[i]-'0')*pow(2,-i+8);
		if(num[0]=='1')decfp*=-1;
		decfp*=pow(2,exp);
		char ans[100];
		sprintf(ans,"%lf",decfp);
		fp=ans;
		return fp;
	}
}

string Num::Float(char *number,int source)//number：待转换的数字 source：目标进制
{
	string fp;
	if(number[0]=='-')fp+="1";
	else fp+="0";
	char cinteger[100]={0};
	double nfraction=0;
	int block=0;
	for(int i=fp[0]=='1'?1:0;i<strlen(number);i++)
	{
		if(number[i]=='.')
		{
			block=i;
			continue;
		}
		if(!block)cinteger[i-(fp[0]=='1'?1:0)]=number[i];
		else nfraction+=(number[i]-'0')*pow(source,-i+block);
	}
	string sinteger=Int(cinteger,source,2,0);

	int idx_1=0;
	int exp=0;
	if(sinteger[0]=='1')
	{
		idx_1=0;
		exp=127+sinteger.length()-1;
	}

	while(nfraction!=0&&sinteger.length()-idx_1-1<23)
	{
		nfraction*=2;
		if(nfraction>=1)
		{
			if(!exp)
			{
				idx_1=sinteger.length();
				exp=127-sinteger.length();
			}
			sinteger+="1";
			nfraction-=1;
		}
		else sinteger+="0";
	}
	fp+=Int((char*)to_string(exp).c_str(),10,2,8);
	
	string mantissa;
	if(sinteger.length()==idx_1)mantissa=sinteger.substr(idx_1);
	else mantissa=sinteger.substr(idx_1+1);
	if(mantissa.length()<23)mantissa.append(23-mantissa.length(),'0');
	fp+=mantissa;
	//cout<<fp<<endl;
	return fp;
}

string Num::Double(char *number,int source)//number：待转换的数字 source：目标进制
{
	string fp;
	if(number[0]=='-')fp+="1";
	else fp+="0";
	char cinteger[100]={0};
	double nfraction=0;
	int block=0;
	for(int i=fp[0]=='1'?1:0;i<strlen(number);i++)
	{
		if(number[i]=='.')
		{
			block=i;
			continue;
		}
		if(!block)cinteger[i-(fp[0]=='1'?1:0)]=number[i];
		else nfraction+=(number[i]-'0')*pow(source,-i+block);
	}
	string sinteger=Int(cinteger,source,2,0);

	int idx_1=0;
	int exp=0;
	if(sinteger[0]=='1')
	{
		idx_1=0;
		exp=1023+sinteger.length()-1;
	}

	while(nfraction!=0&&sinteger.length()-idx_1-1<52)
	{
		nfraction*=2;
		if(nfraction>=1)
		{
			if(!exp)
			{
				idx_1=sinteger.length();
				exp=1023-sinteger.length();
			}
			sinteger+="1";
			nfraction-=1;
		}
		else sinteger+="0";
	}
	fp+=Int((char*)to_string(exp).c_str(),10,2,11);
	
	string mantissa;
	if(sinteger.length()==idx_1)mantissa=sinteger.substr(idx_1);
	else mantissa=sinteger.substr(idx_1+1);
	if(mantissa.length()<52)mantissa.append(52-mantissa.length(),'0');
	fp+=mantissa;
	//cout<<fp<<endl;
	return fp;
}




string Num::IntCompute(char *number1,char *number2,int source,int target,int expand,int compute)
{
	char *stop;
	int int1=strtol(number1, &stop, source);
	if(*stop!='\0')
		return "Not a valid integer.";
	int int2=strtol(number2, &stop, source);
	if(*stop!='\0')
		return "Not a valid integer.";
	char ans[100];
	if(compute==1)// +
		itoa(int1+int2,ans,target);
	else if(compute==2)// -
		itoa(int1-int2,ans,target);
	else if(compute==3)// *
		itoa(int1*int2,ans,target);
	else if(compute==4)// /
		itoa(int1/int2,ans,target);
	string num=ans;
	if(expand)
	{
		if(num.length()<expand)
			num.insert(0,expand-num.length(),'0');
		else if(num.length()>expand)
			num.erase(0,num.length()-expand);
	}
	return num;
}

string Num::DecCompute(char *number1,char *number2,char *source,int compute)//十进制形式的浮点数运算
{
	string fp;
	string fp1=Dec(number1,source),fp2=Dec(number2,source);
	double decfp1=atof(fp1.c_str()),decfp2=atof(fp2.c_str());
	char ans[100];
	if(compute==1)// +
		sprintf(ans,"%lf",decfp1+decfp2);
	else if(compute==2)// -
		sprintf(ans,"%lf",decfp1-decfp2);//cout<<ans<<endl;
	else if(compute==3)// *
		sprintf(ans,"%lf",decfp1*decfp2);
	else if(compute==4)// /
		sprintf(ans,"%lf",decfp1/decfp2);
	fp=ans;
	return fp;
}

string Num::FloatCompute(char *number1,char *number2,int source,int compute)
{
	string fp1=Float(number1,source),fp2=Float(number2,source);
	double decfp1=1,decfp2=1;
	int exp1=strtol((char *)fp1.substr(1,8).c_str(),NULL,2)-127;
	int exp2=strtol((char *)fp2.substr(1,8).c_str(),NULL,2)-127;//cout<<exp1<<" "<<exp2<<endl;
	for(int i=9;i<=31;i++)
	{
		decfp1+=(fp1[i]-'0')*pow(2,-i+8);
		decfp2+=(fp2[i]-'0')*pow(2,-i+8);
	}
	if(fp1[0]=='1')decfp1*=-1;
	if(fp2[0]=='1')decfp2*=-1;
	decfp1*=pow(2,exp1);
	decfp2*=pow(2,exp2);//cout<<decfp1<<" "<<decfp2<<endl;
	char ans[100];
	if(compute==1)// +
	{	
		sprintf(ans,"%lf",decfp1+decfp2);
		return Float(ans,10);
	}
	else if(compute==2)// -
	{
		sprintf(ans,"%lf",decfp1-decfp2);//cout<<ans<<endl;
		return Float(ans,10);
	}
	else if(compute==3)// *
	{
		sprintf(ans,"%lf",decfp1*decfp2);
		return Float(ans,10);
	}
	else if(compute==4)// /
	{
		sprintf(ans,"%lf",decfp1/decfp2);
		return Float(ans,10);
	}
}

string Num::DoubleCompute(char *number1,char *number2,int source,int compute)
{
	string fp1=Double(number1,source),fp2=Double(number2,source);
	double decfp1=1,decfp2=1;
	int exp1=strtol((char *)fp1.substr(1,11).c_str(),NULL,2)-1023;
	int exp2=strtol((char *)fp2.substr(1,11).c_str(),NULL,2)-1023;//cout<<exp1<<" "<<exp2<<endl;
	for(int i=12;i<=63;i++)
	{
		decfp1+=(fp1[i]-'0')*pow(2,-i+11);
		decfp2+=(fp2[i]-'0')*pow(2,-i+11);
	}
	if(fp1[0]=='1')decfp1*=-1;
	if(fp2[0]=='1')decfp2*=-1;
	decfp1*=pow(2,exp1);
	decfp2*=pow(2,exp2);//cout<<decfp1<<" "<<decfp2<<endl;
	char ans[100];
	if(compute==1)// +
	{	
		sprintf(ans,"%lf",decfp1+decfp2);
		return Double(ans,10);
	}
	else if(compute==2)// -
	{
		sprintf(ans,"%lf",decfp1-decfp2);
		return Double(ans,10);
	}
	else if(compute==3)// *
	{
		sprintf(ans,"%lf",decfp1*decfp2);
		return Double(ans,10);
	}
	else if(compute==4)// /
	{
		sprintf(ans,"%lf",decfp1/decfp2);//cout<<ans<<endl;
		return Double(ans,10);
	}
}





//浮点数转换的接口函数
void intDec(char* number, char* source, char* output)//转十进制型
{
	Num n;
	string out = n.Dec(number, source);
	const char* out1 = out.data();
	strcpy(output, out1);
}

void intFloat(char* number, char* source, char* output)//转float型
{
	Num n;
	string out = n.Dec(number, source);
	const char* out1 = out.data();
	string out2 = n.Float((char*)out1, 10);
	const char* out3 = out2.data();
	strcpy(output, out3);
}

void intDouble(char* number, char* source, char* output)//转double型
{
	Num n;
	string out = n.Dec(number, source);
	const char* out1 = out.data();
	string out2 = n.Double((char*)out1, 10);
	const char* out3 = out2.data();
	strcpy(output, out3);
}

//浮点数运算的接口函数
void decCompute(char* number1, char* number2, char* source, int compute, char* output) {
	Num n;
	string out = n.DecCompute(number1, number2, source, compute);
	const char* out1 = out.data();
	strcpy(output, out1);
}

void doubleCompute(char* number1, char* number2, char* source, int compute, char* output) {
	Num n;
	string num1=n.Dec(number1,source),num2=n.Dec(number2,source);
	string out = n.DoubleCompute((char*)num1.c_str(), (char*)num2.c_str(), 10, compute);
	const char* out1 = out.data();
	strcpy(output, out1);
}

void floatCompute(char* number1, char* number2, char* source, int compute, char* output) {
	Num n;
	string num1=n.Dec(number1,source),num2=n.Dec(number2,source);
	string out = n.FloatCompute((char*)num1.c_str(), (char*)num2.c_str(), 10, compute);
	const char* out1 = out.data();
	strcpy(output, out1);
}



int main()
{
	char s[100];
	intFloat("-0.5","10",s);
	cout<<s<<endl;
	return 0;
}