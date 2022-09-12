#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int main ()
{
	//freopen ("input.txt", "r", stdin);
	//freopen ("output.txt", "w", stdout);
	int n, m;
	vector<pair<int, int> > v, r;

	cin >> n >> m;

	for (int a = 0, b;a < n;a++)
	{
		cin >> b;
		v.push_back (make_pair (b, a));
	}

	sort (v.begin (), v.end ());

	for (int a = 0;a < n;a++)
		r.push_back (make_pair (v[a].second, a % 2));

	sort (r.begin (), r.end ());

	for (int a = 0;a < n - 1;a++)
		cout << r[a].second << " ";
	cout << r[n - 1].second << "\n";

	return 0;
}