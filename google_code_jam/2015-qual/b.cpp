#include <iostream>
#include <cstdio>
#include <string>
#include <queue>
using namespace std;

int main ()
{
	freopen ("in.txt", "r", stdin);
	freopen ("out.txt", "w", stdout);

	int T, D, ans, k;
	vector<int> v;
	cin >> T;

	for (int t = 1;t <= T;t++)
	{
		cout << "Case #" << t << ": ";
		cin >> D;

		v.resize (D);

		for (int a = 0;a < D;a++)
			cin >> v[a];

		ans = 1000;
		for (int a = 1;a <= 1000;a++)
		{
			k = 0;
			for (int b = 0;b < v.size ();b++)
			{
				k += ceil ((double)v[b] / a) - 1;
			}
			ans = min (ans, k + a);
		}

		cout << ans << "\n";
	}

	return 0;
}