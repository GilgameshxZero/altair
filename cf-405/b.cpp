#include <iostream>
using namespace std;

int main ()
{
	//freopen ("Text.txt", "r", stdin);

	int n, ans = 0, c = 0;
	char last = '#';
	cin >> n;
	cin.get ();

	for (int a = 0;a < n;a++)
	{
		char x = cin.get ();
		
		if (x == '.')
			c++;
		else if (x == 'R')
		{
			ans += c;
			c = 0;
			last = x;
		}
		else if (x == 'L')
		{
			if (last != '#' && c % 2 == 1)
				ans++;

			last = x;
			c = 0;
		}
	}

	if (last == 'L' || last == '#')
		ans += c;

	cout << ans;
	return 0;
}