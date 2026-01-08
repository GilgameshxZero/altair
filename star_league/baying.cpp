//Solution by Yang Yan
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;

int main ()
{
	freopen ("baying.in", "r", stdin);
	freopen ("baying.out", "w", stdout);

	ll init;
	int n;
	cin >> init >> n;

	ll a1, b1, d1, a2, b2, d2;
	cin >> a1 >> b1 >> d1 >> a2 >> b2 >> d2;

	int pt1 = 0, pt2 = 0;
	ll k1, k2;

	vector<ll> list (n);
	list[0] = init;
	n--;
	k1 = a1 * list[pt1] / d1 + b1;
	k2 = a2 * list[pt2] / d2 + b2;
	for (int a = 0;a < n;a++)
	{
		if (k1 == k2)
			pt1++, pt2++,
			list[a + 1] = k1,
			k1 = a1 * list[pt1] / d1 + b1,
			k2 = a2 * list[pt2] / d2 + b2;
		else if (k1 > k2)
			pt2++,
			list[a + 1] = k2,
			k2 = a2 * list[pt2] / d2 + b2;
		else
			pt1++,
			list[a + 1] = k1,
			k1 = a1 * list[pt1] / d1 + b1;
	}

	cout << list.back () << "\n";

	return 0;
}