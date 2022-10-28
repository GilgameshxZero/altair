#include <iostream>
#include <cstdio>

using namespace std;

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int N, X;
	cin >> N >> X;

	int lID, lc;
	cin >> lID >> lc;
	
	int ans = 0;
	for (int a = 1;a < N;a++)
	{
		int b, c;
		cin >> b >> c;
		
		if (b > lID &&
			c == 1 && lc == 0)
			swap (b, lID);
		if (b < lID &&
			c == 0 && lc == 1)
			swap (b, lID);

		if ((lID <= X && lc == 1) ||
			(lID > X && lc == 0))
			ans++;

		lID = b;
		lc = c;
	}

	if ((lID <= X && lc == 1) ||
		(lID > X && lc == 0))
		ans++;
	
	cout << ans << "\n";

	return 0;
}
