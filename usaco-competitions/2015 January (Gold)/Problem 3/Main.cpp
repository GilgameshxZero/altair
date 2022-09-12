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

const int MAXN = 1e5;
vector< vector<int> > scc_into;
vector<int> edge[MAXN], scc_grass, out_deg, zero_deg, dp;
stack<int> s;
bitset<MAXN> instack;
int ind[MAXN], lowlink[MAXN], scc[MAXN];
int cind, cscc, N, M;

void Tarjan (int x)
{
	ind[x] = cind++; //first time visit
	lowlink[x] = ind[x];
	s.push (x); //so we can find sccs effectively
	instack[x] = true;

	//see if any children have links backward. if unvisited, visit. if on the current stack, then eval lowlink; if not, then ignore, because it belongs to another scc.
	for (int a = 0;a < edge[x].size ();a++)
	{
		if (ind[edge[x][a]] == -1)
		{
			Tarjan (edge[x][a]);
			lowlink[x] = min (lowlink[x], lowlink[edge[x][a]]);
		}
		else if (instack[edge[x][a]])
			lowlink[x] = min (lowlink[x], lowlink[edge[x][a]]);
	}

	if (lowlink[x] == ind[x]) //we cant go farther back, so this is the conclusion of an scc. pop off stack until we reach x to get scc
	{
		scc_grass.push_back (0);
		while (s.top () != x)
		{
			//add s.top to scc
			scc[s.top ()] = cscc;
			scc_grass[cscc]++;
			instack[s.top ()] = false;
			s.pop ();
		}

		//add s.top to scc
		scc[s.top ()] = cscc;
		scc_grass[cscc]++;
		s.pop ();
		instack[x] = false;
		cscc++;
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("grass.in", "r", stdin);
	std::freopen ("grass.out", "w", stdout);

	memset (ind, -1, sizeof (ind));

	cin >> N >> M;
	for (int a = 0, b, c;a < M;a++)
		cin >> b >> c,
		edge[b - 1].push_back (c - 1);

	for (int a = 0;a < N;a++)
		if (ind[a] == -1)
			Tarjan (a);

	scc_into.resize (cscc * 2);
	out_deg.resize (cscc * 2, 0);
	dp.resize (cscc * 2);
	scc_grass.resize (cscc * 2);
	for (int a = cscc;a < cscc * 2;a++)
		scc_grass[a] = scc_grass[a - cscc];
	for (int a = 0;a < N;a++)
	{
		for (int b = 0;b < edge[a].size ();b++)
		{
			if (scc[edge[a][b]] == scc[a])
				continue;
			//normal path
			scc_into[scc[edge[a][b]]].push_back (scc[a]);
			out_deg[scc[a]]++;
			//back path
			scc_into[scc[a]].push_back (scc[edge[a][b]] + cscc);
			out_deg[scc[edge[a][b]] + cscc]++;
			//back normal
			scc_into[scc[edge[a][b]] + cscc].push_back (scc[a] + cscc);
			out_deg[scc[a] + cscc]++;
		}
	}

	for (int a = 0;a < cscc * 2;a++)
		if (out_deg[a] == 0)
			zero_deg.push_back (a),
			dp[a] = scc_grass[a];

	while (!zero_deg.empty ())
	{
		int cur = zero_deg.back ();
		zero_deg.pop_back ();
		if (cur == scc[0])
			dp.clear (),
			dp.resize (cscc * 2);

		for (int a = 0;a < scc_into[cur].size ();a++)
		{
			if (dp[scc_into[cur][a]] < dp[cur] + scc_grass[scc_into[cur][a]])
				dp[scc_into[cur][a]] = dp[cur] + scc_grass[scc_into[cur][a]];
			out_deg[scc_into[cur][a]]--;
			if (out_deg[scc_into[cur][a]] == 0)
				zero_deg.push_back (scc_into[cur][a]);
		}

		if (cur == scc[0] + cscc)
			break;
	}

	cout << max (dp[scc[0]], dp[scc[0] + cscc]) << "\n";

	return 0;
}