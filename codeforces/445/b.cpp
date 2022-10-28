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

int N, M, cComponents;
vector<vector<int>> edges;
vector<bool> visited;

void dfs(int V) {
  visited[V] = true;

	for (int a = 0; a < edges[V].size(); a++) {
		if (visited[edges[V][a]]) {
			continue;
		}

		dfs(edges[V][a]);
	}
}

int main() {
  ios_base::sync_with_stdio(false);

#ifndef ONLINE_JUDGE
  freopen("b.0.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  cin >> N >> M;
  edges.resize(N);
	visited.resize(N);

  for (int a = 0; a < M; a++) {
    int X, Y;
    cin >> X >> Y;
    edges[X - 1].push_back(Y - 1);
    edges[Y - 1].push_back(X - 1);
  }

  for (int a = 0; a < N; a++) {
		if (!visited[a]) {
			cComponents++;
			dfs(a);
		}
	}

	cout << (1LL << (N - cComponents));

  return 0;
}
