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
	cin.tie(nullptr);

	LL N;
	cin >> N;
	vector<LL> P(N);
	RF(i, 0, N) {
		cin >> P[i];
	}
	if (N == 1) {
		cout << 0 << '\n';
		return 0;
	}
	LL Z{0};

	vector<LL> up, down, pre(N);
	if (P[0] < P[1]) {
		up.push_back(1);
		down.push_back(0);
		pre[1] = 1;
		Z++;
	} else {
		up.push_back(0);
		down.push_back(1);
	}
	RF(i, 2, N) {
		if (P[i] > P[up.back()]) {
			while (!up.empty() && P[up.back()] < P[i]) {
				up.pop_back();
			}
			pre[i] = up.empty() ? i : i - up.back() - 1 + pre[up.back()];
			up.push_back(i);
			if (down.back() != i - 1) {
				down.push_back(i - 1);
			}
			Z += pre[i];
		} else if (P[i] < P[down.back()]) {
			while (!down.empty() && P[down.back()] > P[i]) {
				down.pop_back();
			}
			if (up.back() != i - 1) {
				pre[i - 1] =
					down.empty() ? 0LL : pre[up.back()] + down.back() - up.back();
				up.push_back(i - 1);
			}
			down.push_back(i);
			Z += pre[up.back()];
		} else {
			if (P[i] > P[i - 1]) {
				pre[i] = pre[up.back()] + down.back() - up.back();
				up.push_back(i);
				Z += pre[i];
			} else {
				down.push_back(i);
				Z += pre[up.back()];
			}
		}
	}

	cout << Z << '\n';
	return 0;
}
