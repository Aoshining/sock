#include <stdio.h>

char v[100][100];//the names of variables
int vid=0;//the number of variables
char ep[1000];//mathematical expression
int flag;//determine if the expression has been simplified

int cmp(char a,char b)//set and compare the priority of operators: '^' > '*' = '/' > '+' = '-' > ',' > '('
{
	int wa,wb;
	if(a=='^')wa=3;
	else if(a=='*'||a=='/')wa=2;
	else if(a=='+'||a=='-')wa=1;
	else if(a==',')wa=0;
	else if(a=='(')wa=-1;
	if(b=='^')wb=3;
	else if(b=='*'||b=='/')wb=2;
	else if(b=='+'||b=='-')wb=1;
	else if(b==',')wb=0;
	else if(b=='(')wb=-1;
	return wa<=wb?1:0;
}

struct Node;
typedef struct Node* Stack;//set the struct of the tree & stack
struct Node
{
	char op[100];//the name of operators and variables
	int lable;//the lable of mathematical functions:ln--1 log--2 pow--3 exp--4 sin--5 cos--6 tan--7
	Stack next;//next node
	Stack l;//left child node
	Stack r;//right child node
};

void Push(char x[],Stack S)//push the string onto the stack
{
    Stack tmp=malloc(sizeof(struct Node));
	tmp->l=NULL;
	tmp->r=NULL;
    strcpy(tmp->op,x);
	tmp->lable=0;
    tmp->next=S->next;
    S->next=tmp;
}

void Pushnode(Stack x,Stack S)//push the node onto the stack
{
	x->next=S->next;
	S->next=x;
}

void Pop(Stack S)
{
    S->next=S->next->next;
}

void cmb(Stack S1,Stack S2)//combine S1 and S2
{
	Stack tmp=malloc(sizeof(struct Node));
	strcpy(tmp->op,S2->next->op);//take the top node of the S2 stack as the parent node
	Pop(S2);
	tmp->lable=0;
	tmp->r=S1->next;//take the top two nodes of the S1 stack as the right and left child nodes respectively
	if(S1->next)Pop(S1);
	tmp->l=S1->next;
	if(S1->next)Pop(S1);
	Pushnode(tmp,S1);//push the composed binary tree onto the S1 stack
}

int isdigit(char num[])//determine if the string consists of numbers
{
	for(int i=0;i<strlen(num);i++)
		if(!(num[i]>='0'&&num[i]<='9'))return 0;
	return 1;
}

int exist(char num[],char v[][100])//determine if the variable name has been recorded
{
	for(int i=0;i<vid;i++)
		if(strcmp(num,v[i])==0)return 1;
	return 0;
}

Stack bigmathtree(Stack t,int lable)//using 1 * (the nested math functions) to deal with the root node of subtree
{
	Stack T=malloc(sizeof(struct Node));
	strcpy(T->op,"*");
	T->r=t;
	T->lable=lable;
	T->l=malloc(sizeof(struct Node));
	strcpy(T->l->op,"1");
	T->l->lable=0;
	T->l->l=NULL;
	T->l->r=NULL;
	return T;
}

