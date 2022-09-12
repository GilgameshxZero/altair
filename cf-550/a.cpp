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

typedef long long ll;

int main()
{
	ios_base::sync_with_stdio(false);

#ifndef ONLINE_JUDGE
	freopen("input0.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	string s;
	cin >> s;

	vector<int> pos[2];
	int mmax[2], mmin[2];

	mmax[0] = mmax[1] = -1;
	mmin[0] = mmin[1] = 1000000;

	for (int a = 0; a < s.length() - 1;a++)
	{
		if (s[a] == 'A' && s[a + 1] == 'B')
			pos[0].push_back(a),
			mmax[0] = max(mmax[0], a),
			mmin[0] = min(mmin[0], a);
		else if (s[a] == 'B' && s[a + 1] == 'A')
			pos[1].push_back(a),
			mmax[1] = max(mmax[1], a),
			mmin[1] = min(mmin[1], a);
	}

	if (pos[0].size() == 0 || pos[1].size() == 0)
		cout << "NO";
	else if (abs(mmin[0] - mmax[1]) > 1 || abs (mmax[0] - mmin[1]) > 1)
		cout << "YES";
	else
		cout << "NO";

	return 0;
}