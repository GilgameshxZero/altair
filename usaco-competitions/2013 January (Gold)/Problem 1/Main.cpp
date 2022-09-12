//solution by yang yan
//sliding window
#include <iostream>
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;

bool CompInd (const pair<int, int>& a, const pair<int, int>& b)
{
	return (a.second < b.second);
}

int main ()
{
	freopen ("lineup.in", "r", stdin);
	freopen ("lineup.out", "w", stdout);

	int n, k;
	cin >> n >> k;

	vector< pair<int, int> > cow (n); //(id, pos)
	for (int a = 0;a < n;a++)
		cin >> cow[a].first,
		cow[a].second = a;

	//normalize IDs
	sort (cow.begin (), cow.end ());
	int cid = 0;
	for (int a = 0;a < n - 1;a++)
	{
		if (cow[a].first == cow[a + 1].first)
			cow[a].first = cid;
		else
			cow[a].first = cid++;
	}
	cow[n - 1].first = cid;
	sort (cow.begin (), cow.end (), CompInd);

	//normalize k
	k = min (k, n - 1);

	//sliding window with at most k + 1 separate IDs
	int ans = 0, distinct = 0;
	vector<int> cnt (n, 0); //count of each ID
	for (int a = 0, b = 0;b < n;b++) //sliding window (a, b]
	{
		//add the new end in
		cnt[cow[b].first]++;
		if (cnt[cow[b].first] == 1)
			distinct++;

		//remove until distinct is <= k+1
		while (distinct > k + 1)
		{
			cnt[cow[a].first]--;
			if (cnt[cow[a].first] == 0)
				distinct--;
			a++;
		}

		//update ans on last cow
		ans = max (ans, cnt[cow[b].first]);
	}

	cout << ans << "\n";

	return 0;
}