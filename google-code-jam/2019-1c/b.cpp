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

	int T;
	cin >> T;

	for (int a = 0; a < T; a++) {
		int F;
		cin >> F;

		map<char, int> ct[4];
		string resp[5];
		string crit(5, '_');

		for (int c = 0; c < 4; c++) {
			resp[c] = string(119, ' ');
			for (int b = 0; b < 119; b++) {
				if (c == 0 || resp[c - 1][b] == crit[c - 1]) {
					cout << b * 5 + c + 1 << "\n";
					cin >> resp[c][b];
					ct[c][resp[c][b]]++;
				}
			}
			for (char b = 'A'; b <= 'E'; b++) {
				if ((b != crit[0] && b != crit[1] && b != crit[2] && b != crit[3]) && (ct[c][b] < ct[c]['A'] || ct[c][b] < ct[c]['B'] || ct[c][b] < ct[c]['C'] || ct[c][b] < ct[c]['D'] || ct[c][b] < ct[c]['E'])) {
					crit[c] = b;
				}
			}
		}

		crit[4] = (char)('A' - crit[0] + 'B' - crit[1] + 'C' - crit[2] + 'D' - crit[3] + 'E');
		cout << crit << "\n";
		cin >> resp[5];

		if (resp[5] == "N") {
			break;
		}
	}

	return 0;
}