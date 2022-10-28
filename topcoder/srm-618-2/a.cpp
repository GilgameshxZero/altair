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

class WritingWords
{
	public:
		int write(string word)
		{
			int ans = 0;
			for (int a = 0;a < word.size ();a++)
				ans += word[a] - 'A' + 1;

			return ans;
		}
};