Stack mathtree()//generate separate subtree for expressions within mathematical functions
{
	Stack S1=malloc(sizeof(struct Node));//store variables and constants
	Stack S2=malloc(sizeof(struct Node));//store operators
	S1->next=NULL;
	S2->next=NULL;
	char s[100]="(";
	Push(s,S2);
	int bracket=1;//record whether nested brackets occur
	char ch=getchar();
	while(ch!=')'||bracket!=1)//read until the end of the math expression
	{
		if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch>='0'&&ch<='9')
		//read data in the same way as the following function createtree()
		{
			char num[100];
			int id=0;
			num[id++]=ch;
			ch=getchar();
			while(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch>='0'&&ch<='9')
			{
				num[id++]=ch;
				ch=getchar();
			}
			num[id]='\0';

			if(strcmp(num,"ln")==0||strcmp(num,"log")==0||strcmp(num,"sin")==0||strcmp(num,"cos")==0||strcmp(num,"tan")==0||strcmp(num,"pow")==0||strcmp(num,"exp")==0)
			//if a mathematical function is scanned, a separate subtree is generated.
			{
				Stack t=mathtree();
				if(strcmp(num,"ln")==0)
				{
					if(t->lable!=0)//the case of nested mathematical functions
						t=bigmathtree(t,1);
					else t->lable=1;
				}
				else if(strcmp(num,"log")==0)
				{
					if(t->lable!=0)
						t=bigmathtree(t,2);
					else t->lable=2;
				}
				else if(strcmp(num,"pow")==0)
				{
					if(t->lable!=0)
						t=bigmathtree(t,3);
					else t->lable=3;
				}
				else if(strcmp(num,"exp")==0)
				{
					if(t->lable!=0)
						t=bigmathtree(t,4);
					else t->lable=4;
				}
				else if(strcmp(num,"sin")==0)
				{
					if(t->lable!=0)
						t=bigmathtree(t,5);
					else t->lable=5;
				}
				else if(strcmp(num,"cos")==0)
				{
					if(t->lable!=0)
						t=bigmathtree(t,6);
					else t->lable=6;
				}
				else if(strcmp(num,"tan")==0)
				{
					if(t->lable!=0)
						t=bigmathtree(t,7);
					else t->lable=7;
				}
				Pushnode(t,S1);
				ch=getchar();
				continue;
			}
			if(!isdigit(num)&&!exist(num,v))strcpy(v[vid++],num);//determine if the variable name has been recorded or is a constant
			Push(num,S1);
		}
		else
		{
			if(ch=='(')//push the left bracket onto the stack directly
			{
				char s[100];
				s[0]=ch;
				s[1]='\0';
				Push(s,S2);
				bracket++;
			}
			else if(ch==')')//find the corresponding left bracket
			{
				while(S2->next->op[0]!='(')
					cmb(S1,S2);//perform a combining operation before finding
				Pop(S2);
				bracket--;
			}
			else
			{
				while(S2->next&&cmp(ch,S2->next->op[0]))
				//if the priority of the new operator is less than or equal to the priority of the S2 top-of-stack operator, then the combine operation is performed.
					cmb(S1,S2);
				char s[100];
				s[0]=ch;
				s[1]='\0';
				Push(s,S2);
			}
			ch=getchar();
		}
	}
	while(S2->next->op[0]!='(')//read until the beginning of the math expression
		cmb(S1,S2);
	return S1->next;
}

Stack createtree()
{
	char ch=getchar();
	Stack S1=malloc(sizeof(struct Node));//store variables and constants
	Stack S2=malloc(sizeof(struct Node));//store operators
	S1->next=NULL;
	S2->next=NULL;
	while(ch!='\n')
	{
		if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch>='0'&&ch<='9')
		//The following comment details are similar to the above function mathtree().
		{
			char num[100];
			int id=0;
			num[id++]=ch;
			ch=getchar();
			while(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch>='0'&&ch<='9')
			{
				num[id++]=ch;
				ch=getchar();
			}
			num[id]='\0';

			if(strcmp(num,"ln")==0||strcmp(num,"log")==0||strcmp(num,"sin")==0||strcmp(num,"cos")==0||strcmp(num,"tan")==0||strcmp(num,"pow")==0||strcmp(num,"exp")==0)
			{
				Stack t=mathtree();
				if(strcmp(num,"ln")==0)
				{
					if(t->lable!=0)
						t=bigmathtree(t,1);
					else t->lable=1;
				}
				else if(strcmp(num,"log")==0)
				{
					if(t->lable!=0)
						t=bigmathtree(t,2);
					else t->lable=2;
				}
				else if(strcmp(num,"pow")==0)
				{
					if(t->lable!=0)
						t=bigmathtree(t,3);
					else t->lable=3;
				}
				else if(strcmp(num,"exp")==0)
				{
					if(t->lable!=0)
						t=bigmathtree(t,4);
					else t->lable=4;
				}
				else if(strcmp(num,"sin")==0)
				{
					if(t->lable!=0)
						t=bigmathtree(t,5);
					else t->lable=5;
				}
				else if(strcmp(num,"cos")==0)
				{
					if(t->lable!=0)
						t=bigmathtree(t,6);
					else t->lable=6;
				}
				else if(strcmp(num,"tan")==0)
				{
					if(t->lable!=0)
						t=bigmathtree(t,7);
					else t->lable=7;
				}
				Pushnode(t,S1);
				ch=getchar();
				continue;
			}
			if(!isdigit(num)&&!exist(num,v))strcpy(v[vid++],num);
			Push(num,S1);
		}
		else
		{
			if(ch=='(')
			{
				char s[100];
				s[0]=ch;
				s[1]='\0';
				Push(s,S2);
			}
			else if(ch==')')
			{
				while(S2->next->op[0]!='(')
					cmb(S1,S2);
				Pop(S2);
			}
			else
			{
				while(S2->next&&cmp(ch,S2->next->op[0]))
					cmb(S1,S2);
				char s[100];
				s[0]=ch;
				s[1]='\0';
				Push(s,S2);
				
			}
			ch=getchar();
		}
	}
	while(S1->next->next)//read until there is only one node left in S1
		cmb(S1,S2);
	return S1->next;
}

