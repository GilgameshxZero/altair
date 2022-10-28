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

int N;

// true: forward edge; false: backward edge.
vector<vector<pair<int, bool>>> edges;

// # of backwards edges on path from 0 to V.
vector<int> cBackwardsTo, depth;

// Return number of backward edges in V's subtree.
int dfs(int V, int P, int D) {
  depth[V] = D;

  int cSubtreeBackwards = 0;
  for (int a = 0; a < edges[V].size(); a++) {
    if (edges[V][a].first == P) {
      continue;
    }

    cBackwardsTo[edges[V][a].first] =
        cBackwardsTo[V] + (edges[V][a].second == false);
    cSubtreeBackwards +=
        dfs(edges[V][a].first, V, D + 1) + (edges[V][a].second == false);
  }

  return cSubtreeBackwards;
}

int main() {
  ios_base::sync_with_stdio(false);

#ifndef ONLINE_JUDGE
  freopen("d.0.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  cin >> N;
  edges.resize(N);
  cBackwardsTo.resize(N);
  depth.resize(N);
  for (int a = 0; a < N - 1; a++) {
    int X, Y;
    cin >> X >> Y;
    edges[X - 1].push_back(make_pair(Y - 1, true));
    edges[Y - 1].push_back(make_pair(X - 1, false));
  }

  int totalBackwards = dfs(0, -1, 0);
  vector<int> inverses(N);
  int minInverse = N;
  for (int a = 0; a < N; a++) {
    inverses[a] = totalBackwards - 2 * cBackwardsTo[a] + depth[a];
    minInverse = min(minInverse, inverses[a]);
  }

  cout << minInverse << "\n";
  for (int a = 0; a < N; a++) {
    if (minInverse == inverses[a]) {
      cout << a + 1 << " ";
    }
  }

  return 0;
}
