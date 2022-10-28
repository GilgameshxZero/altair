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

string paint[1000];
int alt[2][1000][1000], nalt[2][1000][1000];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n, m;
	cin >> n >> m;

	for (int a = 0;a < n;a++)
		cin >> paint[a];

	//precalc sums
	for (int a = 0;a < n;a++)
		alt[0][a][0] = paint[a][0] == 'X',
		nalt[0][a][0] = !alt[0][a][0];
	for (int a = 0;a < m;a++)
		alt[1][0][a] = paint[0][a] == 'X',
		nalt[1][0][a] = !alt[1][0][a];
	for (int a = 0;a < n;a++)
		for (int b = 1;b < m;b++)
			alt[0][a][b] = alt[0][a][b - 1] + (paint[a][b] == 'X'),
			nalt[0][a][b] = nalt[0][a][b - 1] + (paint[a][b] == '.');
	for (int a = 1;a < n;a++)
		for (int b = 0;b < m;b++)
			alt[1][a][b] = alt[1][a - 1][b] + (paint[a][b] == 'X'),
			nalt[1][a][b] = nalt[1][a - 1][b] + (paint[a][b] == '.');

	int total = 0;
	for (int a = 0;a < n;a++)
		for (int b = 0;b < m;b++)
			total += (paint[a][b] == 'X');

	int ans = 10000000;

	//find upperleftmost square
	int ulr, ulc;
	for (int a = 0;a < n;a++)
	{
		if (alt[0][a][m - 1] != 0)
		{
			for (int b = 0;b < m;b++)
			{
				if (paint[a][b] == 'X')
				{
					ulr = a;
					ulc = b;
					a = n;
					b = m;
				}
			}
		}
	}

	//test row down
	int len = 0;
	for (;paint[ulr][ulc + len] == 'X';len++);

	bool f1;
	for (int a = 0;a + ulr < n;a++)
	{
		if (len * a + len >= ans)
			continue;

		f1 = true;
		for (int b = 0;b < len;b++)
		{
			if (paint[a + ulr][b + ulc] == '.')
			{
				f1 = false;
				break;
			}
		}

		if (!f1)
			break;

		int cr = ulr, cc = ulc, squares = a * len + len;
		for (int b = 0;;b++)
		{
			//down
			if (squares > total)
				break;
			else if (cr + a + 1 < n && paint[cr + a + 1][cc] == 'X' &&
				(nalt[0][cr + a + 1][cc] == nalt[0][cr + a + 1][cc + len - 1]))
			{
				cr++;
				squares += len;
			}
			else if (cc + len < m && paint[cr][cc + len] == 'X' &&
				(nalt[1][cr][cc + len] == nalt[1][cr + a][cc + len]))
			{
				cc++;
				squares += a + 1;
			}
			else if (squares == total)
			{
				ans = a * len + len;
				break;
			}
			else
				break;
		}
	}
	
	//test col right
	len = 0;
	for (;paint[ulr + len][ulc] == 'X';len++);

	for (int a = 0;a + ulc < n;a++)
	{
		if (len * a + len >= ans)
			continue;

		f1 = true;
		for (int b = 0;b < len;b++)
		{
			if (paint[b + ulr][a + ulc] == '.')
			{
				f1 = false;
				break;
			}
		}

		if (!f1)
			break;

		int cr = ulr, cc = ulc, squares = a * len + len;
		for (int b = 0;;b++)
		{
			//down
			if (squares > total)
				break;
			else if (cr + len < n && paint[cr + len][cc] == 'X' &&
				(nalt[0][cr + len][cc] == nalt[0][cr + len][cc + a]))
			{
				cr++;
				squares += a + 1;
			}
			else if (cc + a + 1 < m && paint[cr][cc + a + 1] == 'X' &&
				(nalt[1][cr][cc + a + 1] == nalt[1][cr + len - 1][cc + a + 1]))
			{
				cc++;
				squares += len;
			}
			else if (squares == total)
			{
				ans = a * len + len;
				break;
			}
			else
				break;
		}
	}

	if (ans == 10000000)
		cout << "-1";
	else
		cout << ans;

	return 0;
}