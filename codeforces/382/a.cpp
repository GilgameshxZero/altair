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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	string x, y, z;
	char tc;

	while ((tc = cin.get ()) != '|')
		x += tc;
	while ((tc = cin.get ()) != '\n')
		y += tc;
	cin >> z;

	if ((x.length () + y.length () + z.length ()) % 2 != 0 || max (x.length (), y.length ()) > (x.length () + y.length () + z.length ()) / 2)
	{
		cout << "Impossible\n";
		return 0;
	}


	int shit = (x.length () + y.length () + z.length ()) / 2, fuck = x.length ();
	x += z.substr (0, shit - x.length ());
	y += z.substr (shit - fuck, shit - y.length ());
	cout << x << "|" << y << "\n";

	return 0;
}