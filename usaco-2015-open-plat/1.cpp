#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

void Multiply2 (string &s)
{
	string r;
	int carry = 0;
	for (int a = 0, b;a < s.length ();a++)
	{
		b = (s[a] - '0') * 2 + carry * 10;
		r += (char)(b / 10 + '0');
		b %= 10;
		carry = b;
	}
	s = r + (char)(carry + '0');

	if (s[0] == '0')
		s = s.substr (1, s.length () - 1);
}

void Exp2 (string &s, int k)
{
	for (int a = 0;a < k;a++)
		Multiply2 (s);
}

void Sub1 (string &s)
{
	for (int a = s.length () - 1;a >= 0;a--)
	{
		if (s[a] != '0')
		{
			s[a] -= 1;
			break;
		}
		s[a] = '9';
	}

	if (s[0] == '0')
		s = s.substr (1, s.length () - 1);
}

void Sub2 (string &s)
{
	Sub1 (s);
	Sub1 (s);
}

string Add (string &x, string &y)
{
	int a = 1, b = max (x.length (), y.length ());
	string r;
	int dig1, dig2, carry = 0;
	for (;a <= b;a++)
	{
		if (a > x.length ())
			dig1 = 0;
		else
			dig1 = x[x.length () - a] - '0';
		if (a > y.length ())
			dig2 = 0;
		else
			dig2 = y[y.length () - a] - '0';
		carry += dig1 + dig2;
		r += (char)(carry % 10 + '0');
		carry /= 10;
	}

	if (carry != 0)
		r += (char)(carry + '0');

	reverse (r.begin (), r.end ());
	return r;
}

int Div2 (string &s)
{
	int carry = 0, dig;
	for (int a = 0;a < s.length ();a++)
	{
		dig = carry * 10 + s[a] - '0';
		s[a] = (char)(dig / 2 + '0');
		carry = dig % 2;
	}
	
	if (s[0] == '0')
		s = s.substr (1, s.length () - 1);

	return carry;
}

string ConBin (string s)
{
	string r;

	while (s != "")
	{
		r += (char)(Div2 (s) + '0');
	}

	reverse (r.begin (), r.end ());
	return r;
}

string Sub (string &x, string &y)
{
	int a = 1, b = x.length ();
	string r;
	int dig1, dig2, carry = 0, t;
	for (;a <= b;a++)
	{
		dig1 = x[x.length () - a] - '0';
		if (a > y.length ())
			dig2 = 0;
		else
			dig2 = y[y.length () - a] - '0';
		t = dig1 - dig2 - carry;
		if (t < 0)
			t += 10,
			carry = 1;
		else
			carry = 0;
		r += (char)(t + '0');
	}

	int cnt = 0;
	for (int a = r.length() - 1;a >= 0;a--, cnt++)
		if (r[a] != '0')
			break;

	r = r.substr (0, r.length () - cnt);

	reverse (r.begin (), r.end ());
	
	return r;
}

int main ()
{
	/*
	string a = "1", b = "0000000000000000000000031";
	Exp2 (a, 332);
	cout << Div2 (a) << " " << a << " ";
	cout << Add (a, b) << " " << a;
	cin.get ();
	return 0;
	*/
	ios_base::sync_with_stdio (false);

	//std::freopen ("file_name.in", "r", stdin);
	//std::freopen ("file_name.out", "w", stdout);

	string x, y = "1";
	int mlvl = 0;
	while (y != "0")
	{
		mlvl++;
		cout << y << "\n";
		cin >> x >> y;
	}

	x = "1";
	int llvl = 0;
	while (x != "0")
	{
		llvl++;
		cout << x << "\n";
		cin >> x >> y;
	}

	if (llvl == mlvl)
	{
		string one = "1";
		Exp2 (one, mlvl);
		Sub1 (one);
		cout << "Answer " << one << "\n";
		return 0;
	}

	//cout << "Answer " << mlvl << "\n";
	//return 0;

	string low = "1", high = "1", mid, bin, t, k, orig;
	//mlvl = 15;
	Exp2 (low, mlvl);
	Exp2 (high, mlvl + 1);
	//Sub2 (high);
	orig = low;
	while (true)
	{
		mid = Add (low, high);
		Div2 (mid);

		if (mid == low)
			break;

		k = Sub (mid, orig);
		bin = ConBin (k);

		x = y = "1";
		if (bin.length () < mlvl)
		{
			//if (bin.length () == mlvl)
			//	bin = bin[0] + string (llvl - bin.length (), '0') + bin.substr (1, bin.length () - 1);
			//else
				bin = string (mlvl - bin.length (), '0') + bin;
		}

		for (int a = bin.length ();a > 0;a--)
		{
			if (a == bin.length () || bin[a] == '0')
				cout << x << "\n";
			else
				cout << y << "\n";
			cin >> x >> y;
		}

		if (bin[0] == '0')
			t = x;
		else
			t = y;

		if (t == "0")
			high = mid;
		else
			low = mid;
	}

	cout << "Answer " << low << "\n";

	return 0;
}