void sort(char v[][100])//output the name of variables in the lexicographical order by bubbling sort
{
	for(int i=vid-1;i>0;i--)
	{
		int flag=0;
		for(int j=0;j<i;j++)
		{
			if(strcmp(v[j],v[j+1])>0)
			{
				char tmp[100];
				strcpy(tmp,v[j+1]);
				strcpy(v[j+1],v[j]);
				strcpy(v[j],tmp);
				flag=1;
			}
		}
		if(flag==0)return;//optimize sorting algorithm
	}
}

void input(char add[])//fill the expression string with characters
{
	strcat(ep,add);
}

void inorder(Stack T)//inorder traversal the current tree
{
	if(T)
	{
		if(T->lable==1)input("ln(");//add different prefixes and suffixes depending on the label
		if(T->lable==2)input("log(");
		if(T->lable==4)input("e^(");
		if(T->lable==5)input("sin(");
		if(T->lable==6)input("cos(");
		if(T->lable==7)input("tan(");
		inorder(T->l);
		input(T->op);
		inorder(T->r);
		if(T->lable!=0&&T->lable!=3)input(")");
	}
}

int find(char s[],char target[])//return the index of the first character of the substring in the original string
{
	return strlen(s)-strlen(strstr(s,target));
}

void delbracket(char s[])//delete redundant brackets
{
	//protect the brackets that come with math functions by replacing brackets with other characters
	while(strstr(s,"ln"))
	{
		int ids=find(s,"ln")+2;
		s[ids-2]='?';
		s[ids-1]='?';
		s[ids]='$';
		while(s[ids]!=')')
		{
			if(s[ids]=='(')//skip nested brackets
			{
				int count=1;
				ids++;
				while(s[ids]!=')'||count!=1)
				{
					if(s[ids]=='(')count++;
					if(s[ids]==')')count--;
					ids++;
				}
			}
			ids++;
		}
		s[ids]='`';
	}

	while(strstr(s,"log"))
	{
		int ids=find(s,"log")+3;
		s[ids-3]='~';
		s[ids-2]='~';
		s[ids-1]='~';
		s[ids]='$';
		while(s[ids]!=')')
		{
			if(s[ids]=='(')
			{
				int count=1;
				ids++;
				while(s[ids]!=')'||count!=1)
				{
					if(s[ids]=='(')count++;
					if(s[ids]==')')count--;
					ids++;
				}
			}
			ids++;
		}
		s[ids]='`';
	}

	while(strstr(s,"sin"))
	{
		int ids=find(s,"sin")+3;
		s[ids-3]='!';
		s[ids-2]='!';
		s[ids-1]='!';
		s[ids]='$';
		while(s[ids]!=')')
		{
			if(s[ids]=='(')
			{
				int count=1;
				ids++;
				while(s[ids]!=')'||count!=1)
				{
					if(s[ids]=='(')count++;
					if(s[ids]==')')count--;
					ids++;
				}
			}
			ids++;
		}
		s[ids]='`';
	}

	while(strstr(s,"cos"))
	{
		int ids=find(s,"cos")+3;
		s[ids-3]='@';
		s[ids-2]='@';
		s[ids-1]='@';
		s[ids]='$';
		while(s[ids]!=')')
		{
			if(s[ids]=='(')
			{
				int count=1;
				ids++;
				while(s[ids]!=')'||count!=1)
				{
					if(s[ids]=='(')count++;
					if(s[ids]==')')count--;
					ids++;
				}
			}
			ids++;
		}
		s[ids]='`';
	}

	while(strstr(s,"tan"))
	{
		int ids=find(s,"tan")+3;
		s[ids-3]=';';
		s[ids-2]=';';
		s[ids-1]=';';
		s[ids]='$';
		while(s[ids]!=')')
		{
			if(s[ids]=='(')
			{
				int count=1;
				ids++;
				while(s[ids]!=')'||count!=1)
				{
					if(s[ids]=='(')count++;
					if(s[ids]==')')count--;
					ids++;
				}
			}
			ids++;
		}
		s[ids]='`';
	}

	int level[256]={0};//priority correspondence table for deleting brackets
	level[',']=4;level['+']=1;level['-']=2;level['*']=3;level['/']=4;level['^']=5;
	struct stack
	{
		char c;
		int id;
		struct stack* next;
	};
	struct stack* S=malloc(sizeof(struct stack));
	S->next=NULL;
	for(int i=0;i<strlen(s);i++)
	{
		if(s[i]=='('||s[i]==','||s[i]=='+'||s[i]=='-'|| s[i]=='*'||s[i]=='/'||s[i]=='^')
		//operators are pushed onto the stack when encountered
		{
            struct stack* tmp=malloc(sizeof(struct stack));
			tmp->c=s[i];
			tmp->id=i;
			tmp->next=S->next;
			S->next=tmp;
        }
		else if(s[i]==')')
		{
			int min=10;
			while(S->next->c!='(')
			{
				//find the minimum operator precedence inside the brackets
				if(min>level[S->next->c])min=level[S->next->c];
				S->next=S->next->next;
			}
			int l=-1;
			int r=-1;
			if(i+1<strlen(s)&&s[i+1]!=')')
				r=level[s[i+1]];//record the priority of the operator to the left of the left bracket
			if(S->next->id-1>=0&&s[S->next->id-1]!='(')
				l=level[s[S->next->id-1]];//record the priority of the operator to the right of the right bracket
			if(min>=l&&min>=r)
			//if min is greater than or equal to both l and r, then the brackets can be removed.
			{
				s[i]=s[S->next->id]='#';
				flag=1;
			}
			else if((min==1&&r==2&&l<=1)||(min==3&&r==4&&l<=3))
			//special cases judgment
			{
                s[i]=s[S->next->id]='#';
				flag=1;
            }
            S->next=S->next->next;
		}
	}
	while(strstr(s,"#"))//delete redundant brackets
	{
		int id=find(s,"#");
		strcpy(s+id,s+1+id);
	}

	//restore protected brackets and math functions
	while(strstr(s,"$"))s[find(s,"$")]='(';
	while(strstr(s,"`"))s[find(s,"`")]=')';
	while(strstr(s,"??"))
	{
		int ids=find(s,"??");
		s[ids]='l';
		s[ids+1]='n';
	}
	while(strstr(s,"~~~"))
	{
		int ids=find(s,"~~~");
		s[ids]='l';
		s[ids+1]='o';
		s[ids+2]='g';
	}
	while(strstr(s,"!!!"))
	{
		int ids=find(s,"!!!");
		s[ids]='s';
		s[ids+1]='i';
		s[ids+2]='n';
	}
	while(strstr(s,"@@@"))
	{
		int ids=find(s,"@@@");
		s[ids]='c';
		s[ids+1]='o';
		s[ids+2]='s';
	}
	while(strstr(s,";;;"))
	{
		int ids=find(s,";;;");
		s[ids]='t';
		s[ids+1]='a';
		s[ids+2]='n';
	}
}

