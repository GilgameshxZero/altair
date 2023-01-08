//fast nlogn

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

//#ifndef ONLINE_JUDGE
//	freopen ("input0.txt", "r", stdin);
//	freopen ("output.txt", "w", stdout);
//#endif

	int n;
	cin >> n;

	vector<int> x;
	x.resize (n);
	for (int a = 0;a < n;a++)
		cin >> x[a];

	vector<int> seq, len;
	seq.push_back (x[0]);
	len.push_back (1);
	for (int a = 1, b;a < n;a++)
	{
		if (x[a] < seq[0])
			seq[0] = x[a];
		else if (x[a] > seq[seq.size () - 1])
		{
			seq.push_back (x[a]);
			len.push_back (len[len.size () - 1] + 1);
		}
		else
		{
			b = lower_bound (seq.begin (), seq.end (), x[a]) - seq.begin (); //first elem equal or greater to
			seq[b] = x[a];
		}
	}

	cout << len[len.size () - 1] << "\n";

	return 0;
}