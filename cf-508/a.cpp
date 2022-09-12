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

bool pix[1002][1002];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int N, M, K;
	cin >> N >> M >> K;
	for (int a = 0;a < K;a++)
	{
		int x, y;
		cin >> x >> y;
		if (pix[x][y] == 1)
			continue;
		else
		{
			pix[x][y] = 1;
			if (pix[x - 1][y] == 1 && pix[x][y - 1] == 1 && pix[x - 1][y - 1] == 1)
			{
				cout << a + 1;
				return 0;
			}
			if (pix[x - 1][y] == 1 && pix[x][y + 1] == 1 && pix[x - 1][y + 1] == 1)
			{
				cout << a + 1;
				return 0;
			}
			if (pix[x + 1][y] == 1 && pix[x][y + 1] == 1 && pix[x + 1][y + 1] == 1)
			{
				cout << a + 1;
				return 0;
			}
			if (pix[x + 1][y] == 1 && pix[x][y - 1] == 1 && pix[x + 1][y - 1] == 1)
			{
				cout << a + 1;
				return 0;
			}
		}
	}

	cout << "0";
	return 0;
}