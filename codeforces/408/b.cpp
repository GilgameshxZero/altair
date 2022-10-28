#include <iostream>
using namespace std;

int main ()
{
	//freopen ("Text.txt", "r", stdin);

	int n, p[1000];
	unsigned long long dp[1001];
	cin >> n;

	for (int a = 0;a < n;a++)
		cin >> p[a];

	dp[0] = 0;

	for (int a = 1;a <= n;a++)
		dp[a] = (2 * dp[a - 1] + 2 - dp[p[a - 1] - 1] + 1000000007) % 1000000007;

	cout << dp[n];
	return 0;
}