void del1(char s[])//delete redundant "1"
{
	while(strstr(s,"1"))
	{
		if(s[find(s,"1")+1]>='0'&&s[find(s,"1")+1]<='9'||s[find(s,"1")-1]>='0'&&s[find(s,"1")-1]<='9')
		//determine if the "1" here is part of a constant
		{
			s[find(s,"1")]='$';//if yes, protect it with other character
			continue;
		}

		//starting at "1", traverse left and right to determine where to delete.
		int idl=find(s,"1"),idr=find(s,"1")+1;
		if(idl-1>=0&&(s[idl-1]=='*'||s[idl-1]=='/'))idl--;
		if(idr<strlen(s)&&idl==idr-1&&s[idr]=='*')idr++;
		if(idl!=idr-1)
		{
			flag=1;
			strcpy(s+idl,s+idr);
		}
		else s[find(s,"1")]='$';
	}
	while(strstr(s,"$"))s[find(s,"$")]='1';//restore protected "1"
}

void del0(char s[])//delete redundant "0"
{
	while(strstr(s,"0"))
	{
		if(s[find(s,"0")+1]>='0'&&s[find(s,"0")+1]<='9'||s[find(s,"0")-1]>='0'&&s[find(s,"0")-1]<='9')
		//determine if the "0" here is part of a constant
		{
			s[find(s,"0")]='$';//if yes, protect it with other character
			continue;
		}

		flag=1;
		//starting at "0", traverse left and right to determine where to delete.
		int idl=find(s,"0"),idr=find(s,"0");
		while(idl>=0&&s[idl]!='+'&&(s[idl]!='-'||s[idl-1]=='(')&&s[idl]!='(')
		{
			if(s[idl]==')')//skip nested brackets
			{
				int count=1;
				idl--;
				while(s[idl]!='('||count!=1)
				{
					if(s[idl]==')')count++;
					if(s[idl]=='(')count--;
					idl--;
				}
			}	
			idl--;
		}
		while(idr<strlen(s)&&s[idr]!='+'&&(s[idr]!='-'||s[idr-1]=='(')&&s[idr]!=')')
		{
			if(s[idr]=='(')//skip nested brackets
			{
				int count=1;
				idr++;
				while(s[idr]!=')'||count!=1)
				{
					if(s[idr]=='(')count++;
					if(s[idr]==')')count--;
					idr++;
				}
			}
			idr++;
		}

		//categorize and discuss whether the characters at s[idl] and s[idr] are to be retained or not
		if(idl>=0&&idr<strlen(s))
		{
			if(s[idl]=='(')
			{
				if(s[idr]=='+')strcpy(s+idl+1,s+idr+1);
				else strcpy(s+idl+1,s+idr);//s[idr] is '-' or ')'
			}
			else strcpy(s+idl,s+idr);
		}
		else if(idl<0)
		{
			if(s[idr]=='+')strcpy(s,s+idr+1);
			else if(s[idr]==')')
			{
				s[idr]='0';
				strcpy(s,s+idr);
			}
			else strcpy(s,s+idr);
		}
		else if(idr>strlen(s)-1)strcpy(s+idl,"");
	}
	while(strstr(s,"()"))
	//replace "()" with "0" if it appears and delete redundant "0"
	{
		flag=1;
		int id=find(s,"()");
		strcpy(s+id,s+id+1);
		s[id]='0';
		del0(s);
	}
	while(strstr(s,"$"))s[find(s,"$")]='0';//restore protected "0"
}


