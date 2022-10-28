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
const int MOD = 1e9+9;
map< pair<int, int>, int> ex;
vector<int> ab[100000], be[100000];
pair<int, int> co[100000];
priority_queue<int> hq;
priority_queue<int, vector<int>, greater<int> > lq;
bitset<100000> rem;
map< pair<int, int>, int>::iterator it;
int N, ans;
bool flag;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> N;
	
	for (int a = 0;a < N;a++)
	{
		cin >> co[a].first >> co[a].second;
		ex.insert (make_pair (co[a], a));
	}

	for (int a = 0;a < N;a++)
	{
		for (int b = co[a].first - 1;b <= co[a].first + 1;b++)
		{
			it = ex.find (make_pair (b, co[a].second + 1));
			if (it != ex.end ()) 
			{
				ab[a].push_back (it->second);
				be[it->second].push_back (a);
			}
		}
	}

	for (int a = 0;a < N;a++)
	{
		flag = true;
		for (int b = 0;b < ab[a].size ();b++)
		{
			if (be[ab[a][b]].size () < 2)
			{
				flag = false;
				break;
			}
		}

		if (flag)
			lq.push (a),
			hq.push (a);
	}
	
	rem.reset ();
	for (int a = N - 1, b;a >= 0;a--)
	{
		if (((N - 1 - a) & 1) == 0)
		{
			while (true)
			{
				if (rem[hq.top ()] == true)
				{
					hq.pop ();
					continue;
				}
				flag = true;
				for (int c = 0;c < ab[hq.top ()].size ();c++)
				{
					if (be[ab[hq.top ()][c]].size () < 2)
					{
						flag = false;
						break;
					}
				}
				if (flag)
					break;
				hq.pop ();
			}
			b = hq.top ();
			hq.pop ();
		}
		else
		{
			while (true)
			{
				if (rem[lq.top ()] == true)
				{
					lq.pop ();
					continue;
				}
				flag = true;
				for (int c = 0;c < ab[lq.top ()].size ();c++)
				{
					if (be[ab[lq.top ()][c]].size () < 2)
					{
						flag = false;
						break;
					}
				}
				if (flag)
					break;
				lq.pop ();
			}
			b = lq.top ();
			lq.pop ();
		}

		rem[b] = true;
		ans = ((ll)ans * N + b) % MOD;

		for (int c = 0;c < be[b].size ();c++)
		{
			ab[be[b][c]].erase (find (ab[be[b][c]].begin (), ab[be[b][c]].end (), b));
			flag = true;
			for (int d = 0;d < ab[be[b][c]].size ();d++)
			{
				if (be[ab[be[b][c]][d]].size () < 2)
				{
					flag = false;
					break;
				}
			}

			if (flag)
				lq.push (be[b][c]),
				hq.push (be[b][c]);
		}
		for (int c = 0;c < ab[b].size ();c++)
			be[ab[b][c]].erase (find (be[ab[b][c]].begin (), be[ab[b][c]].end (), b));
	}

	cout << ans;

	return 0;
}