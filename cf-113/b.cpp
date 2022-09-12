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
	int index, rank, next; //Rank is b/t 0 and 127
};

bool NextComp (Triple x, Triple y)
{
	return (x.next < y.next);
}

bool RankComp (Triple x, Triple y)
{
	return (x.rank < y.rank);
}

//Nlog^2N, for strings with alphabet in [0, 127] of char
void SuffixArray (string& str, vector<int>& sa)
{
	int l = str.length ();

	vector<Triple> tri;
	tri.resize (l);
	for (int a = 0;a < l;a++)
		tri[a].index = a,
		tri[a].rank = str[a];
	for (int a = 0;a < l - 1;a++)
		tri[a].next = tri[a + 1].rank;
	tri[l - 1].next = -1;

	stable_sort (tri.begin (), tri.end (), NextComp);
	stable_sort (tri.begin (), tri.end (), RankComp);

	int dig; //digits in binary of str len
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
		for (int b = 0, c = l - shift;b < c;b++)
		{
			if (tri[b].index + shift >= l)
				tri[b].next = -1;
			else
				tri[b].next = indrank[tri[b].index + shift];
		}

		//sort all according to rank and next
		stable_sort (tri.begin (), tri.end (), NextComp);
		stable_sort (tri.begin (), tri.end (), RankComp);
	}

	//directly copy indexes into return array
	sa.resize (l);
	for (int a = 0;a < l;a++)
		sa[a] = tri[a].index;

	return;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	string str, first, last;
	cin >> str >> first >> last;

	//get suffix array for str first
	vector<int> sa;
	SuffixArray (str, sa);

	//binary search for lower and upper bounds on first
	int lbound, hbound, low = 0, high = sa.size (), mid;
	while (low + 1 < high)
	{
		mid = (low + high) / 2;
		if (str.substr (sa[mid], min (str.length () - sa[mid], first.length ())) < first)
			low = mid;
		else
			high = mid;
	}
	lbound = low; //last suffix < first
	low = 0, high = sa.size ();
	while (low + 1 < high)
	{
		mid = (low + high) / 2;
		if (str.substr (sa[mid], min (str.length () - sa[mid], first.length ())) <= first)
			low = mid;
		else
			high = mid;
	}
	hbound = low; //last suffix <= first

	//build failure function for last
	vector<int> ff;
	ff.resize (last.length () + 1);
	ff[0] = ff[1] = 0;
	for (int a = 2, b;a < ff.size ();a++)
	{
		b = ff[a - 1];
		while (true)
		{
			if (last[b] == last[a - 1])
			{
				ff[a] = b + 1;
				break;
			}
			else if (b == 0)
			{
				ff[a] = 0;
				break;
			}
			else
				b = ff[b];
		}
	}

	//walk through each valid suffix (sa[a]) and KMP
	int ans = 0;
	for (int a = lbound + 1;a <= hbound;a++)
	{
		for (int b = 0, c = 0;b < str.length () - sa[a];)
		{
			if (str[b + sa[a]] == last[c])
			{
				b++;
				c++;
				if (c == last.size ())
				{
					ans++;
					c = ff[c];
				}
			}
			else if (c != 0)
				c = ff[c];
			else
				b++;
		}
	}

	cout << ans;

	return 0;
}