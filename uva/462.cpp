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

int scnt[4], fcnt[4], scpd[128], ccpd[128];
bool fsex[4][4];
bool stp[4];
char srcpd[4];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.in", "r", stdin);
	freopen ("output.out", "w", stdout);
#endif

	scpd['S'] = 0;
	scpd['H'] = 1;
	scpd['D'] = 2;
	scpd['C'] = 3;
	srcpd[0] = 'S';
	srcpd[1] = 'H';
	srcpd[2] = 'D';
	srcpd[3] = 'C';
	for (int a = 0;a < 128;a++)
		ccpd[a] = a - '0';
	ccpd['A'] = 14;
	ccpd['T'] = 10;
	ccpd['J'] = 11;
	ccpd['Q'] = 12;
	ccpd['K'] = 13;
	int k = 0;
	string s;

	while (cin >> s)
	{
		//if (k)
			//cout << "\n";
		memset (scnt, 0, sizeof (scnt));
		memset (fcnt, 0, sizeof (fcnt));
		memset (fsex, 0, sizeof (fsex));
		memset (stp, 0, sizeof (stp));
		scnt[scpd[s[1]]]++;
		if (ccpd[s[0]] - 11 >= 0)
		{
			fcnt[ccpd[s[0]] - 11]++;
			fsex[scpd[s[1]]][ccpd[s[0]] - 11] = true;
		}
		int pttl = 0;
		for (int a = 1;a < 13;a++)
		{
			cin >> s;
			scnt[scpd[s[1]]]++;
			if (ccpd[s[0]] - 11 >= 0)
			{
				fcnt[ccpd[s[0]] - 11]++;
				fsex[scpd[s[1]]][ccpd[s[0]] - 11] = true;
			}
		}

		pttl = fcnt[0] + 2 * fcnt[1] + 3 * fcnt[2] + 4 * fcnt[3];
		for (int a = 0;a < 4;a++)
		{
			if (fsex[a][2] && scnt[a] == 1)
				pttl--;
			if (fsex[a][1] && scnt[a] <= 2)
				pttl--;
			if (fsex[a][0] && scnt[a] <= 3)
				pttl--;
			if (fsex[a][3] || (fsex[a][2] && scnt[a] > 1) || (fsex[a][1] && scnt[a] > 2))
				stp[a] = true;
		}

		int ptnt = pttl;
		for (int a = 0; a < 4; a++)
		{
			if (scnt[a] == 2)
				pttl++;
			if (scnt[a] < 2)
				pttl +=2;
		}

		if (pttl < 14)
			cout << "PASS";
		else if (stp[0] && stp[1] && stp[2] && stp[3] && ptnt >= 16)
			cout << "BID NO-TRUMP";
		else
		{
			vector<int> lg (1, 0);
			for (int a = 1;a < 4;a++)
				if (scnt[a] > scnt[lg[0]])
					lg.clear (), lg.push_back (a);
				else if (scnt[a] == scnt[lg[0]])
					lg.push_back (a);
			cout << "BID";
			for (int a = 0;a < lg.size ();a++)
			{
				cout << " " << srcpd[lg[a]];
				break;
			}
		}
		cout << "\n";
		k = 1;
	}

	return 0;
}