#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

long long dp[65][65][2]; //0: same, 1: less
long long CntBin (long long n, long long k)
{
	int dig;

	for (dig = 0;dig < 64;dig++)
		if ((n >> dig) == 0)
			break;
	//cout << n << "\n";
	
	memset (dp, 0, sizeof (dp));
	
	for (int a = 1;a <= dig;a++)
		dp[a][0][1] = 1;
	
	dp[0][0][0] = 1;
	dp[0][0][1] = 0;

	for (int a = 1;a <= dig;a++)
		for (int b = 1;b <= a;b++)
		{
			//cout << (n & (1 << (dig - a))) << "\n";
			if (n >> (dig - a) & 1)
			{
				dp[a][b][0] = dp[a - 1][b - 1][0];
				dp[a][b][1] = dp[a - 1][b][0] + dp[a - 1][b - 1][1] + dp[a - 1][b][1];
			}
			else
			{
				dp[a][b][0] = dp[a - 1][b][0];
				dp[a][b][1] = dp[a - 1][b][1] + dp[a - 1][b - 1][1];				
			}
		}
	
	//cout << dp[dig][k][0] << " " << dp[dig][k][1] << "\n";
	return dp[dig][k][0] + dp[dig][k][1];
	/*dp[i][j][k] = number of numbers with i bits and j set bits either equal to or less than n.
	dp[i][j][0] = if (n[i] == 0) dp[i - 1][j][0]
					if (n[i] == 1) dp[i - 1][j - 1][0];
	dp[i][j][1] = if (n[i] == 0) dp[i - 1][j][1] + dp[i - 1][j - 1][1];
					if (n[i] == 1) dp[i - 1][j][0] + dp[i - 1][j - 1][1] + dp[i - 1][j][1];*/
}

int main ()
{
	//freopen ("input0.txt", "r", stdin);
	//freopen ("output.txt", "w", stdout);
	
	long long m, k;
	cin >> m >> k;
	
	long long s = 1, curbin = CntBin (s * 2, k), nbin = CntBin (s, k);
	while (curbin - nbin < m)
	{
	//cout << nbin << "\n";
		s *= 2;
		nbin = curbin;
		curbin = CntBin (s * 2, k);
	}
	//cout << s << "\n";
	
	long long bot = s / 2, top = s + 1, mid = (bot + top) / 2, x;
	//cout << "\n\n" << CntBin (mid, k) << "\n" << CntBin (top, k) << "\n" << CntBin (bot, k) << "\n\n";
	
	while (bot < top && bot != 0)
	{
		x = CntBin (mid * 2, k) - CntBin (mid, k);
		
		//cout << "bot: " << bot << "\t" << "top: " << top << "\tx: " << x << "\n";
		
		if (x < m)
		{
			bot = mid + 1;
			mid = (bot + top) / 2;
		}
		else //if (x > m)
		{
			top = mid;
			mid = (bot + top) / 2;
		}
		/*else
		{
			cout << mid << "\n";
			return 0;
		}*/
	}
	
	if (bot == 0)
		bot = 1;
	
	cout << bot << "\n";
	return 0;
}