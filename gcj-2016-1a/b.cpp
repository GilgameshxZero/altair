#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool compvh (vector<int> &x, vector<int> &y)
{
	for (int a = 0;a < x.size ();a++)
	{
		if (x[a] < y[a])
			return true;
		else if (x[a] > y[a])
			return false;
	}

	return false;
}

bool strictless (vector<int> &x, vector<int> &y)
{
	for (int a = 0; a < x.size (); a++)
	{
		if (x[a] >= y[a])
			return false;
	}

	return true;
}

int main ()
{
	ifstream in ("in.txt");
	ofstream out ("out.txt");
	int tt;

	in >> tt;

	for (int t = 1; t <= tt; t++)
	{
		out << "Case #" << t << ":";

		int n;
		in >> n;

		/*vector< vector<int> > h (2 * n - 1, vector<int> (n));
		for (int a = 0;a < 2 * n - 1;a++)
			for (int b = 0;b < n;b++)
				in >> h[a][b];

		sort (h.begin (), h.end (), compvh);

		vector<int> smt (2 * n, -1), lis (2 * n - 1), last (2 * n - 1);
		smt[1] = 0;
		lis[0] = 1;
		last[0] = -1;

		for (int a = 1;a < 2 * n - 1;a++)
		{
			int low = 0, mid, high = 2 * n;
			while (low + 1 < high)
			{
				mid = (low + high) / 2;
				if (smt[mid] != -1 && strictless (h[smt[mid]], h[a]))
					low = mid;
				else
					high = mid;
			}

			if (smt[low] == -1)
				lis[a] = 1,
				last[a] = -1;
			else
				lis[a] = lis[smt[low]] + 1,
				last[a] = smt[low];
			if (smt[lis[a]] != -1)
				smt[lis[a]] = min (smt[lis[a]], a);
			else
				smt[lis[a]] = a;
		}

		vector< vector<int> > hh (n, vector<int> (n));
		int lenn = 0;
		for (int a = 0;a < 2 * n - 1;a++)
			if (lis[a] > lenn)
				lenn*/

		vector<int> cnt (2501, 0);
		for (int a = 0;a < 2 * n - 1;a++)
			for (int b = 0, c;b < n;b++)
				in >> c,
				cnt[c]++;

		vector<int> ans;
		for (int a = 0;a <= 2500;a++)
			if (cnt[a] % 2 == 1)
				ans.push_back (a);

		sort (ans.begin (), ans.end ());

		for (int a = 0;a < ans.size ();a++)
			out << " " << ans[a];

		out << '\n';
	}

	in.close ();
	out.close ();
}