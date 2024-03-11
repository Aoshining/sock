#include "Vector.h"

int main()
{
	Vector<int> a;//test Default Ctor
	cout << "Initialize Vector::a" << endl;
	a.push_back(1);//test push_back()
	cout << "Push 1 into a" << endl;
	Vector<int> b(10);//test Ctor
	cout << "Initialize Vector::b(10)" << endl;
	b=a;//test assignment operator
	cout << "Make b = a" << endl;
	Vector<int> c(a);//test Copy Ctor
	cout << "Initialize Vector::c(a)" << endl;
	cout << "c comes from Copy Ctor of a" << endl;
	
	cout << "b[0] is " << b[0] << endl;
	cout << "c[0] is " << c[0] << endl;
	cout << "The size of a is " << a.size() << endl;//test size()

	a.clear();//test clear()
	cout << "After a.clear(), the size of a is " << a.size() << endl;
	cout << "a is empty: " << (a.empty()?"Yes":"No") << endl;//test empty()
	cout << "b is empty: " << (b.empty()?"Yes":"No") << endl;
	cout << "c is empty: " << (c.empty()?"Yes":"No") << endl;

	cout << "a[10] is " << a.at(10) << endl;//test at()
	return 0;
}

