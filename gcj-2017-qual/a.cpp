#define _CRT_SECURE_NO_WARNINGS

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



int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.in", "r", stdin);
	freopen ("output.out", "w", stdout);
#endif

	int t;
	cin >> t;

	for (int k = 1;k <= t;k++) {
		string s;
		cin >> s;

		int ans = 110;
		int x = 1 << s.size ();
		for (int a = 0;a < x;a++) {
			int b = a;
			for (int c = 0;c < s.size ();c++)
				if (a & (1 << c))
					for (int d = 

	return 0;
}