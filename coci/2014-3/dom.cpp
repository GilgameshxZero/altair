#include <string>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int n, m, p;
	cin >> n >> m >> p;

	vector<int> fav (m, -1);
	for (int a = 0, b, c;a < n;a++)
	{
		cin >> b >> c;
		if (fav[c - 1] == -1)
			fav[c - 1] = b - 1;
	}

	vector<bool> watch (m, false);
	int cnt = 0;
	p--;
	while (watch[p] == false && fav[p] != -1)
		watch[p] = true,
		p = fav[p],
		cnt++;

	if (fav[p] == -1)
		cout << cnt << "\n";
	else
		cout << "-1\n";

	return 0;
}