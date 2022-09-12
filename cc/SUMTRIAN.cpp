#include <iostream>
using namespace std;

int main ()
{
	int t;
	cin >> t;
	for (;t > 0;t--)
	{
		int n;
		cin >> n;

		int row[100][100];
		for (int a = 0;a < n;a++)
			for (int b = 0;b <= a;b++)
				cin >> row[a][b];

		int dp[100][100];
		for (int a = 0;a < n;a++)
			dp[n - 1][a] = row[n - 1][a];
		for (int a = n - 2;a >= 0;a--)
			for (int b = 0;b <= a;b++)
				dp[a][b] = row[a][b] + max (dp[a + 1][b], dp[a + 1][b + 1]);

		cout << dp[0][0] << "\n";
	}
}