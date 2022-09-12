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
#include <string>
#include <vector>

using namespace std;

int main ()
{
	ios_base::sync_with_stdio (false);

	/*std::freopen ("file_name.in", "r", stdin);
	std::freopen ("file_name.out", "w", stdout);*/
	std::ifstream in ("photo.in");
	std::ofstream out ("photo.out");

	int n;
	in >> n;

	map<int, int> backlink;
	int ref[20000], pos[5][20000];

	for (int a = 0, b;a < n;a++)
	{
		in >> b;
		ref[a] = b;
		backlink.insert (make_pair (b, a));
		pos[0][a] = a;
	}

	for (int a = 1;a < 5;a++)
	{
		for (int b = 0, c;b < n;b++)
		{
			in >> c;
			pos[a][backlink.find (c)->second] = b;
		}
	}

	pair<int, int> after[20000]; //number of numbers that x succeeds
	memset (after, 0, sizeof (after));
	for (int a = 0;a < n;a++)
		after[a].second = a;
	for (int a = 0;a < n;a++)
	{
		for (int b = a + 1, cnt;b < n;b++)
		{
			cnt = 0; //number of times a is after b
			for (int c = 0;c < 5;c++)
				cnt += (pos[c][a] > pos[c][b]);

			if (cnt >= 3)
				after[a].first++;
			else
				after[b].first++;
		}
	}

	sort (after, after + n);
	for (int a = 0;a < n;a++)
		out << ref[after[a].second] << "\n";

	return 0;
}