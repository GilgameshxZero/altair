#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;
int main ()
{
	int n, m;
	double dist[2000], ans;

	//freopen ("Input.txt", "r", stdin);
	cin >> n >> m;
	cout << std::setprecision (8);
	while (!cin.eof ())
	{
		for (int a = 0;a < n + m;a++)
			dist[a] = abs (10000.0 / (n + m) * a - (int)(10000.0 / (n + m) * a * n / 10000 + 0.5) * 10000.0 / n);

		sort (dist, dist + n + m);
		ans = 0;

		for (int a = 0;a < n;a++)
			ans += dist[a];

		cout << ans;
		if (ans == (int)ans)
			cout << ".0\n";
		else
			cout << "\n";
		cin >> n >> m;
	}

	return 0;
}