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

class HappyLetterDiv2
{
	public:
		char getHappyLetter(string letters)
		{
			int cnt[128];
			memset (cnt, 0, sizeof (cnt));
			for (int a = 0;a < letters.size ();a++)
				cnt[letters[a]]++;

			for (int a = 0;a < 128;a++)
				if (cnt[a] > letters.size () / 2)
					return (char)a;

			return '.';
		}
};