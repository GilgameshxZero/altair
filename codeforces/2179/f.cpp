#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

string const O{"rgb"};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string _R;
	cin >> _R;
	if (_R == "first") {
		LL _T;
		cin >> _T;
		while (_T--) {
			LL N, M;
			cin >> N >> M;
			vector<vector<LL>> E(N);
			RF(i, 0, M) {
				LL U, V;
				cin >> U >> V;
				U--;
				V--;
				E[U].push_back(V);
				E[V].push_back(U);
			}
			vector<LL> Y(N, -1);
			Y[0] = 0;
			queue<LL> Q;
			Q.push(0);
			while (!Q.empty()) {
				LL U{Q.front()};
				Q.pop();
				for (auto &j : E[U]) {
					if (Y[j] == -1) {
						Y[j] = (Y[U] + 1) % 3;
						Q.push(j);
					}
				}
			}
			RF(i, 0, N) {
				cout << O[Y[i]];
			}
			cout << '\n';
		}
	} else {
		LL _T;
		cin >> _T;
		while (_T--) {
			LL Q;
			cin >> Q;
			RF(i, 0, Q) {
				LL D;
				cin >> D;
				string S;
				cin >> S;
				bool H[3]{};
				RF(j, 0, D) {
					if (S[j] == 'r') {
						H[0] = true;
					} else if (S[j] == 'g') {
						H[1] = true;
					} else {
						H[2] = true;
					}
				}
				if (H[0] + H[1] + H[2] == 1) {
					cout << "1\n";
				} else {
					char C;
					RF(j, 0, 3) {
						if (!H[j]) {
							C = O[(j + 2) % 3];
						}
					}
					RF(j, 0, D) {
						if (S[j] == C) {
							cout << j + 1 << '\n';
							break;
						}
					}
				}
			}
		}
	}

	return 0;
}
