//NlogN

#include <algorithm>
#include <bitset>
#include <cassert>
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
#include <limits>
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

	vector< pair<int, int> > x, seq;
	vector<int> len; //len of our active seqs
	x.resize (n);
	for (int a = 0;a < n;a++)
		cin >> x[a].first >> x[a].second;

	seq.push_back (x[0]);
	len.push_back (1);


	return 0;
}