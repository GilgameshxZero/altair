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

int cnt[1000001];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n;
	vector<int> id;
	map<int, int> m[2];

	cin >> n;
	id.resize (n);

	for (int a = 0, b, c;a < n;a++)
	{
		cin >> b >> c;
		m[0].insert (make_pair (b, c));
		m[1].insert (make_pair (c, b));
		cnt[b]++;
		cnt[c]++;
	}

	id[1] = m[0].find (0)->second;

	map<int, int>::iterator mit;
	for (int b = 1;b < n;)
	{
		mit = m[0].find (id[b]);
		if (mit == m[0].end () || mit->second == 0)
			break;
		b += 2;
		id[b] = mit->second;
	}

	if (mit == m[0].end ())
	{
		id[n - 2] = m[1].find (0)->second;
		for (int b = n - 2;b >= 0;)
		{
			mit = m[1].find (id[b]);
			b -= 2;
			if (b < 0)
				break;
			id[b] = mit->second;
		}
	}
	else //odd
	{
		//cnt = 1 is the first and last pos
		vector<int> finals;
		for (int a = 0;a <= 1000000;a++)
			if (cnt[a] == 1)
				finals.push_back (a);

		mit = m[0].find (finals[0]);
		if (mit == m[0].end ())
			swap (finals[0], finals[1]),
			mit = m[0].find (finals[0]);

		id[0] = finals[0];
		for (int b = 0;b < n;)
		{
			mit = m[0].find (id[b]);
			b += 2;
			if (b >= n)
				break;
			id[b] = mit->second;
		}
	}

	for (int a = 0;a < n;a++)
		cout << id[a] << " ";

	return 0;
}