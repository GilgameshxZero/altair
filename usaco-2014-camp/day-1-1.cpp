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
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

void FenInc (vector<int>& fen, int x)
{
	for (;x < fen.size ();x += (x & -x))
		fen[x]++;
}

ll FenSum (vector<int>& fen, int x)
{
	ll r = 0;
	for (;x > 0;x -= (x & -x))
		r += fen[x];
	return r;
}

//find number of subsequences sum strictly less than x
ll CalcLess (vector<int>& pre, int x)
{
	int n = pre.size (); //n + 1

	//divide space into n intervals
	vector<int> interval(n);
	interval[0] = numeric_limits<int>::max ();
	for (int a = 1;a < n;a++)
		interval[a] = pre[a] - x;
	interval.push_back (numeric_limits<int>::min ()); //fen[0] filler
	sort (interval.begin (), interval.end ());

	//fenwick tree represents intervals (directly before intervals, (,])
	vector<int> fen(n + 1);
	
	//sweep through pre and find # of valid subseqs ending at it
	ll r = 0;
	FenInc (fen, lower_bound (interval.begin (), interval.end (), 0) - interval.begin ());
	for (int a = 1;a < n;a++)
	{
		//update r
		r += a - FenSum (fen, lower_bound (interval.begin (), interval.end (), pre[a] - x) - interval.begin ());

		//update fen
		FenInc (fen, lower_bound (interval.begin (), interval.end (), pre[a]) - interval.begin ());
	}

	return r;
}

int main ()
{
	ios_base::sync_with_stdio (false);

	/*std::freopen ("file_name.in", "r", stdin);
	std::freopen ("file_name.out", "w", stdout);*/
	std::ifstream in ("favenums.in");
	std::ofstream out ("favenums.out");

	//we'll be using binary search + prefix sums + fenwick trees
	int n, k;
	in >> n >> k;

	vector<int> pre(n + 1);
	pre[0] = 0;
	for (int a = 1;a <= n;a++)
		in >> pre[a],
		pre[a] += pre[a - 1];

	//binary search on ans
	int low = -10000 * 50000, high = 10000 * 50000 + 1, mid;
	while (low + 1 < high)
	{
		mid = (low + high) / 2;
		if (CalcLess (pre, mid) < k)
			low = mid;
		else
			high = mid;
	}

	out << low << "\n";

	return 0;
}