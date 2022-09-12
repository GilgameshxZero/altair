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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;

	vector<int> v[2001];
	for (int a = 0;a < n;a++)
	{
		int b;
		cin >> b;
		v[b].push_back (a + 1);
	}

	int cnt = 1;
	vector<int> cool;
	for (int a = 0;a <= 2000;a++)
	{
		if (v[a].size () != 0)
		{
			cnt *= v[a].size ();
			if (v[a].size () > 1)
				cool.push_back (a);
			if (cnt >= 3)
				break;
		}
	}

	if (cnt < 3)
	{
		cout << "NO";
		return 0;
	}

	cout << "YES\n";

	if (v[cool[0]].size () >= 3)
	{
		for (int k = 0;k < 3;k++)
		{
			for (int a = 0;a <= 2000;a++)
			{
				if (v[a].size () > 0)
				{
					for (int b = 0;b < v[a].size ();b++)
						cout << v[a][b] << " ";
					next_permutation (v[a].begin (), v[a].end ());
				}
			}
			cout << "\n";
		}
	}
	else
	{
		for (int a = 0;a <= 2000;a++)
		{
			if (v[a].size () > 0)
			{
				for (int b = 0;b < v[a].size ();b++)
					cout << v[a][b] << " ";
			}
		}
		cout << "\n";
		next_permutation (v[cool[1]].begin (), v[cool[1]].end ());
		for (int a = 0;a <= 2000;a++)
		{
			if (v[a].size () > 0)
			{
				for (int b = 0;b < v[a].size ();b++)
					cout << v[a][b] << " ";
			}
		}
		cout << "\n";
		next_permutation (v[cool[0]].begin (), v[cool[0]].end ());
		for (int a = 0;a <= 2000;a++)
		{
			if (v[a].size () > 0)
			{
				for (int b = 0;b < v[a].size ();b++)
					cout << v[a][b] << " ";
			}
		}
	}

	return 0;
}