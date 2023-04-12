#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	// LL A, B;
	// cin >> A >> B;

	// auto cn7{[](LL cur) {
	// 	array<LL, 2> cnt;
	// 	cnt[0] = 1;
	// 	cnt[1] = 0;
	// 	LL fac{10000000000000};
	// 	while (fac >= 1) {
	// 		LL dig{(cur / fac) % 10};
	// 		fac /= 10;
	// 		decltype(cnt) c2;
	// 		c2[0] = c2[1] = 0;
	// 		RF(i, 0, 10) {
	// 			if (i == 7) {
	// 				continue;
	// 			}
	// 			if (i == dig) {
	// 				c2[0] += cnt[0];
	// 				c2[1] += cnt[1];
	// 			} else if (i < dig) {
	// 				c2[1] += cnt[0] + cnt[1];
	// 			} else {
	// 				c2[1] += cnt[1];
	// 			}
	// 		}
	// 		c2.swap(cnt);
	// 	}
	// 	return cnt[0] + cnt[1];
	// }};

	// cout << (B + 1 - cn7(B)) - (A - cn7(A - 1));

	// LL ans{0};
	// RF(i, A, B + 1) {
	// 	string S{to_string(i)};
	// 	bool has{false};
	// 	RF(j, 0, S.size()) {
	// 		has |= S[j] == '7';
	// 	}
	// 	ans += has;
	// }
	// cout << '\n' << ans;

	string A, B;
	LL a_, b_;
	cin >> a_ >> b_;
	A = to_string(a_ - 1);
	B = to_string(b_);
	RF(i, 0, A.size()) {
		if (A[i] >= '7') {
			A[i]--;
			if (A[i] == '6') {
				RF(j, i + 1, A.size()) {
					A[j] = '8';
				}
				break;
			}
		}
	}
	RF(i, 0, B.size()) {
		if (B[i] >= '7') {
			B[i]--;
			if (B[i] == '6') {
				RF(j, i + 1, B.size()) {
					B[j] = '8';
				}
				break;
			}
		}
	}

	LL a{0}, b{0};
	RF(i, 0, A.size()) {
		a = a * 9 + A[i] - '0';
	}
	RF(i, 0, B.size()) {
		b = b * 9 + B[i] - '0';
	}
	cout << b_ - a_ + 1 - (b - a);
	return 0;
}
