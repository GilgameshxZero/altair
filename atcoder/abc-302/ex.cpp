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

LL N, CC;
vector<LL> A, B, C, S, T;
vector<vector<LL>> E;

void add(LL U, LL V) {
	if (C[U] == C[V]) {
		T[C[U]]++;
	} else {
		S[C[V]] += S[C[U]];
		T[C[V]] += T[C[U]] + 1;
		C[U] = C[V];
	}
}

void remove(LL U, LL V) {
	if (T[C[U]] + 1 == S[C[U]]) {
		S.push_back
		CC++;
	} else {
		T[C[U]]--;
	}
}

void dfs(LL X, LL P) {
	
}

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N;
	A.resize(N);
	B.resize(N);
	C.resize(N);
	CC = N;
	RF(i, 0, N) {
		C[i] = i;
	}
	S.resize(N);
	fill(S.begin(), S.end(), 1);
	T.resize(N);
	E.resize(N);
	RF(i, 0, N) {
		cin >> A[i] >> B[i];
		A[i]--;
		B[i];
	}
	RF(i, 0, N) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].push_back(V - 1);
		E[V - 1].push_back(U - 1);
	}

	dfs(0, -1);

	return 0;
}
