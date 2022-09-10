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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	string buffer;
	while (getline (cin, buffer))
	{
		stringstream ss;
		ss << buffer;
		cout << buffer << "\n";

		vector<int> list;
		int x;
		while (ss >> x)
			list.push_back (x);

		for (int a = list.size ();a > 1;a--)
		{
			int b = max_element (list.begin (), list.begin () + a) - list.begin ();
			if (b == a - 1)
				continue;
			else if (b != 0)
			{
				cout << list.size () - b << " ";
				reverse (list.begin (), list.begin () + b + 1);
			}
			cout << list.size () - a + 1 << " ";
			reverse (list.begin (), list.begin () + a);
		}

		cout << "0\n";
	}

	return 0;
}