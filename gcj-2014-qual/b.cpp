#include <iomanip>
#include <iostream>

using namespace std;

void main ()
{
	int t, n;
	double c, f, x, last, s, cur;

	freopen ("in.txt", "r", stdin);
	freopen ("out.txt", "w", stdout);

	cin >> t;
	cout << setprecision (7) << std::fixed;

	for (int a = 0;a < t;a++)
	{
		last = numeric_limits<double>::max ();
		n = 0;
		cin >> c >> f >> x;

		while (true)
		{
			s = 2;
			cur = 0;

			for (int b = 0;b < n;b++)
			{
				cur += c / s;
				s += f;
			}

			cur += x / s;

			if (cur > last)
				break;
			else
			{
				last = cur;
				n++;
			}
		}

		cout << "Case #" << a + 1 << ": " << last << "\n";
	}
}