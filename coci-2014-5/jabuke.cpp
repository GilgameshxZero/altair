#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

bool grid[500][500];
pair<int, int> tloc[500 * 500 + 100000];
int ct = 0;
vector<int> trow[500];

int main ()
{
	//freopen ("in.txt", "r", stdin); freopen ("out.txt", "w", stdout);
	int R, C;
	cin >> R >> C;

	string s;
	for (int a = 0;a < R;a++)
	{
		cin >> s;
		for (int b = 0;b < C;b++)
			if (s[b] == 'x')
				grid[a][b] = true,
				tloc[ct++] = make_pair (a, b),
				trow[a].push_back (b);
	}

	int Q;
	cin >> Q;
	for (int a = 0, b, c;a < Q;a++)
	{
		cin >> b >> c;
		b--;c--;

		int aprx = 2000000;
		for (int d = 0;d < 400;d++)
		{
			int f = rand () % ct;
			aprx = min (aprx, (tloc[f].first - b) * (tloc[f].first - b) + (tloc[f].second - c) * (tloc[f].second - c));
		}

		int ans = aprx;
		aprx = sqrt ((double)aprx - 1);
		for (int d = max (0, b - aprx), D = min (R - 1, b + aprx);d <= D;d++)
		{
			int e = max (0, c - aprx), E = min (C - 1, c + aprx);
			if (trow[d].size () < E - e + 1)
			{
				for (int f = 0;f < trow[d].size ();f++)
					if (trow[d][f] >= e && trow[d][f] <= E)
						ans = min (ans, (d - b) * (d - b) + (trow[d][f] - c) * (trow[d][f] - c));
			}
			else
			{
				for (;e <= E;e++)
					if (grid[d][e])
						ans = min (ans, (d - b) * (d - b) + (e - c) * (e - c));
			}
		}

		cout << ans << "\n";
		grid[b][c] = true;
		tloc[ct++] = make_pair (b, c);
		trow[b].push_back (c);
	}

	return 0;
}