#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int cmp(string a, string b)
{
	if (a.length() < b.length())
		return -1;
	else if (a.length() > b.length())
		return 1;
	else
	{
		for (int i = 0; i < a.length(); i++)
		{
			if (a[i] < b[i])
				return -1;
			else if (a[i] > b[i])
				return 1;
		}
		return 0;
	}
}

string sub(string a, string b)
{
	vector<int> na, nb;
	for (int i = 0; i < a.length(); i++)
		na.push_back(a[a.length()-1-i]-'0');
	for (int i = 0; i < b.length(); i++)
		nb.push_back(b[b.length()-1-i]-'0');
	int negative = 0;
	if (cmp(a, b) == -1)
	{
		vector<int> temp = na;
		na = nb;
		nb = temp;
		negative = 1;
	}
	int length = max(a.length(), b.length());
	for (int i = 0; i < min(a.length(), b.length()); i++)
	{
		if (na[i] < nb[i])
		{
			na[i + 1]--;
			na[i] = na[i] + 10 - nb[i];
		}
		else
			na[i] -= nb[i];
	}
	while (length && na[--length] == 0);
	string res;
	for (int j = 0; j <= length; j++)
		res.insert(0, 1, na[j] + '0');
	if (negative)
		res.insert(0, 1, '-');
	return res;
}

string mult(string a, string b)
{
	vector<int> na, nb;
	for (int i = 0; i < a.length(); i++)
		na.push_back(a[a.length()-1-i]-'0');
	for (int i = 0; i < b.length(); i++)
		nb.push_back(b[b.length()-1-i]-'0');
	if (a.length() < b.length())
	{
		vector<int> temp = na;
		na = nb;
		nb = temp;
	}
	int length = a.length() + b.length();
	vector<int> nc(length);
	for (int i = 0; i < nb.size(); i++)
	{
		int carry = 0;
		for (int j = 0; j < na.size(); j++)
		{
			nc[i + j] += na[j] * nb[i] + carry;
			carry = nc[i + j] / 10;
			nc[i + j] %= 10;
		}
		if (carry)
			nc[i + na.size()] = carry;
	}
	while (length && nc[--length] == 0);
	string res;
	for (int j = 0; j <= length; j++)
		res.insert(0, 1, nc[j] + '0');
	return res;
}

string mod(string a, string b)
{
	if (cmp(a, b) <= 0)
		return a;
	string suba = a.substr(0, b.length());
	for (int i = b.length() - 1; i < a.length(); i++)
	{
		if (i != b.length() - 1)
		{
			if(suba == "0")
				suba = a[i];
			else
				suba += a[i];
		}
		while (cmp(suba, b) >= 0)
			suba = sub(suba, b);
	}
	return suba;
}

string uk(string p, string g, string rk)
{
	string pub = g;
	int n = log(atoi(rk.c_str())) / log(2);
	int dif = atoi(rk.c_str()) - pow(2, n);
	for (int i = 0; i < n; i++)
		pub = mult(pub, pub);
	for (int i = 0; i < dif; i++)
		pub = mult(pub, g);
	return mod(pub, p);
}

int main()
{
	string p, g, a, b;
	cin >> p >> g >> a >> b;
	string A = uk(p, g, a), B = uk(p, g, b), K = uk(p, A, b);
	cout << A << endl;
	cout << B << endl;
	cout << K << endl;
	return 0;
}