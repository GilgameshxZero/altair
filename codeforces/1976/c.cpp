#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, f, t)                                      \
	for (LL x(f), _t(t), _d{x < _t ? 1LL : -1LL}; x != _t; \
			 x += _d)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N >> M;
		vector<LL> A(N + M + 1), B(N + M + 1);
		RF(i, 0, N + M + 1) {
			cin >> A[i];
		}
		RF(i, 0, N + M + 1) {
			cin >> B[i];
		}
		LL force[2]{LLONG_MAX, LLONG_MAX}, score{0};
		vector<LL> p, t, pos(N + M + 1);
		RF(i, 0, N + M) {
			if (A[i] > B[i]) {
				if (p.size() == N) {
					t.push_back(i);
					force[1] = min(force[1], i);
					score += B[i];
					pos[i] = 1;
				} else {
					p.push_back(i);
					score += A[i];
					pos[i] = 0;
				}
			} else {
				if (t.size() == M) {
					p.push_back(i);
					force[0] = min(force[0], i);
					score += A[i];
					pos[i] = 0;
				} else {
					t.push_back(i);
					score += B[i];
					pos[i] = 1;
				}
			}
		}
		RF(i, 0, N + M) {
			LL ts{score};
			if (pos[i] == 0) {
				ts -= A[i];
				if (force[1] < LLONG_MAX) {
					ts -= B[force[1]] - A[force[1]];
					ts += B.back();
				} else {
					ts += A.back();
				}
			} else {
				ts -= B[i];
				if (force[0] < LLONG_MAX) {
					ts -= A[force[0]] - B[force[0]];
					ts += A.back();
				} else {
					ts += B.back();
				}
			}
			cout << ts << ' ';
		}
		cout << score << '\n';
	}

	return 0;
}
