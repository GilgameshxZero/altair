#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main ()
{
	ifstream in ("crowded.in");
	ofstream out ("crowded.out");
	int n, d;
	in >> n >> d;
	vector< pair<int, int> > cows;
	cows.resize (n);
	for (int a = 0, b, c;a < n;a++)
	{
		in >> b >> c;
		cows[a] = make_pair (b, c);
	}
	sort (cows.begin (), cows.end ());
	cows.push_back (make_pair (2000000000, 0));
	in.close ();

	//init bbsts
	multiset<int> low, high;
	int ans = 0, lc = -1, hc; //lowcow, highcow, both out of bounds
	for (hc = 1;hc < cows.size () && cows[hc].first - cows[0].first <= d;hc++)
		high.insert (cows[hc].second);

	//sweep window
	for (int a = 1;a < n;a++)
	{
		low.insert (cows[a - 1].second);
		for (;cows[a].first - cows[lc + 1].first > d;lc++)
			low.erase (cows[lc + 1].second);
		for (;cows[hc].first - cows[a].first <= d;hc++)
			high.insert (cows[hc].second);
		high.erase (cows[a].second);
		if (low.size () > 0 && high.size () > 0 && *low.rbegin () >= cows[a].second * 2 && *high.rbegin () >= cows[a].second * 2)
			ans++;
	}

	out << ans << "\n";
	out.close ();

	return 0;
}