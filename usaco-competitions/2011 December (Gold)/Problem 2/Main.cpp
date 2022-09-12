#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;
typedef long long ll;

int Find (vector<int>& par, int x)
{
	if (par[x] < 0)
		return x;
	return par[x] = Find (par, par[x]);
}

bool Union (vector<int>& par, int x, int y)
{
	int i = Find (par, x), j = Find (par, y);

	if (i == j)
		return false;
	else if (-par[i] <= -par[j])
		par[i] += par[j],
		par[j] = i;
	else
		par[j] += par[i],
		par[i] = j;
	
	return true;
}

int main ()
{
	freopen ("simplify.in", "r", stdin);
	freopen ("simplify.out", "w", stdout);

	int n, m;
	cin >> n >> m;

	vector< pair<int, pair<int, int> > > edge (m);
	for (int a = 0;a < m;a++)
	{
		cin >> edge[a].second.first >> edge[a].second.second >> edge[a].first;
		edge[a].second.first--;
		edge[a].second.second--;
		if (edge[a].second.first > edge[a].second.second)
			swap (edge[a].second.first, edge[a].second.second);
	}

	sort (edge.begin (), edge.end ());
	
	vector<int> par (n, -1); //for use in dsu: negative means size, positive is parent
	set< pair<int, int> > s;
	pair<ll, ll> ans (0, 1);
	const ll MOD = 1000000007;
	for (int a = 0, b, c, d, e, f;a < m;)
	{
		s.clear ();
		for (b = a, d = 0;b < m && edge[b].first == edge[a].first;b++)
		{
			e = Find (par, edge[b].second.first);
			f = Find (par, edge[b].second.second);
			if (e > f)
				swap (e, f);
			if (e != f)
				s.insert (make_pair (e, f)), //s counts out of the edges with same len those that connect same components
				d++;
		}

		//find how many edges we will actually insert
		for (c = 0;a < b;a++)
			c += Union (par, edge[a].second.first, edge[a].second.second);

		ans.first += c * edge[a - 1].first;
		if (d == 2 && c == 1)
			ans.second = (ans.second * 2) % MOD;
		else if (d == 3 && c == 1)
			ans.second = (ans.second * 3) % MOD;
		else if (d == 3 && c == 2 && s.size () == 2)
			ans.second = (ans.second * 2) % MOD;
		else if (d == 3 && c == 2 && s.size () == 3)
			ans.second = (ans.second * 3) % MOD;
	}

	cout << ans.first << " " << ans.second << "\n";

	return 0;
}