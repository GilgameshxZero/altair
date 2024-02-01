#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

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

	stable_sort (tri.begin (), tri.end (), NextComp);
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
		stable_sort (tri.begin (), tri.end (), NextComp);
		stable_sort (tri.begin (), tri.end (), RankComp);
	}

	//directly copy indexes into return array
	sa.resize (l);
	for (int a = 0;a < l;a++)
		sa[a] = tri[a].index;

	return;
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
		for (int b = 0;b < l;b++)
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
	while (true)
	{
		string com;
		cout << "Enter a string ('exit' to quit): ";
		cin >> com;

		if (com == "exit")
			return 0;

		vector<int> vec;
		vec.resize (com.size ());
		for (int a = 0;a < com.length ();a++)
			vec[a] = com[a];
		
		vector<int> sa;
		SuffixArrayWide (vec, sa);
		for (int a = 0;a < sa.size ();a++)
			cout << com.substr (sa[a], com.size () - sa[a]) << '\n';
		cout << '\n';
	}

	/*
	
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

	*/
}