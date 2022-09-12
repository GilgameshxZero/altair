#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Divisor
{
	int temp, change[3];
};

int n, x, y, z;
Divisor divisor[40000];

bool DComp (Divisor x, Divisor y)
{
	return (x.temp < y.temp);
}

int main ()
{
	freopen ("milktemp.in", "r", stdin);
	freopen ("milktemp.out", "w", stdout);
	int n, x, y, z;
	cin >> n >> x >> y >> z;
	for (int a = 0, b, c;a < n;a++)
	{
		cin >> b >> c;
		divisor[a * 2].temp = b - 1;
		divisor[a * 2].change[0] = -1;
		divisor[a * 2].change[1] = 1;
		divisor[a * 2].change[2] = 0;
		divisor[a * 2 + 1].temp = c;
		divisor[a * 2 + 1].change[0] = 0;
		divisor[a * 2 + 1].change[1] = -1;
		divisor[a * 2 + 1].change[2] = 1;
	}

	sort (divisor, divisor + n * 2, DComp);
	int ans = x * n, cnt[3] = {n, 0, 0};
	for (int a = 0;a < 2 * n;a++)
	{
		while (a != 2 * n - 1 && divisor[a + 1].temp == divisor[a].temp)
		{
			for (int b = 0;b < 3;b++)
				divisor[a + 1].change[b] += divisor[a].change[b];
			a++;
		}
		for (int b = 0;b < 3;b++)
			cnt[b] += divisor[a].change[b];
		ans = max (ans, cnt[0] * x + cnt[1] * y + cnt[2] * z);
	}
	cout << ans << "\n";
	return 0;
}