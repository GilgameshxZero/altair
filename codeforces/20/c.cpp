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

int main() {
  ios_base::sync_with_stdio(false);

#ifndef ONLINE_JUDGE
  freopen("c.0.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int N, M;
  cin >> N >> M;

  // Pair of (vertex, edge weight).
  vector<vector<pair<int, int> > > edges(N);
  for (int a = 0; a < M; a++) {
    int X, Y, C;
    cin >> X >> Y >> C;
    edges[X - 1].push_back(make_pair(Y - 1, C));
    edges[Y - 1].push_back(make_pair(X - 1, C));
  }

  vector<bool> visited(N, false);
  vector<ll> dist(N, 4000000000000000000), par(N, -1);

  // Pair of (priority, vertex).
  priority_queue<pair<int, int> > pq;
  dist[0] = 0;
  pq.push(make_pair(0, 0));
  while (!pq.empty()) {
    int V = pq.top().second;
    pq.pop();

    for (int a = 0; a < edges[V].size(); a++) {
      int neighbor = edges[V][a].first;
      if (dist[V] + edges[V][a].second < dist[neighbor]) {
        dist[neighbor] = dist[V] + edges[V][a].second;
        pq.push(make_pair(-dist[neighbor], neighbor));
        par[neighbor] = V;
      }
    }

    visited[V] = true;

    // Remove any visited elements at the front of queue.
    while (!pq.empty() && visited[pq.top().second]) {
      pq.pop();
    }
  }

  if (par[N - 1] == -1) {
    cout << "-1";
  } else {
    vector<int> path;
    int V = N - 1;
    while (V != -1) {
      path.push_back(V);
      V = par[V];
    }
    for (int a = path.size() - 1; a >= 0; a--) {
      cout << path[a] + 1 << " ";
    }
  }

  return 0;
}
