#define _CRT_SECURE_NO_DEPRECATE 
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

int FindMinDepth (vector<string> &bo, vector< vector< vector< pair<int, int> > > > &bk, vector< vector< pair<int, int> > > &fo, int r, int c)
{
	int ret = 0, mi = 0;

	if (bo[r][c] != '.' && bo[r][c] != '0')
		mi++;

	for (int a = 0;a < bk[r][c].size ();a++)
		ret = min (mi + FindMinDepth (bo, bk, fo, bk[r][c][a].first, bk[r][c][a].second), ret);

	return ret;
}

int main ()
{
	freopen ("in.txt", "r", stdin);
	freopen ("out.txt", "w", stdout);

	int T;
	cin >> T;

	for (int a = 0;a < T;a++)
	{
		cout << "Case #" << a + 1 << ": ";
		int R, C;
		cin >> R >> C;
		vector<string> bo (R + 2);
		bo[0] = string (C + 2, '0');
		for (int b = 1;b <= R;b++)
			cin >> bo[b],
			bo[b] = "0" + bo[b] + "0";
		bo.back () = string (C + 2, '0');

		vector< vector< vector< pair<int, int> > > > bk (R + 2, vector< vector< pair<int, int> > >(C + 2));
		vector< vector< pair<int, int> > > fo (R + 2, vector< pair<int, int> >(C + 2));

		for (int b = 1;b <= R;b++)
		{
			for (int c = 1;c <= C;c++)
			{
				if (bo[b][c] == '.')
				{
					bk[b][c].push_back (make_pair (b, c));
					fo[b][c] = make_pair (b, c);
				}
				else if (bo[b][c] == '<')
				{
					fo[b][c] = make_pair (b, c - 1);
					bk[b][c - 1].push_back (make_pair (b, c));
				}
				else if (bo[b][c] == '^')
				{
					fo[b][c] = make_pair (b - 1, c);
					bk[b - 1][c].push_back (make_pair (b, c));
				}
				else if (bo[b][c] == '>')
				{
					fo[b][c] = make_pair (b, c + 1);
					bk[b][c + 1].push_back (make_pair (b, c));
				}
				else if (bo[b][c] == 'v')
				{
					fo[b][c] = make_pair (b + 1, c);
					bk[b + 1][c].push_back (make_pair (b, c));
				}
			}
		}

		//impo/find mindepth of each tree
		bool flag = false;
		int ans = 0;
		for (int b = 0; b <= R + 1; b++)
		{
			for (int c = 0; c <= C + 1; c++)
			{
				if (b == 0 || c == 0 || b == R + 1 || c == C + 1)
				{
					int mindepth = FindMinDepth (bo, bk, fo, b, c);

					if (mindepth == 1)
						flag = true;
					if (mindepth != 0)
						ans++;
				}
			}
		}

		if (flag)
			cout << "IMPOSSIBLE\n";
		else
			cout << ans << '\n';
	}

	return 0;
}