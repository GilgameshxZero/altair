#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int main ()
{
	ios_base::sync_with_stdio (false);
	//freopen ("Text.txt", "r", stdin);

	int n, q;
	bool sum = 0, arr[1000];
	string s;

	cin >> n;
	getline (cin, s);
	for (int a = 0;a < n;a++)
	{
		getline (cin, s);
		arr[a] = s[a * 2] - '0';
		sum ^= arr[a];
	}

	cin >> q;
	for (int a = 0, b;a < q;a++)
	{
		cin >> b;

		if (b <= 2)
		{
			cin >> b;
			sum = !sum;
		}
		else
			printf ("%c", (char)(sum + '0'));
	}

	return 0;
}