#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	// cin.tie(nullptr);

	LL N;
	cin >> N;
	string S(N, ' ');
	cout << "? 1 1" << endl;
	cin >> S[0];

	set<LL> P;
	array<LL, 26> C;
	C.fill(-1);
	C[S[0] - 'a'] = 0;
	P.insert(0);
	RF(i, 1, N) {
		cout << "? 2 1 " << i + 1 << endl;
		LL x;
		cin >> x;
		if (x > P.size()) {
			cout << "? 1 " << i + 1 << endl;
			cin >> S[i];
			C[S[i] - 'a'] = i;
			P.insert(i);
		} else {
			LL low{0}, high(P.size()), mid;
			while (low + 1 < high) {
				mid = (low + high) / 2;
				auto j{P.end()};
				RF(k, 0, mid) {
					j--;
				}
				cout << "? 2 " << *j + 1 << ' ' << i + 1 << endl;
				cin >> x;
				if (x == mid) {
					high = mid;
				} else {
					low = mid;
				}
			}

			auto j{P.end()};
			RF(k, 0, high) {
				j--;
			}
			RF(k, 0, 26) {
				if (C[k] == *j) {
					S[i] = k + 'a';
					C[k] = i;
					P.erase(j);
					P.insert(i);
					break;
				}
			}
		}
	}

	cout << "! " << S << endl;
	return 0;
}
