//Suffix Array w/ Binary Search

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

struct Triple
{
	int index, rank, next;
};

bool NextComp (Triple x, Triple y)
{
	return (x.next < y.next);
}

bool RankComp (Triple x, Triple y)
{
	return (x.rank < y.rank);
}

//Nlog^2N, for strings with alphabet in integer32 range
void SuffixArrayWide (vector<int>& vec, vector<int>& sa)
{
	int l = vec.size ();

	vector<Triple> tri;
	tri.resize (l);
	for (int a = 0;a < l;a++)
		tri[a].index = a,
		tri[a].rank = vec[a];
	for (int a = 0;a < l - 1;a++)
		tri[a].next = tri[a + 1].rank;
	tri[l - 1].next = -1;

	sort (tri.begin (), tri.end (), NextComp);
	stable_sort (tri.begin (), tri.end (), RankComp);

	int dig; //digits in binary of vec len
	for (dig = 0;(l >> dig) > 0;dig++);

	vector<int> nrank, indrank;
	nrank.resize (l);
	indrank.resize (l);
	for (int a = 2, shift;a <= dig;a++) //sort by first 2^a chars
	{
		//create new ranks
		nrank[0] = 0;
		for (int b = 1;b < l;b++)
		{
			if (tri[b].rank == tri[b - 1].rank && tri[b].next == tri[b - 1].next)
				nrank[b] = nrank[b - 1];
			else
				nrank[b] = nrank[b - 1] + 1;
		}
		for (int b = 0;b < l;b++)
			tri[b].rank = nrank[b],
			indrank[tri[b].index] = nrank[b];
		shift = 1 << (a - 1);
		for (int b = 0;b < l;b++)
		{
			if (tri[b].index + shift >= l)
				tri[b].next = -1;
			else
				tri[b].next = indrank[tri[b].index + shift];
		}

		//sort all according to rank and next
		sort (tri.begin (), tri.end (), NextComp);
		stable_sort (tri.begin (), tri.end (), RankComp);
	}

	//directly copy indexes into return array
	sa.resize (l);
	for (int a = 0;a < l;a++)
		sa[a] = tri[a].index;

	return;
}

bool CompSubSeq1 (vector<int>& x, vector<int>& y, int beg)
{
	int k = min (x.size () - beg, y.size ());

	for (int a = beg;a < beg + k;a++)
	{
		if (x[a] < y[a - beg])
			return true;
		else if (x[a] > y[a - beg])
			return false;
	}

	if (k < y.size ())
		return true;
	return false;
}

bool CompSubSeq2 (vector<int>& x, vector<int>& y, int beg)
{
	int k = min (x.size () - beg, y.size ());

	for (int a = beg;a < beg + k;a++)
	{
		if (x[a] < y[a - beg])
			return true;
		else if (x[a] > y[a - beg])
			return false;
	}

	return true;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n, w;
	cin >> n >> w;

	if (n < w)
	{
		cout << "0";
		return 0;
	}
	if (w == 1)
	{
		cout << n;
		return 0;
	}

	vector<int> bear, ele;
	bear.resize (n);
	ele.resize (w);
	cin >> bear[0];
	for (int a = 1, b;a < n;a++)
		cin >> bear[a],
		bear[a - 1] = bear[a - 1] - bear[a];
	cin >> ele[0];
	for (int a = 1;a < w;a++)
		cin >> ele[a],
		ele[a - 1] = ele[a - 1] - ele[a];

	bear.pop_back ();
	ele.pop_back ();

	//build suffix array for bears
	vector<int> bsuf;
	SuffixArrayWide (bear, bsuf);

	//binary search for bounds of ele
	int lbound, hbound, low = 0, high = bsuf.size (), mid;
	while (low + 1 < high)
	{
		mid = (low + high) / 2;
		if (CompSubSeq1 (bear, ele, bsuf[mid]))
			low = mid;
		else
			high = mid;
	}
	lbound = low; //last suffix < first
	low = 0, high = bsuf.size ();
	while (low + 1 < high)
	{
		mid = (low + high) / 2;
		if (CompSubSeq2 (bear, ele, bsuf[mid]))
			low = mid;
		else
			high = mid;
	}
	hbound = low; //last suffix <= first

	cout << hbound - lbound;

	return 0;
}