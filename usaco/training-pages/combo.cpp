/*
ID: yangchess1
PROG: combo
LANG: C++
*/
#include <fstream>
#include <iostream>
using namespace std;

int main ()
{
	freopen ("combo.in", "r", stdin);
	freopen ("combo.out", "w", stdout);
	int n, combo[2][3];
	cin >> n;
	for (int a = 0;a < 2;a++)
		for (int b = 0;b < 3;b++)
			cin >> combo[a][b];

	int x[3], ans = 0;
	for (x[0] = 1;x[0] <= n;x[0]++)
	{
		for (x[1] = 1;x[1] <= n;x[1]++)
		{
			for (x[2] = 1;x[2] <= n;x[2]++)
			{
				bool f1;
				for (int d = 0;d < 2;d++)
				{
					f1 = true;
					for (int e = 0;e < 3;e++)
						if (max (combo[d][e], x[e]) - min (combo[d][e], x[e]) > 2 && 
							min (combo[d][e], x[e]) + n - max (combo[d][e], x[e]) > 2)
							f1 = false;
					if (f1)
						break;
				}
				ans += f1;
			}
		}
	}

	cout << ans << "\n";
	return 0;
}