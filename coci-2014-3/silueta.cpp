#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair< int, pair<int, int>> piii;

bool CompBeg (const piii& a, const piii& b)
{
	return (a.second.first < b.second.first);
}

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int n;
	cin >> n;

	priority_queue<piii> pq;
	vector<piii> build (n);
	int minx = 1000, maxx = 0;
	for (int a = 0;a < n;a++)
		cin >> build[a].second.first >> build[a].second.second >> build[a].first,
		build[a].second.first--,
		build[a].second.second--,
		minx = min (build[a].second.first, minx),
		maxx = max (build[a].second.second, maxx);

	sort (build.begin (), build.end (), CompBeg); //sort by beginning
	vector<int> tallest (1000);
	int mhei = 0;
	for (int a = 0, b = 0;a < 1000;a++)
	{
		for (;b < n && build[b].second.first == a;b++)
			pq.push (build[b]);
		while (!pq.empty () && pq.top ().second.second <= a) //pop off ended sections
			pq.pop ();
		if (!pq.empty ())
			tallest[a] = pq.top ().first;
		else
			tallest[a] = 0;
		mhei = max (tallest[a], mhei);
	}

	vector<string> grid (mhei + 1, string (maxx - minx, '.'));
	tallest.push_back (0);
	int lhei = 0; //last height
	int chei0 = 0; //count where tallest is 0
	for (int a = minx;a < maxx;a++)
	{
		//if last height is less than cur height output # between those heights
		if (lhei <= tallest[a])
			for (int b = lhei;b <= tallest[a];b++)
				grid[b][a - minx] = '#';

		//if next height is less than cur height output # between those heights
		if (tallest[a + 1] <= tallest[a])
			for (int b = tallest[a + 1];b <= tallest[a];b++)
				grid[b][a - minx] = '#';

		//always fill in cur height
		grid[tallest[a]][a - minx] = '#';

		//update lhei
		lhei = tallest[a];
		chei0 += (tallest[a] == 0);
	}

	//get perim
	int perim = 0;
	for (int a = 0;a <= mhei;a++)
		for (int b = 0;b < maxx - minx;b++)
			perim += (grid[a][b] == '#');

	//output, with abscissa
	cout << perim - chei0 << "\n";
	for (int a = mhei;a > 0;a--)
		cout << grid[a] << "\n";
	for (int a = minx;a < maxx;a++)
		cout << '*';
	cout << "\n";

	return 0;
}