#define _CRT_SECURE_NO_WARNINGS

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

void SetUsed (bool (*att)[8], int r, int c)
{
	if (r < 0 || r >= 8 || c < 0 || c >= 8)
		return;
	att[r][c] = true;
}

bool IsOcc (bool (*occ)[8], int r, int c)
{
	if (r < 0 || r >= 8 || c < 0 || c >= 8)
		return true;
	return occ[r][c];
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.in", "r", stdin);
	freopen ("output.out", "w", stdout);
#endif

	int kn[8][2] = {{1, -2},{2, -1},{2, 1},{1, 2},{-1, 2},{-2, 1},{-2, -1},{-1, -2}};

	while (true)
	{
		bool att[8][8], occ[8][8];
		memset (att, 0, sizeof (att));
		memset (occ, 0, sizeof (occ));

		string s;
		getline (cin, s);

		if (s.length () < 5)
			break;

		int cr, cc;
		cr = cc = 0;
		for (int a = 0; a < s.length (); a++)
		{
			if (s[a] == '/')
				cr++, cc = 0;
			else if (s[a] >= '0' && s[a] <= '9')
				cc += s[a] - '0';
			else
				occ[cr][cc] = true,
				cc++;
		}
		cr = cc = 0;
		for (int a = 0;a < s.length ();a++)
		{
			if (s[a] == '/')
				cr++, cc = 0;
			else if (s[a] >= '0' && s[a] <= '9')
				cc += s[a] - '0';
			else
			{
				char k = tolower (s[a]);
				att[cr][cc] = true;

				if (s[a] == 'P')
					SetUsed (att, cr - 1, cc - 1), SetUsed (att, cr - 1, cc + 1);
				else if (s[a] == 'p')
					SetUsed (att, cr + 1, cc - 1), SetUsed (att, cr + 1, cc + 1);
				else if (k == 'n')
				{
					for (int b = 0;b < 8;b++)
						SetUsed (att, cr + kn[b][0], cc + kn[b][1]);
				}
				else if (k == 'b')
				{
					for (int b = 1;b <= 8;b++)
					{
						SetUsed (att, cr + b, cc + b);
						if (IsOcc (occ, cr + b, cc + b))
							break;
					}
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr + b, cc - b);
						if (IsOcc (occ, cr + b, cc - b))
							break;
					}
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr - b, cc + b);
						if (IsOcc (occ, cr - b, cc + b))
							break;
					}
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr - b, cc - b);
						if (IsOcc (occ, cr - b, cc - b))
							break;
					}
				}
				else if (k == 'r')
				{
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr, cc + b);
						if (IsOcc (occ, cr, cc + b))
							break;
					}
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr + b, cc);
						if (IsOcc (occ, cr + b, cc))
							break;
					}
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr, cc - b);
						if (IsOcc (occ, cr, cc - b))
							break;
					}
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr - b, cc);
						if (IsOcc (occ, cr - b, cc))
							break;
					}
				}
				else if (k == 'q')
				{
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr + b, cc + b);
						if (IsOcc (occ, cr + b, cc + b))
							break;
					}
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr + b, cc - b);
						if (IsOcc (occ, cr + b, cc - b))
							break;
					}
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr - b, cc + b);
						if (IsOcc (occ, cr - b, cc + b))
							break;
					}
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr - b, cc - b);
						if (IsOcc (occ, cr - b, cc - b))
							break;
					}
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr, cc + b);
						if (IsOcc (occ, cr, cc + b))
							break;
					}
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr + b, cc);
						if (IsOcc (occ, cr + b, cc))
							break;
					}
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr, cc - b);
						if (IsOcc (occ, cr, cc - b))
							break;
					}
					for (int b = 1; b <= 8; b++)
					{
						SetUsed (att, cr - b, cc);
						if (IsOcc (occ, cr - b, cc))
							break;
					}
				}
				else if (k == 'k')
				{
					for (int b = 1; b <= 1; b++)
						SetUsed (att, cr + b, cc + b),
						SetUsed (att, cr + b, cc - b),
						SetUsed (att, cr - b, cc + b),
						SetUsed (att, cr - b, cc - b);
					for (int b = 1; b <= 1; b++)
						SetUsed (att, cr, cc + b),
						SetUsed (att, cr + b, cc),
						SetUsed (att, cr, cc - b),
						SetUsed (att, cr - b, cc);
				}
				cc++;
			}
		}

		int ans = 0;
		for (int a = 0;a < 8;a++)
			for (int b = 0;b < 8;b++)
				ans += !att[a][b];

		cout << ans << "\n";
	}

	return 0;
}