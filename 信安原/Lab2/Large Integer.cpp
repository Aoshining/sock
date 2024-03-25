#include <iostream>
#include <vector>

using namespace std;

//default non-negative

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

string add(string a, string b)
{
	vector<int> na, nb;
	for (int i = 0; i < a.length(); i++)
		na.push_back(a[a.length()-1-i]-'0');
	for (int i = 0; i < b.length(); i++)
		nb.push_back(b[b.length()-1-i]-'0');
	if (cmp(a, b) == -1)
	{
		vector<int> temp = na;
		na = nb;
		nb = temp;
	}
	int length = min(a.length(), b.length());
	int carry = 0;
	int i;
	for (i = 0; i < length; i++)
	{
		na[i] += nb[i] + carry;
		carry = na[i] / 10;
		na[i] %= 10;
	}
	while(carry)
	{
		if (i >= na.size())
		{
			na.push_back(1);
			break;
		}
		na[i] += carry;
		carry = na[i] / 10;
		na[i] %= 10;
		i++;
	}
	string res;
	for (int j = 0; j < na.size(); j++)
		res.insert(0, 1, na[j] + '0');
	return res;
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

string div(string a, string b)
{
	if (cmp(a, b) == -1)
		return "0";
	string quo;
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
		quo.insert(0, 1, '0');
		while (cmp(suba, b) >= 0)
		{
			suba = sub(suba, b);
			quo[0]++;
		}
	}
	int length = quo.length();
	while (length && quo[--length] == '0');
	quo = quo.substr(0, length + 1);
	return string(quo.rbegin(), quo.rend());
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

int main()
{
	string a, b;
	cin >> a >> b;
	cout << add(a, b) << endl;
	cout << sub(a, b) << endl;
	cout << mult(a, b) << endl;
	cout << div(a, b) << endl;
	cout << mod(a, b) << endl;
	return 0;
}