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
#include <stack>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

long long n, k, p, x;
vector< vector<long long> > even, odd;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif


	cin >> n >> k >> p;
	for (int a = 0;a < n;a++)
	{
		cin >> x;
		if (x % 2 == 0)
		{
			even.push_back (vector<long long>());
			even[even.size () - 1].push_back (x);
		}
		else
		{
			odd.push_back (vector<long long>());
			odd[odd.size () - 1].push_back (x);
		}
	}

	//Too many evens.
	if (even.size () > p)
	{
		if (p == 0) //shit happens
		{
			if (odd.size () < 1) //were fucked
			{
				cout << "NO\n";
				return 0;
			}

			for (int a = 0;a < even.size ();a++)
				for (int b = 0;b < even[a].size ();b++)
					odd[0].push_back (even[a][b]);

			even.clear ();
		}
		else
		{
			while (even.size () > p)
			{
				even[0].push_back (even[even.size () - 1][0]);
				even.pop_back ();
			}
		}
	}
	else if (even.size () < p)
	{
		//Not enough evens.
		while (even.size () < p && odd.size () >= 2)
		{
			even.push_back (vector<long long>());
			even[even.size () - 1].push_back (odd[odd.size () - 1][0]);
			even[even.size () - 1].push_back (odd[odd.size () - 2][0]);
			odd.pop_back ();
			odd.pop_back ();
		}

		if (even.size () < p)
		{
			cout << "NO\n";
			return 0;
		}
	}

	//Not enough odds or too many odds but can't reduce to right amount.
	if (odd.size () < k - p || 
		((odd.size () - (k - p)) % 2 == 1 && odd.size () > k - p))
	{
		cout << "NO\n";
		return 0;
	}

	//Too many odds, reduce.
	if (k - p == 0) //fuck, p >= 1, even number of odds.
	{
		if (even.size () < 1) //shit
		{
			cout << "NO\n";
			return 0;
		}

		for (int a = 0;a < odd.size ();a++)
			for (int b = 0;b < odd[a].size ();b++)
				even[0].push_back (odd[a][b]);

		odd.clear ();
	}
	else
	{
		while (odd.size () > k - p)
		{
			odd[0].push_back (odd[odd.size () - 1][0]);
			odd[0].push_back (odd[odd.size () - 2][0]);
			odd.pop_back ();
			odd.pop_back ();
		}
	}
	
	cout << "YES\n";

	for (int a = 0;a < even.size ();a++)
	{
		cout << even[a].size () << " ";
		for (int b = 0;b < even[a].size () - 1;b++)
			cout << even[a][b] << " ";
		cout << even[a][even[a].size () - 1] << "\n";
	}
	for (int a = 0;a < odd.size ();a++)
	{
		cout << odd[a].size () << " ";
		for (int b = 0;b < odd[a].size () - 1;b++)
			cout << odd[a][b] << " ";
		cout << odd[a][odd[a].size () - 1] << "\n";
	}

	return 0;
}