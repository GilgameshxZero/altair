/*
ID: yangchess1
LANG: C++
PROB: milk4
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

//-Remove multiples.
//DP on pails with Q. One array stores min num of pails to reach a Q, another stores the last pail used to reach the Q (to see if free update/backtrack for answer), and a final array stores the number of last pails to get to Q (backtrack).
//Sort pails descending, so that if we find a sequence with the same # of pails, it is always a update.

const int MAXQ = 20001, MAXN = 100, INF = 2e9;

vector<int> ans;
int Q, P, p[MAXN], 
	mn[MAXQ], lp[MAXQ], sl[MAXQ]; //min num of pails, last pail index, milk filled by last pail.

//True if sequence ending at x is better than the one at y. If same, return false.
bool Better (int x, int y)
{
	while (x != 0)
	{
		if (lp[x] > lp[y]) return true;
		if (lp[x] < lp[y]) return false;
		x -= sl[x];
		y -= sl[y];
	}
	return false;
}

int main ()
{
	ios_base::sync_with_stdio (false);
	freopen ("milk4.in", "r", stdin);
	freopen ("milk4.out", "w", stdout);

	cin >> Q >> P;
	for (int a = 0;a < P;a++)
		cin >> p[a];

	sort (p, p + P, greater<int>());
	for (int a = 0;a <= Q;a++)
		mn[a] = lp[a] = sl[a] = INF;
	mn[0] = 0;

	//We can use pail subsets 0...a.
	for (int a = 0;a < P;a++)
		for (int b = p[a];b <= Q;b++)
			for (int c = b - p[a];c >= 0;c -= p[a])
				if (lp[c] == a) //Reach back with cur pail and take best set of pails.
				{
					if (mn[c] < mn[b] || (mn[c] == mn[b] && Better (c, b)))
						mn[b] = mn[c],
						lp[b] = a,
						sl[b] = sl[c] + b - c;
				}
				else
				{
					if ((mn[c] + 1 < mn[b]) || (mn[c] + 1 == mn[b] && 
						((a > lp[b]) || (a == lp[b] && Better (c, b - sl[b])))))
						mn[b] = mn[c] + 1,
						lp[b] = a,
						sl[b] = b - c;
				}
	
	//Backtrack.
	while (Q != 0)
		ans.push_back (p[lp[Q]]),
		Q -= sl[Q];

	cout << ans.size () << " ";
	for (int a = 0;a < ans.size () - 1;a++)
		cout << ans[a] << " ";
	cout << ans[ans.size () - 1] << "\n";

	return 0;
}