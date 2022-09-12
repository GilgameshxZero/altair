/*
ID: yangchess1
PROG: hamming
LANG: C++
*/

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

int PopCount (int x)
{
	int r = 0;
	for (;x != 0;x >>= 1)
		if (x & 1)
			r++;
	return r;
}

int main ()
{
	ios_base::sync_with_stdio (false);
	std::freopen ("hamming.in", "r", stdin);
	std::freopen ("hamming.out", "w", stdout);

	vector<int> ans;
	int N, B, D;
	cin >> N >> B >> D;

	ans.push_back (0);
	for (int a = 1;ans.size () < N;a++)
	{
		bool flag = true;
		for (int b = 0;b < ans.size ();b++)
			if (PopCount (ans[b] ^ a) < D)
				flag = false;

		if (flag)
			ans.push_back (a);
	}

	for (int a = 0;a < N / 10;a++)
	{
		for (int b = 0;b < 9;b++)
			cout << ans[a * 10 + b] << " ";
		cout << ans[a * 10 + 9] << "\n";
	}
	for (int a = N - N % 10;a < N - 1;a++)
		cout << ans[a] << " ";
	if (N % 10 != 0)
		cout << ans[N - 1] << "\n";

	return 0;
}