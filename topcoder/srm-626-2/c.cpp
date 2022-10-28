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

class NegativeGraphDiv2
{
	public:
		long long findMin (int N, vector <int> s, vector <int> t, vector <int> weight, int charges)
		{
			long long dist[51][51];

			for (int a = 1;a <= N;a++)
				for (int b = 1;b <= N;b++)
					dist[a][b] = 1e13;

			for (int a = 0;a < s.size ();a++)
				dist[s[a]][t[a]] = min (dist[s[a]][t[a]], (long long)weight[a]);

			//Floyd.
			for (int a = 1;a <= N;a++)
				for (int b = 1;b <= N;b++)
					for (int c = 1;c <= N;c++)
						dist[b][c] = min (dist[b][c], dist[b][a] + dist[a][c]);

			//Init zero path.
			for (int a = 1;a <= N;a++)
				dist[a][a] = 0;

			//Copy and algorithm.
			long long ldist[1001][51];

			for (int i = 1; i <= N; i++)
			  ldist[0][i] = dist[i][N]; 

			//memcpy (ldist[0], dist[N], sizeof (dist[N]));
			for (int a = 1;a <= charges;a++)
			{
				for (int b = 1;b <= N;b++)
				{
					ldist[a][b] = ldist[a - 1][b];

					for (int c = 0;c < s.size ();c++)
						ldist[a][b] = min (ldist[a][b], dist[b][s[c]] - weight[c] + ldist[a - 1][t[c]]);
				}
			}

			return ldist[charges][1];
		}
};

bool KawigiEdit_RunTest(int testNum, int p0, vector <int> p1, vector <int> p2, vector <int> p3, int p4, bool hasAnswer, long long p5) {
	cout << "Test " << testNum << ": [" << p0 << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p1[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p2.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p2[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p3.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p3[i];
	}
	cout << "}" << "," << p4;
	cout << "]" << endl;
	NegativeGraphDiv2 *obj;
	long long answer;
	obj = new NegativeGraphDiv2();
	clock_t startTime = clock();
	answer = obj->findMin(p0, p1, p2, p3, p4);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p5 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p5;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;
	
	int p0;
	vector <int> p1;
	vector <int> p2;
	vector <int> p3;
	int p4;
	long long p5;
	
	{
	// ----- test 0 -----
	p0 = 3;
	int t1[] = {1,1,2,2,3,3};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {2,3,1,3,1,2};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {1,5,1,10,1,1};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 1;
	p5 = -9LL;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	p0 = 1;
	int t1[] = {1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {100};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 1000;
	p5 = -100000LL;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = 2;
	int t1[] = {1,1,2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {2,2,1};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {6,1,4};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 2;
	p5 = -9LL;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = 2;
	int t1[] = {1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {2};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {98765};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 100;
	p5 = -98765LL;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	cin.get ();
	return 0;
}