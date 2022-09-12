#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void main ()
{
	int t, n, war, dwar;
	vector<double> ken, naomi;
	double temp;

	freopen ("in.txt", "r", stdin);
	freopen ("out.txt", "w", stdout);

	cin >> t;

	for (int a = 0;a < t;a++)
	{
		cin >> n;
		naomi.clear ();
		ken.clear ();

		for (int b = 0;b < n;b++)
		{
			cin >> temp;
			naomi.push_back (temp);
		}
		for (int b = 0;b < n;b++)
		{
			cin >> temp;
			ken.push_back (temp);
		}

		sort (naomi.begin (), naomi.end ());
		sort (ken.begin (), ken.end ());
		war = dwar = 0;

		for (int b = 0, c = 0;b < n;b++)
		{
			for (;c < n;c++)
				if (ken[c] > naomi[b])
					break;

			if (c == n)
				war++;
			else
				c++;
		}

		for (int b = 0, c = 0;c < n;c++)
		{
			for (;b < n;b++)
				if (naomi[b] > ken[c])
					break;
			
			if (b != n)
			{
				dwar++;
				b++;
			}
			else
				break;
		}

		cout << "Case #" << a + 1 << ": " << dwar << " " << war << "\n";
	}
}