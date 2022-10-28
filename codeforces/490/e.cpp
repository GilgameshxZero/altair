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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n;
	bool flag;
	vector<string> s;
	string t;
	
	cin >> n;
	s.resize (n + 1);
	for (int a = 1;a <= n;a++)
	{
		cin >> s[a];
		if (s[a].size () < s[a - 1].size ())
		{
			cout << "NO";
			return 0;
		}
	}

	s[0] = "";
	for (int a = 1;a <= n;a++)
	{
		if (s[a].length () > s[a - 1].length ())
		{
			if (s[a][0] == '?')
				s[a][0] = '1';
			for (int b = 0;b < s[a].length ();b++)
				if (s[a][b] == '?')
					s[a][b] = '0';
		}
		else //equal length
		{
			t = s[a];
			flag = true;
			for (int b = 0, c;b < t.length ();b++)
			{
				if (t[b] == '?')
				{
					if (flag)
						t[b] = s[a - 1][b];
					else
						t[b] = '0';
				}
				else if (t[b] > s[a - 1][b])
					flag = false;
				else if (t[b] < s[a - 1][b] && flag) //increase last ? digit
				{
					c = b;
					while (c >= 0)
					{
						if (s[a][c] == '?')
						{
							t[c]++;
							if (t[c] <= '9')
								break;
							t[c] = '0';
						}
						c--;
					}

					if (c == -1)
					{
						cout << "NO";
						return 0;
					}

					flag = false;
				}
			}

			if (flag) //still equal
			{
				int b = t.length () - 1;
				while (b >= 0)
				{
					if (s[a][b] == '?')
					{
						t[b]++;
						if (t[b] <= '9')
							break;
						t[b] = '0';
					}
					b--;
				}

				if (b == -1)
				{
					cout << "NO";
					return 0;
				}
			}

			s[a] = t;
		}
	}

	cout << "YES\n";
	for (int a = 1;a <= n;a++)
		cout << s[a] << "\n";

	return 0;
}