#include <string>
#include <iostream>
#include <cstring>
using namespace std;

int main ()
{
	freopen ("in.txt", "r", stdin); freopen ("out.txt", "w", stdout);
	string s;
	cin >> s;
	for (int a = 0;a < s.length ();a++)
		s[a] -= '0';
	string x = s;

	bool dual[1000];
	memset (dual, 0, sizeof (dual));

	for (int a = 1;a < s.length ();a++)
	{
		if (!dual[a - 1])
		{
			if (s[a] % 2 != s[a - 1] % 2)
				;
			else
			{
				if (s[a] == 0)
					s[a] = 1;
				else if (s[a] == 9)
					s[a] = 8;
				else
					dual[a] = true;
			}
		}
		else
		{
			if (s[a] % 2 == s[a - 1] % 2)
				;
			else
			{
				if (s[a] == 0)
					s[a] = 1;
				else if (s[a] == 9)
					s[a] = 8;
				else
					dual[a] = true;
			}
		}
	}

	string n1, n2;

	n1 = n2 = s;

	bool pos2 = true, slant = 0; //slant in lower direction
	for (int a = s.length () - 1;a > 0;a--)
	{
		if (dual[a])
		{
			if (slant == 0)
				n1[a] = s[a] + 1;
			else
				n1[a] = s[a] - 1;
			slant = !slant;
		}
		else
		{
			if (s[a] != x[a])
				pos2 = false;
			n1[a] = s[a];
			if (s[a] > x[a])
				slant = 1;
			else if (s[a] < x[a])
				slant = 0;
		}
		n1[a] += '0';
	}

	n1[0] = s[0] + '0';

	if (!pos2)
		cout << n1;
	else
	{
		for (int a = 0;a < s.length ();a++)
		{
			if (dual[a])
				n2[a] = '0' + (2 * s[a] - (n1[a] - '0'));
			else
				n2[a] = n1[a];
		}
		if (n1 != n2) //no duals
			cout << min (n1, n2) << " " << max (n1, n2);
		else
			cout << n1;
	}

	return 0;
}