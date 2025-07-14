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

	LL N;
	cin >> N;
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
		A[i]--;
	}
	vector<LL> B{A};
	sort(B.begin(), B.end());

	array<array<unordered_set<LL>, 4>, 4> S;
	RF(i, 0, N) {
		S[A[i]][B[i]].insert(i);
	}
	RF(i, 0, 4) {
		S[i][i].clear();
	}

	LL Z{0};
	RF(i, 0, N) {
		if (A[i] == B[i]) {
			continue;
		}
		if (!S[B[i]][A[i]].empty()) {
			LL Y{2}, path[]{i, *S[B[i]][A[i]].begin()};
			RF(z, 0, Y) {
				S[A[path[z]]][A[path[(z + 1) % Y]]].erase(path[z]);
			}
			RF(z, 0, Y - 1) {
				swap(A[path[z]], A[path[z + 1]]);
			}
			Z += Y - 1;
		}
	}
	RF(i, 0, N) {
		if (A[i] == B[i]) {
			continue;
		}
		RF(j, 0, 4) {
			if (!S[B[i]][j].empty()) {
				if (!S[j][A[i]].empty()) {
					LL Y{3}, path[]{i, *S[B[i]][j].begin(), *S[j][A[i]].begin()};
					RF(z, 0, Y) {
						S[A[path[z]]][A[path[(z + 1) % Y]]].erase(path[z]);
					}
					RF(z, 0, Y - 1) {
						swap(A[path[z]], A[path[z + 1]]);
					}
					Z += Y - 1;
				}
			}
		}
	}
	RF(i, 0, N) {
		if (A[i] == B[i]) {
			continue;
		}
		RF(j, 0, 4) {
			if (!S[B[i]][j].empty()) {
				RF(k, 0, 4) {
					if (!S[j][k].empty()) {
						if (!S[k][A[i]].empty()) {
							LL Y{4},
								path[]{
									i,
									*S[B[i]][j].begin(),
									*S[j][k].begin(),
									*S[k][A[i]].begin()};
							RF(z, 0, Y) {
								S[A[path[z]]][A[path[(z + 1) % Y]]].erase(path[z]);
							}
							RF(z, 0, Y - 1) {
								swap(A[path[z]], A[path[z + 1]]);
							}
							Z += Y - 1;
						}
					}
				}
			}
		}
	}
	cout << Z;
	return 0;
}
