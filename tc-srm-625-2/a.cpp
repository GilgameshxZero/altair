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

class AddMultiply
{
	public:
		vector<int> makeExpression (int y)
		{
			vector<int> v;
			
			for (int a = -1000;a <= 1000;a++)
			{
				for (int b = -1000;b <= 1000;b++)
				{
					if (a != 0 && a != 1 && b != 0 && b != 1 && 
						y - a * b != 0 && y - a * b != 1 && y - a * b >= -1000 && y - a * b <= 1000)
					{
						v.push_back (a);
						v.push_back (b);
						v.push_back (y - a * b);
						return v;
					}
				}
			}
		}
};