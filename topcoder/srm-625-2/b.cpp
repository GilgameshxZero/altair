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

//maximum bipartite matching w/ array
class IncrementingSequence
{
	public:
		int n, match[2][50];
		vector<int> edge[50];
		bool vis[50];

		bool DFS (int vert)
		{
			if (vert == -1) //this vert wasn't used
				return true;

			for (int a = 0;a < edge[vert].size ();a++)
			{
				if (!vis[edge[vert][a]])
				{
					vis[edge[vert][a]] = true;
					if (DFS (match[1][edge[vert][a]]))
					{
						match[1][edge[vert][a]] = vert;
						return true;
					}
				}
			}

			return false;
		}

		string canItBeDone (int k, vector<int> A)
		{
			n = A.size ();
			for (int a = 0;a < n;a++)
				match[0][a] = match[1][a] = -1;
			for (int a = 0;a < n;a++)
				for (int b = A[a];b <= n;b += k)
					edge[a].push_back (b - 1);

			for (int a = 0;a < n;a++)
			{
				//should not be matched yet
				assert (match[0][a] == -1);

				//dfs
				memset (vis, 0, sizeof (vis));
				if (!DFS (a))
					return "IMPOSSIBLE";
			}

			return "POSSIBLE";
		}
};

// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, int p0, vector <int> p1, bool hasAnswer, string p2) {
	cout << "Test " << testNum << ": [" << p0 << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p1[i];
	}
	cout << "}";
	cout << "]" << endl;
	IncrementingSequence *obj;
	string answer;
	obj = new IncrementingSequence();
	clock_t startTime = clock();
	answer = obj->canItBeDone(p0, p1);
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
	
	int p0;
	vector <int> p1;
	string p2;
	
	{
	// ----- test 0 -----
	p0 = 3;
	int t1[] = {1,2,4,3};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "POSSIBLE";
	all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	p0 = 5;
	int t1[] = {2,2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "IMPOSSIBLE";
	all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = 1;
	int t1[] = {1,1,1,1,1,1,1,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "POSSIBLE";
	all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = 2;
	int t1[] = {5,3,3,2,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "IMPOSSIBLE";
	all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	p0 = 9;
	int t1[] = {1,2,3,1,4,5,6,7,9,8};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "POSSIBLE";
	all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	p0 = 2;
	int t1[] = {1,1,1,1,1,1,2,2,2,2,2,2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "POSSIBLE";
	all_right = KawigiEdit_RunTest(5, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 6 -----
	p0 = 1;
	int t1[] = {1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "POSSIBLE";
	all_right = KawigiEdit_RunTest(6, p0, p1, true, p2) && all_right;
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