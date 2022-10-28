#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 52 * 52;
int par[MAXN], spath[MAXN][MAXN];

int Find (int x)
{
	if (par[x] < 0) return x;
	return par[x] = Find (par[x]);
}

void Union (int x, int y)
{
	int i = Find (x), j = Find (y);

	if (i == j) return;
	if (-par[i] >= -par[j])
		par[i] += par[j],
		par[j] = i;
	else
		par[j] += par[i],
		par[i] = j;
}

int main ()
{
	ios_base::sync_with_stdio (false);
	freopen ("in.txt", "r", stdin);
	freopen ("out.txt", "w", stdout);

	int t;
	cin >> t;

	vector< pair<ll, pair<int, int> > > v;
	ll grid[52][52];
	int row, col;
	bool flag;
	pair<int, int> pii;

	for (int a = 1;a <= t;a++)
	{
		cin >> row >> col;

		memset (grid, -1, sizeof (grid));
		v.clear ();
		for (int b = 1;b <= row;b++)
		{
			for (int c = 1;c <= col;c++)
			{
				cin >> grid[b][c];
				v.push_back (make_pair (grid[b][c], make_pair (b, c)));
			}
		}

		for (int b = 0;b < MAXN;b++)
		{
			for (int c = 0;c < MAXN;c++)
			{
				if (b == c)
					spath[b][c] = 0;
				else
					spath[b][c] = 1e9;
			}
		}

		memset (par, -1, sizeof (par));
		sort (v.begin (), v.end (), greater< pair<ll, pair<int, int> > >());
		flag = true;
		for (int b = 0;b < v.size () - 1;b++) //Find paths between all until least element
		{
			if (v[b].first == v[b + 1].first)
			{
				flag = false;
				break;
			}

			pii = v[b].second;
			bool eval = ((v[b].second.first - v[b + 1].second.first + v[b].second.second - v[b + 1].second.second + 100) % 2 == (v[b].first - v[b + 1].first) % 2);
			int id = v[b].second.first * 52 + v[b].second.second;
			if (!(
				eval && (
				grid[pii.first - 1][pii.second] == v[b + 1].first ||
				grid[pii.first][pii.second + 1] == v[b + 1].first ||
				grid[pii.first + 1][pii.second] == v[b + 1].first ||
				grid[pii.first][pii.second - 1] == v[b + 1].first ||
				Find (id) == Find (v[b + 1].second.first * 52 + v[b + 1].second.second))
				))
			{
				flag = false;
				break;
			}

			Union (id, id - 52);
			Union (id, id + 1);
			Union (id, id + 52);
			Union (id, id - 1);

			spath[id][id - 52] = spath[id - 52][id] = 1;
			spath[id][id + 1] = spath[id + 1][id] = 1;
			spath[id][id + 52] = spath[id + 52][id] = 1;
			spath[id][id - 1] = spath[id - 1][id] = 1;

			//Update shortest distances DP
			for (int c = 0;c <= MAXN;c++)
			{
				for (int d = 0;d <= MAXN;d++)
				{
					spath[c][d] = spath[d][c] = min (spath[c][d], spath[c][id] + 1 + spath[d][id - 52]);
					spath[c][d] = spath[d][c] = min (spath[c][d], spath[c][id] + 1 + spath[d][id + 1]);
					spath[c][d] = spath[d][c] = min (spath[c][d], spath[c][id] + 1 + spath[d][id + 52]);
					spath[c][d] = spath[d][c] = min (spath[c][d], spath[c][id] + 1 + spath[d][id - 1]);
				}
			}

			//Any possible long path will be shorter than the dist, so OK
			if (v[b].first - v[b + 1].first > b + 1)
				continue;

			if (spath[id][v[b + 1].second.first * 52 + v[b + 1].second.second] > v[b].first - v[b + 1].first)
			{
				flag = false;
				break;
			}
		}

		cout << "Case #" << a << ":\n";
		if (flag == true)
			cout << "YES\n";
		else
			cout << "NO\n";
	}

	return 0;
}