void delas(char s[])//delete "+" in "+-"
{
	while(strstr(s,"+-"))
	{
		flag=1;
		int id=find(s,"+-");
		strcpy(s+id,s+id+1);
	}
}

void simplify(char s[])
{
	while(flag)//cyclize to the simplest form
	{
		flag=0;
		delbracket(s);
		del0(s);
		del1(s);
		delas(s);
	}
}

void Autograd(char s[],Stack T)//partially derive by tree
{
	if(T==NULL)return;
	char opr=T->op[0];
	char ops[100];
	strcpy(ops,T->op);
	if(T->lable==0)
	//determine if a math function is applied to the subtree here by label
	{
		if(opr=='+')
		{
			Autograd(s,T->l);
			input("+");
			Autograd(s,T->r);
		}
		else if(opr=='-')
		{
			Autograd(s,T->l);
			input("-");
			Autograd(s,T->r);
		}
		else if(opr=='*')
		{
			input("(");
			inorder(T->l);
			input(")*(");
			Autograd(s,T->r);
			input(")");
			input("+");
			input("(");
			Autograd(s,T->l);
			input(")*(");
			inorder(T->r);
			input(")");
		}
		else if(opr=='/')
		{
			input("((");
			Autograd(s,T->l);
			input(")*(");
			inorder(T->r);
			input(")");
			input("-");
			input("(");
			inorder(T->l);
			input(")*(");
			Autograd(s,T->r);
			input("))");
			input("/");
			input("(");
			inorder(T->r);
			input(")^2");
		}
		else if(opr=='^')
		{
			inorder(T->r);
			input("*");
			inorder(T->l);
			input("^(");
			inorder(T->r);
			input("-1)*(");
			Autograd(s,T->l);
			input(")+(");
			inorder(T);
			input(")*ln(");
			inorder(T->l);
			input(")*(");
			Autograd(s,T->r);
			input(")");
		}
		else if(strcmp(s,ops)==0)//The derivative of the independent variable with respect to itself is 1
		{
			input("1");
		}
		else//The derivative of other variables or constants with respect to the independent variable is 0
		{
			input("0");
		}
	}
	else
	{
		if(T->lable==1)//ln
		{
			T->lable=0;
			input("(");
			Autograd(s,T);
			input(")/(");
			inorder(T);
			input(")");
			T->lable=1;
		}
		else if(T->lable==2)//log
		{
			T->lable=0;
			input("(");
			Autograd(s,T->r);
			input(")/((");
			inorder(T->r);
			input(")*ln(");
			inorder(T->l);
			input("))-(");
			Autograd(s,T->l);
			input(")/((log(");
			inorder(T->r);
			input(",");
			inorder(T->l);
			input("))^2*(");
			inorder(T->l);
			input(")*ln(");
			inorder(T->r);
			input("))");
			T->lable=2;
		}
		else if(T->lable==3)//pow
		{
			T->lable=0;
			strcpy(T->op,"^");
			Autograd(s,T);
			T->lable=3;
		}
		else if(T->lable==4)//exp
		{
			T->lable=0;
			input("e^(");
			inorder(T);
			input(")*(");
			Autograd(s,T);
			input(")");
			T->lable=4;
		}
		else if(T->lable==5)//sin
		{
			T->lable=0;
			input("cos(");
			inorder(T);
			input(")*(");
			Autograd(s,T);
			input(")");
			T->lable=5;
		}
		else if(T->lable==6)//cos
		{
			T->lable=0;
			input("-sin(");
			inorder(T);
			input(")*(");
			Autograd(s,T);
			input(")");
			T->lable=6;
		}
		else if(T->lable==7)//tan
		{
			T->lable=0;
			input("(");
			Autograd(s,T);
			input(")/(");
			input("cos(");
			inorder(T);
			input("))^2");
			T->lable=7;
		}
	}
}

int main()
{
	Stack T=createtree();
	sort(v);
	for(int i=0;i<vid;i++)//output the partial derivatives of each variable in order
	{
		printf("%s: ",v[i]);
		strcpy(ep,"");
		Autograd(v[i],T);
		flag=1;
		simplify(ep);
		printf("%s\n",ep);//output the simplest expression
	}
	return 0;
}