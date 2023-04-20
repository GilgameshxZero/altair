#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("O3", "unroll-loops")
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

	LL T;
	cin >> T;
	while (T--) {
		LL N, K;
		cin >> N >> K;
		vector<LL> SL(N), SR(N);
		RF(i, 0, N) {
			cin >> SL[i];
		}
		LL total{0};
		RF(i, 0, N) {
			cin >> SR[i];
			total += SR[i] - SL[i] + 1;
		}
		if (total < K) {
			cout << "-1\n";
			continue;
		}
		LL low{0}, high{INT_MAX}, mid;
		vector<LL> S(N);
		vector<bool> M(N);
		while (low + 1 < high) {
			mid = (low + high) / 2;

			fill(M.begin(), M.end(), false);
			priority_queue<pair<LL, LL>> PQU;
			RF(i, 0, N) {
				if (SL[i] > mid) {
					break;
				}
				if (SR[i] <= mid) {
					S[i] = SR[i] - SL[i] + 1;
				} else {
					S[i] = mid - SL[i] + 1;
				}
				PQU.push({S[i], i});
			}

			LL cur{0};
			auto kill{[&](LL i) {
				LL j(upper_bound(SL.begin(), SL.end(), i) - SL.begin());
				j--;
				if (j >= 0 && SR[j] >= i) {
					pair<LL, LL> cand{S[j], j};
					if (!M[j]) {
						S[j]--;
						PQU.push({S[j], j});
					} else {
						M[j] = false;
						cur -= S[j];
						S[j]--;
						PQU.push({S[j], j});
						while (true) {
							auto k{PQU.top()};
							if (S[k.second] == k.first) {
								break;
							}
							PQU.pop();
						}
						auto k{PQU.top()};
						PQU.pop();
						cur += k.first;
						M[k.second] = true;
					}
				}
			}};

			LL best{0};
			RF(i, 1, PQU.size() + 1) {
				if (mid - i * 2 < 0) {
					break;
				}
				kill(mid - i * 2 + 2);
				kill(mid - i * 2 + 1);

				while (true) {
					auto k{PQU.top()};
					if (S[k.second] == k.first) {
						break;
					}
					PQU.pop();
				}
				auto k{PQU.top()};
				PQU.pop();
				cur += k.first;
				M[k.second] = true;

				best = max(best, cur);
			}

			if (best >= K) {
				high = mid;
			} else {
				low = mid;
			}
		}
		cout << high << '\n';
	}

	return 0;
}
