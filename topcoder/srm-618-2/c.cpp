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

class MovingRooksDiv2
{
	public:
		string move(vector <int> Y1, vector <int> Y2)
		{
			//count inversions
			vector< pair<int, int> > inv1, inv2;
			for (int a = 0;a < Y1.size ();a++)
				for (int b = a + 1;b < Y1.size ();b++)
					if (Y1[a] > Y1[b])
						inv1.push_back (make_pair (Y1[a], Y1[b]));
			for (int a = 0;a < Y2.size ();a++)
				for (int b = a + 1;b < Y2.size ();b++)
					if (Y2[a] > Y2[b])
						inv2.push_back (make_pair (Y2[a], Y2[b]));

			//make sure all of inv1 are in inv2
			for (int a = 0;a < inv1.size ();a++)
			{
				bool f1 = false;
				for (int b = 0;b < inv2.size ();b++)
					if (inv2[b] == inv1[a])
						f1 = true;

				if (!f1)
					return "Impossible";
			}

			return "Possible";
		}
};

// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <int> p0, vector <int> p1, bool hasAnswer, string p2) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p1[i];
	}
	cout << "}";
	cout << "]" << endl;
	MovingRooksDiv2 *obj;
	string answer;
	obj = new MovingRooksDiv2();
	clock_t startTime = clock();
	answer = obj->move(p0, p1);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << "\"" << p2 << "\"" << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << "\"" << answer << "\"" << endl;
	if (hasAnswer) {
		res = answer == p2;
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
	
	vector <int> p0;
	vector <int> p1;
	string p2;
	
	{
	// ----- test 0 -----
	int t0[] = {0};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "Possible";
	all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	int t0[] = {1,0};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "Possible";
	all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	int t0[] = {0,1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {1,0};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "Impossible";
	all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	int t0[] = {3,1,2,0};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,2,1,3};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "Possible";
	all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	int t0[] = {3,1,2,0};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {3,2,0,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "Impossible";
	all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	int t0[] = {6, 7, 5, 4, 3, 2, 1, 0};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {7, 0, 1, 2, 3, 4, 5, 6};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "Impossible";
	all_right = KawigiEdit_RunTest(5, p0, p1, true, p2) && all_right;
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