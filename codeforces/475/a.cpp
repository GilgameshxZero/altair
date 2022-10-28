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

	int k, x;
	cin >> k;

	cout << "+------------------------+\n";
	if (k < 1)
		cout << "|#.#.#.#.#.#.#.#.#.#.#.|D|)\n";
	else if (k < 5)
		cout << "|O.#.#.#.#.#.#.#.#.#.#.|D|)\n";
	else
	{
		cout << "|O.";
		for (x = 5;x <= k;x += 3)
			cout << "O.";
		for (;x <= 34;x += 3)
			cout << "#.";
		cout << "|D|)\n";
	}

	if (k < 2)
		cout << "|#.#.#.#.#.#.#.#.#.#.#.|.|\n";
	else if (k < 6)
		cout << "|O.#.#.#.#.#.#.#.#.#.#.|.|\n";
	else
	{
		cout << "|O.";
		for (x = 6;x <= k;x += 3)
			cout << "O.";
		for (;x <= 34;x += 3)
			cout << "#.";
		cout << "|.|\n";
	}

	if (k < 3)
		cout << "|#.......................|\n";
	else
		cout << "|O.......................|\n";

	if (k < 4)
		cout << "|#.#.#.#.#.#.#.#.#.#.#.|.|)\n";
	else if (k < 7)
		cout << "|O.#.#.#.#.#.#.#.#.#.#.|.|)\n";
	else
	{
		cout << "|O.";
		for (x = 7;x <= k;x += 3)
			cout << "O.";
		for (;x <= 34;x += 3)
			cout << "#.";
		cout << "|.|)\n";
	}

	cout << "+------------------------+";

	return 0;
}