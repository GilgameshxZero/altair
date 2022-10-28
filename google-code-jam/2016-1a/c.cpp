#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main ()
{
	ifstream in ("in.txt");
	ofstream out ("out.txt");
	int tt;

	in >> tt;

	for (int t = 1; t <= tt; t++)
	{
		out << "Case #" << t << ": ";

		int n;
		in >> n;

		vector<int> bff (n), ind (n), lone;
		for (int a = 0;a < n;a++)
		{
			in >> bff[a];
			bff[a]--;
			ind[bff[a]]++;
		}

		int ans = 2;

		//find all 0 ins
		for (int a = 0;a < n;a++)
			if (ind[a] == 0)
				lone.push_back (a);

		//find all loops
		vector<bool> tlp (n, false);
		vector<int> longest (n, 0);
		int tlpp = 0;
		for (int a = 0;a < n;a++)
		{
			int next = bff[a], step = 0;
			while (next != a && step < n + 1)
			{
				step++;
				next = bff[next];
			}

			if (next == a && step > 1)
				ans = max (ans, step + 1);
			if (next == a && step == 1)
			{
				tlp[a] = true;
				tlp[bff[a]] = true;
				tlpp++;
			}
		}

		//start from lone node on to tlp
		for (int a = 0;a < lone.size ();a++)
		{
			int len = 1, next = bff[lone[a]];
			while (tlp[next] != true && len <= n + 1)
			{
				len++;
				next = bff[next];
			}

			if (tlp[next] == true)
				longest[next] = max (longest[next], len);
		}

		int temp = 0;
		for (int a = 0;a < n;a++)
			if (tlp[a])
				temp++;

		if (temp != tlpp)
			int k = 0;

		int tans = tlpp;
		for (int a = 0;a < n;a++)
			tans += longest[a];

		ans = max (ans, tans);

		out << ans << '\n';
		cout << t << '\n';
	}

	in.close ();
	out.close ();
}