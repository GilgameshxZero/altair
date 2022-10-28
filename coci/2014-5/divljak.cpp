#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

string bar[100000];
vector<int> ff[100000];
int cnt[100000];

int main ()
{
	//freopen ("in.txt", "r", stdin); freopen ("out.txt", "w", stdout);

	int N, Q;
	cin >> N;

	for (int a = 0;a < N;a++)
		cin >> bar[a];

	//find failure func for each barbarian string O(2e6)
	for (int k = 0;k < N;k++)
	{
		ff[k].resize (bar[k].length () + 1);
		ff[k][0] = ff[k][1] = 0;
		for (int a = 2, b;a < ff[k].size ();a++)
		{
			b = ff[k][a - 1];
			while (true)
			{
				if (bar[k][b] == bar[k][a - 1])
				{
					ff[k][a] = b + 1;
					break;
				}
				else if (b == 0)
				{
					ff[k][a] = 0;
					break;
				}
				else
					b = ff[k][b];
			}
		}
	}

	string s;
	cin >> Q;
	for (int k = 0, i, j;k < Q;k++)
	{
		cin >> i;
		if (i == 1)
		{
			cin >> s;

			for (int z = 0;z < N;z++)
			{
				for (int b = 0, c = 0;b < s.length ();)
				{
					if (s[b] == bar[z][c])
					{
						b++;
						c++;
						if (c == bar[z].length ())
						{
							cnt[z]++;
							break;
						}
					}
					else if (c != 0)
						c = ff[z][c];
					else
						b++;
				}
			}
		}
		else //i == 2
		{
			cin >> j;
			cout << cnt[j - 1] << "\n";
		}
	}

	return 0;
}