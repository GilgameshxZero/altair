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

const int MOD = 1e9 + 9,
	NODES = 1048577;

//segtree, 0 is unused
//524288 nodes, double size + 1
int arr[NODES], lazy[NODES][2], 
	fib[300001], 
	start_x;
pair<int, int> range[NODES];

//note: F(x, y, z) = f(z - 2) * x + f(z - 1) * y, and sigma(F) = F(k + 2) - F(2)
int IrrFib (int x, int y, int num)
{
	if (num == 1)
		return x;
	else if (num == 2)
		return y;
	else
		return (int)((((long long)fib[num - 2] * x) % MOD + (long long)fib[num - 1] * y) % MOD);
}

int SumFib (int x, int y, int num)
{
	return (IrrFib (x, y, num + 2) - y + MOD) % MOD;
}

void PropagateLazy (int root)
{
	int left = root * 2, right = left + 1;

	lazy[left][0] = (lazy[left][0] + lazy[root][0]) % MOD;
	lazy[left][1] = (lazy[left][1] + lazy[root][1]) % MOD;
	lazy[right][0] = (lazy[right][0] + IrrFib (lazy[root][0], lazy[root][1], range[right].first - range[root].first + 1)) % MOD;
	lazy[right][1] = (lazy[right][1] + IrrFib (lazy[root][0], lazy[root][1], range[right].first - range[root].first + 2)) % MOD;
	lazy[root][0] = lazy[root][1] = 0;
}

void Update (int root, int x, int y, int first, int last) //inclusive, first and last will be in range
{
	int left = root * 2, right = left + 1;
	
	if (first == range[root].first && last == range[root].second) //spans entire range
	{
		if (first == last) //single node
			arr[root] = (arr[root] + x) % MOD;
		else
		{
			lazy[root][0] = (lazy[root][0] + x) % MOD;
			lazy[root][1] = (lazy[root][1] + y) % MOD;
		}
	}
	else if (last <= range[left].second)
	{
		PropagateLazy (root);
		Update (left, x, y, first, last);
		arr[root] = (int)(((long long)(arr[left]) + arr[right] + 
			SumFib (lazy[left][0], lazy[left][1], range[left].second - range[left].first + 1) + 
			SumFib (lazy[right][0], lazy[right][1], range[right].second - range[right].first + 1)) % MOD);
	}
	else if (first >= range[right].first)
	{
		PropagateLazy (root);
		Update (right, x, y, first, last);
		arr[root] = (int)(((long long)(arr[left]) + arr[right] + 
			SumFib (lazy[left][0], lazy[left][1], range[left].second - range[left].first + 1) + 
			SumFib (lazy[right][0], lazy[right][1], range[right].second - range[right].first + 1)) % MOD);
	}
	else //spans across middle line
	{
		PropagateLazy (root);
		Update (left, x, y, first, range[left].second);
		Update (right, 
			IrrFib (x, y, range[right].first - first + 1), IrrFib (x, y, range[right].first - first + 2), 
			range[right].first, last);
		arr[root] = (int)(((long long)(arr[left]) + arr[right] + 
			SumFib (lazy[left][0], lazy[left][1], range[left].second - range[left].first + 1) + 
			SumFib (lazy[right][0], lazy[right][1], range[right].second - range[right].first + 1)) % MOD);
	}
}

int Get (int root, int first, int last)
{
	int left = root * 2, right = left + 1;
	
	if (first == range[root].first && last == range[root].second) //covers entire range
		return (arr[root] + SumFib (lazy[root][0], lazy[root][1], range[root].second - range[root].first + 1)) % MOD;
	else if (last <= range[left].second)
	{
		//before propagation update root
		arr[root] = (arr[root] + SumFib (lazy[root][0], lazy[root][1], range[root].second - range[root].first + 1)) % MOD;
		PropagateLazy (root);
		return Get (left, first, last);
	}
	else if (first >= range[right].first)
	{
		arr[root] = (arr[root] + SumFib (lazy[root][0], lazy[root][1], range[root].second - range[root].first + 1)) % MOD;
		PropagateLazy (root);
		return Get (right, first, last);
	}
	else //spans across middle line
	{
		arr[root] = (arr[root] + SumFib (lazy[root][0], lazy[root][1], range[root].second - range[root].first + 1)) % MOD;
		PropagateLazy (root);
		return (Get (left, first, range[left].second) + Get (right, range[right].first, last)) % MOD;
	}
}

void InitSTree (int root)
{
	if (root >= start_x)
		return;

	int mid = (range[root].first + range[root].second) / 2;
	range[root * 2] = make_pair (range[root].first, mid);
	range[root * 2 + 1] = make_pair (mid + 1, range[root].second);

	InitSTree (root * 2);
	InitSTree (root * 2 + 1);
	arr[root] = (arr[root * 2] + arr[root * 2 + 1]) % MOD;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input3.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	fib[1] = fib[2] = 1;
	for (int a = 3;a <= 300000;a++)
		fib[a] = (fib[a - 1] + fib[a - 2]) % MOD;

	int n, m;
	cin >> n >> m;

	start_x = n;
	while (true)
	{
		if (start_x == (start_x & -start_x))
			break;
		else
			start_x -= (start_x & -start_x);
	}

	start_x *= 2;

	for (int a = 0;a < n;a++)
		cin >> arr[start_x + a];
	
	range[1].first = 1;
	range[1].second = start_x;
	InitSTree (1);

	for (int a = 0;a < m;a++)
	{
		int b, c, d;
		cin >> b >> c >> d;
		if (b == 1)
			Update (1, 1, 1, c, d);
		else
			cout << Get (1, c, d) << "\n";
	}

	return 0;
}