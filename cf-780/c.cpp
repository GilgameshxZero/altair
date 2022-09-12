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

int N, cColors;
vector<vector<int>> edges;
vector<int> colors;

void dfs(int V, int P) {
  int curColor = 1;

  for (int a = 0; a < edges[V].size(); a++) {
    if (edges[V][a] == P) {
      continue;
    }

    while (curColor == colors[V] || (P != -1 && curColor == colors[P])) {
      curColor++;
    }

    colors[edges[V][a]] = curColor++;
    dfs(edges[V][a], V);
  }
}

int main() {
  ios_base::sync_with_stdio(false);

#ifndef ONLINE_JUDGE
  freopen("c.0.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  cin >> N;
  edges.resize(N);
  colors.resize(N);

  for (int a = 0; a < N - 1; a++) {
    int X, Y;
    cin >> X >> Y;
    edges[X - 1].push_back(Y - 1);
    edges[Y - 1].push_back(X - 1);
  }

  for (int a = 0; a < edges.size(); a++) {
    cColors = max(cColors, (int)(edges[a].size() + 1));
  }
  cout << cColors << "\n";

  colors[0] = 1;
  dfs(0, -1);
  for (int a = 0; a < N; a++) {
    cout << colors[a] << " ";
  }

  return 0;
}
