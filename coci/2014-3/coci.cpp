#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void FenAdd (vector<int>& fen, int x, int inc)
{
	for (;x < fen.size ();x += (x & -x))
		fen[x] += inc;
}

int FenSum (vector<int>& fen, int x)
{
	int r = 0;
	for (;x > 0;x -= (x & -x))
		r += fen[x];
	return r;
}

bool Comp (const pair< pair<int, int>, int>& a, const pair< pair<int, int>, int>& b)
{
	if (a.first.first < b.first.first)
		return true;
	else if (a.first.first > b.first.first)
		return false;
	else //=
		return (a.first.second > b.first.second);
}

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int n;
	cin >> n;

	vector< pair<int, int> > ans (n, make_pair (1, n)); //(high, low)
	vector<int> cxmax (651, 0), cymax (651, 0), //count of points with x = 650 or y = 650 for any y or x
		prex (651, 0); //number of points with that x coordinate or less
	vector< pair< pair<int, int>, int> > pt (n);
	for (int a = 0;a < n;a++)
	{
		cin >> pt[a].first.first >> pt[a].first.second;
		pt[a].second = a;
		cxmax[pt[a].first.second] += (pt[a].first.first == 0);
		cymax[pt[a].first.first] += (pt[a].first.second == 0);
		prex[pt[a].first.first]++;
	}
	
	//correct prefix array
	for (int a = 1;a < 651;a++)
		prex[a] += prex[a - 1];

	//subtract out border cases now
	for (int a = 0;a < n;a++)
	{
		if (pt[a].first.first == 650)
			ans[a].second -= cxmax[pt[a].first.second];
		if (pt[a].first.second == 650)
			ans[a].second -= cymax[pt[a].first.first];
	}

	sort (pt.begin (), pt.end (), Comp); //sort by x, dec y

	vector<int> compl (n); //a2 <= a1 and b2 <= b1
	vector<int> fen (652, 0); //fenwick tree shift 1
	for (int a = 0;a < n;a++)
	{
		if (a != 0 && pt[a].first.first != pt[a - 1].first.first) //finished last column
		{
			for (int b = a - 1;b >= 0 && pt[b].first.first == pt[a - 1].first.first;b--)
				compl[pt[b].second] = FenSum (fen, pt[b].first.second + 1);
		}
		ans[pt[a].second].second -= FenSum (fen, pt[a].first.second);
		FenAdd (fen, pt[a].first.second + 1, 1);
	}
	for (int b = n - 1;b >= 0 && pt[b].first.first == pt[n - 1].first.first;b--)
		compl[pt[b].second] = FenSum (fen, pt[b].first.second + 1);

	//use compl to find highs
	for (int a = 0;a < n;a++)
		ans[pt[a].second].first += n - prex[pt[a].first.first] - FenSum (fen, pt[a].first.second + 1) + compl[pt[a].second];

	for (int a = 0;a < n;a++)
		cout << ans[a].first << " " << ans[a].second << "\n";

	return 0;
}