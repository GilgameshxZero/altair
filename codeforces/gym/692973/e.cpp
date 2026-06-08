#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
	// <https://codeforces.com/blog/entry/135127>.
	#include <string>
	#pragma GCC target("arch=core-avx2")
	#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for ( \
		LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
		x != _to; \
		x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		vector<vector<LL>> C;
		LL N;
		cin >> N;
		vector<LL> A(N), B(N);
		RF(i, 0, N) {
			cin >> A[i];
			A[i]--;
		}
		RF(i, 0, N) {
			cin >> B[i];
			B[i] = B[i] == -1 ? -1 : B[i] - 1;
		}
		{
			vector<bool> V(N);
			RF(i, 0, N) {
				if (V[i]) {
					continue;
				}
				V[i] = true;
				C.push_back({});
				C.back().push_back(i);
				for (LL j{A[i]}; j != i; j = A[j]) {
					V[j] = true;
					C.back().push_back(j);
				}
			}
		}
		sort(
			C.begin(),
			C.end(),
			[](vector<LL> const &left, vector<LL> const &right) {
				return left.size() < right.size();
			});
		vector<LL> RC(N), RCI(N);
		RF(i, 0, C.size()) {
			RF(j, 0, C[i].size()) {
				RC[C[i][j]] = i;
				RCI[C[i][j]] = j;
				// cout << C[i][j] << ' ';
			}
			// cout << '\n';
		}

		bool fail{false};
		vector<LL> BC(C.size(), -1);
		vector<LL> BCO(C.size(), -1);
		vector<bool> M(C.size());
		RF(i, 0, N) {
			if (B[i] == -1) {
				continue;
			}
			if (BC[RC[i]] == -1) {
				if (C[RC[i]].size() != C[RC[B[i]]].size()) {
					fail = true;
					break;
				}
				if (M[RC[B[i]]]) {
					fail = true;
					break;
				}
				BC[RC[i]] = RC[B[i]];
				M[RC[B[i]]] = true;
				BCO[RC[i]] =
					(RCI[B[i]] - RCI[i] + C[RC[i]].size()) %
					C[RC[i]].size();
			} else if (BC[RC[i]] != RC[B[i]]) {
				fail = true;
				break;
			} else if (
				BCO[RC[i]] !=
				(RCI[B[i]] - RCI[i] + C[RC[i]].size()) %
					C[RC[i]].size()) {
				fail = true;
				break;
			}
		}
		// cout << fail << '\n';
		// RF(i, 0, C.size()) { cout << BC[i] << ' '; }
		// cout << '\n';
		// RF(i, 0, C.size()) { cout << BCO[i] << ' '; }
		// cout << '\n';
		if (fail) {
			cout << "NO\n";
			continue;
		}

		{
			RF(i, BC.size() - 1, -1) {
				while (!M.empty() && M.back()) {
					M.pop_back();
				}
				if (BC[i] != -1) {
					continue;
				}
				BC[i] = M.size() - 1;
				M.pop_back();
			}
			// cout << M.size() << '\n';
			RF(i, 0, C.size()) {
				BCO[i] = BCO[i] == -1 ? 0 : BCO[i];
			}
		}

		cout << "YES\n";
		RF(i, 0, N) {
			if (B[i] == -1) {
				B[i] =
					C[BC[RC[i]]]
					 [(RCI[i] + BCO[RC[i]]) % C[BC[RC[i]]].size()];
			}
			cout << B[i] + 1 << ' ';
		}
		cout << '\n';
	}

	return 0;
}
