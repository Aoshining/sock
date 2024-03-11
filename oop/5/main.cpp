#include "Fraction.h"

using namespace std;

int main()
{
	Fraction f1,f2;
    cin >> f1 >> f2;
    cout << "f1 + f2 = " << f1 + f2 << endl;
	cout << "f1 - f2 = " << f1 - f2 << endl;
    cout << "f1 * f2 = " << f1 * f2 << endl;
	cout << "f1 / f2 = " << f1 / f2 << endl;
	cout << "f1 <  f2 : " << (f1 < f2?"True":"False") << endl;
	cout << "f1 <= f2 : " << (f1 <= f2?"True":"False") << endl;
    cout << "f1 == f2 : " << (f1 == f2?"True":"False") << endl;
	cout << "f1 != f2 : " << (f1 != f2?"True":"False") << endl;
	cout << "f1 >= f2 : " << (f1 >= f2?"True":"False") << endl;
	cout << "f1 >  f2 : " << (f1 > f2?"True":"False") << endl;
    return 0;
}