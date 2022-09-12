#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;

int N, M;
vector<vector<int>> edges;
vector<int> component, compSizes;

void dfs(int V, int P) {
	for (int a = 0; a < edges[V].size(); a++) {
		if (edges[V][a] == P) {
			continue;
		}

		if (component[edges[V][a]] != -1) {
			continue;
		}

		component[edges[V][a]] = component[V];
		compSizes[component[V]]++;
		dfs(edges[V][a], V);
	}
}

int main() {
  ios_base::sync_with_stdio(false);

#ifndef ONLINE_JUDGE
  freopen("c.0.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  cin >> N >> M;
	edges.resize(N);

	for (int a = 0; a < M; a++) {
		int K;
		cin >> K;

		if (K == 0) {
			continue;
		}

		int X;
		cin >> X;
		for (int b = 0; b < K - 1; b++) {
			int Y;
			cin >> Y;
			edges[X - 1].push_back(Y - 1);
			edges[Y - 1].push_back(X - 1);
			X = Y;
		}
	}

	component.resize(N, -1);
	for (int a = 0; a < N; a++) {
		if (component[a] == -1) {
			component[a] = compSizes.size();
			compSizes.push_back(1);
			dfs(a, -1);
		}

		cout << compSizes[component[a]] << " ";
	}

  return 0;
}
