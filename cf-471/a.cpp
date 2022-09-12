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

	int cnt[10];
	memset (cnt, 0, sizeof (cnt));
	for (int a = 0;a < 6;a++)
	{
		int b;
		cin >> b;
		cnt[b]++;
	}

	bool f1 = false;
	for (int a = 0;a < 10;a++)
		if (cnt[a] >= 4)
			f1 = true;
	if (!f1)
	{
		cout << "Alien";
		return 0;
	}

	for (int a = 0;a < 10;a++)
		if (cnt[a] < 4 && cnt[a] == 1)
		{
			cout << "Bear";
			return 0;
		}

	cout << "Elephant";

	return 0;
}