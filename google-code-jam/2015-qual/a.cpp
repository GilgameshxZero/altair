#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main ()
{
	freopen ("in.txt", "r", stdin);
	freopen ("out.txt", "w", stdout);

	int T, sm;
	cin >> T;

	for (int k = 1;k <= T;k++)
	{
		cout << "Case #" << k << ": ";
		cin >> sm;

		string s;
		cin >> s;

		int up = 0, ans = 0;
		for (int a = 0;a < s.length ();a++)
		{
			if (up < a)
			{
				ans += a - up;
				up = a;
				up += s[a] - '0';
			}
			else
				up += s[a] - '0';
		}

		cout << ans << "\n";
	}

	return 0;
}