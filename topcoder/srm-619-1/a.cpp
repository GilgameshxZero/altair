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

class SplitStoneGame
{
	public:
		string winOrLose(vector<int> number)
		{
			int n = number.size();
			if ( (n % 2 == 0) || (n <= 2) || (number == vector<int>(n, 1)) ) {
				return "LOSE";
			} else {
				return "WIN";
			}
		}
};