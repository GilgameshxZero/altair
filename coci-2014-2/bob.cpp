#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
	ios_base::sync_with_stdio (false);

	int n, m;
	cin >> n >> m;

	vector< vector<int> > grid (n + 1, vector<int> (m + 1, 0));
	for (int a = 1;a <= n;a++)
		for (int b = 1;b <= m;b++)
			cin >> grid[a][b];

	//dp, for houses whose bottom-right is cur square
	ll ans = 0;
	vector< vector<int> > mh (n + 1, vector<int>(m + 1, 0)), //max height extension on current square
		ml, //max left extension on square, with same grid value
		calc; //answer on cur square
	ml = calc = mh;

	//set up ml and mh
	for (int a = 1; a <= n;a++)
	{
		for (int b = 1;b <= m;b++)
		{
			if (grid[a - 1][b] == grid[a][b])
				mh[a][b] = mh[a - 1][b] + 1;
			else
				mh[a][b] = 1;
			if (grid[a][b - 1] == grid[a][b])
				ml[a][b] = ml[a][b - 1] + 1;
			else
				ml[a][b] = 1;
		}
	}

	//calculate answers w/ vector
	vector<int> s; //like stack
	for (int a = 1;a <= n;a++)
	{
		s.clear ();
		s.push_back (0);
		for (int b = 1;b <= m;b++)
		{
			while (mh[a][s.back ()] >= mh[a][b])
				s.pop_back ();
			if (b - s.back () >= ml[a][b])
				calc[a][b] = ml[a][b] * mh[a][b];
			else
				calc[a][b] = (b - s.back ()) * mh[a][b] + calc[a][s.back ()];
			s.push_back (b);
			ans += calc[a][b];
		}
	}

	cout << ans << "\n";

	return 0;
}