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

int main()
{
	ios_base::sync_with_stdio(false);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	map<char, int> CHARMAP;
	CHARMAP['R'] = 0;
	CHARMAP['P'] = 1;
	CHARMAP['S'] = 2;

	map<int, char> INTMAP;
	INTMAP[1] = 'R';
	INTMAP[2] = 'P';
	INTMAP[4] = 'S';

	int T;
	cin >> T;

	for (int a = 0; a < T; a++) {
		int A;
		cin >> A;
		vector<string> seqs(A);
		for (int b = 0; b < A; b++) {
			cin >> seqs[b];
		}

		cout << "Case #" << a + 1 << ": ";

		string sol;
		for (int b = 0; b < 500; b++) {
			int lim = 0;
			for (int c = 0; c < seqs.size(); c++) {
				lim |= 1 << (CHARMAP[seqs[c][b % seqs[c].length()]]);
			}
			int ct = bitset<3>(lim).count();

			if (ct == 1) {
				cout << sol << INTMAP[1 << ((CHARMAP[INTMAP[lim]] + 1) % 3)];
				break;
			} else if (ct == 3) {
				cout << "IMPOSSIBLE";
				break;
			} else {
				sol += INTMAP[1 << ((CHARMAP[INTMAP[7 - lim]] + 2) % 3)];
				for (int c = seqs.size() - 1; c >= 0; c--) {
					if (INTMAP[1 << ((CHARMAP[seqs[c][b % seqs[c].length()]] + 1) % 3)] == sol.back()) {
						seqs.erase(seqs.begin() + c);
					}
				}
			}
		}

		cout << "\n";
	}

	return 0;
}