#include <iostream>
#include <string>
#include <cstring>
using namespace std;

/*	0. contains 0 (doesn't need mine)
	1. contains 1, need mine
	2. contains 1, doesn't need mine
	3. contains 2 (needs mine)
	4. contains mine
*/

int main ()
{
	//freopen ("Text.txt", "r", stdin);

	const unsigned long long mod = 1000000007;
	unsigned long long dp[2][5];
	string s;
	cin >> s;

	memset (dp[0], 0, 5 * sizeof (unsigned long long));

	if (s[0] == '?')
	{
		dp[0][0] = dp[0][1] = dp[0][4] = 1;
		dp[0][2] = dp[0][3] = 0;
	}
	else if (s[0] == '*')
		dp[0][4] = 1;
	else if (s[0] == '0')
		dp[0][0] = 1;
	else if (s[0] == '1')
		dp[0][1] = 1;
	else if (s[0] == '2')
	{
		cout << "0";
		return 0;
	}

	for (int a = 1;a < s.length ();a++)
	{
		memset (dp[a % 2], 0, 5 * sizeof (unsigned long long));
		if (s[a] == '?' || s[a] == '*') //Case 4 <-- 1, 3, 4.
			dp[a % 2][4] += (dp[(a - 1) % 2][1] + dp[(a - 1) % 2][3] + dp[(a - 1) % 2][4]) % mod;
		if (s[a] == '?' || s[a] == '0') //Case 0 <-- 0, 2.
			dp[a % 2][0] += (dp[(a - 1) % 2][0] + dp[(a - 1) % 2][2]) % mod;
		if (s[a] == '?' || s[a] == '1') //Case 1 <-- 0, 2. Case 2 <-- 4.
		{
			dp[a % 2][1] += (dp[(a - 1) % 2][0] + dp[(a - 1) % 2][2]) % mod;
			dp[a % 2][2] += dp[(a - 1) % 2][4] % mod;
		}
		if (s[a] == '?' || s[a] == '2') //Case 3 <-- 4.
			dp[a % 2][3] += dp[(a - 1) % 2][4] % mod;
	}

	cout << (dp[(s.length () - 1) % 2][0] + dp[(s.length () - 1) % 2][2] + dp[(s.length () - 1) % 2][4]) % mod << "\n";

	return 0;
}