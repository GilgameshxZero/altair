#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

long long int n, ave, x1, ans, pre[1000001], coins[1000001];

int main ()
{
	//freopen ("Input.txt", "r", stdin);
	cin >> n;
	
	while (!cin.eof ())
	{
		ave = 0;
		for (int a = 0;a < n;a++)
		{
			cin >> coins[a];
			ave += coins[a];
		}

		ave /= n;
		pre[0] = 0;

		for (int a = 1;a < n;a++)
			pre[a] = pre[a - 1] + coins[a - 1] - ave;

		sort (pre, pre + n);
		x1 = pre[n/2];
		ans = 0;

		for (int a = 0;a < n;a++)
			ans += abs (x1 - pre[a]);

		cout << ans << "\n";
		cin >> n;
	}

	return 0;
}