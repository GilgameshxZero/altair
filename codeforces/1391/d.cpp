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
  freopen("d.0.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int N, M;
  cin >> N >> M;

  vector<string> mat(N);
  for (int a = 0; a < N; a++) {
    cin >> mat[a];
  }

  vector<vector<int>> bm(min(N, M), vector<int>(max(N, M)));
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < M; c++) {
      if (N > M) {
        bm[c][r] = mat[r][c] - '0';
      } else {
        bm[r][c] = mat[r][c] - '0';
      }
    }
  }

  if (min(N, M) == 1) {
    cout << 0;
  } else if (min(N, M) == 2) {
    vector<int> colpar(bm[0].size(), 0);
    for(int a = 0; a < bm[0].size(); a++) {
      colpar[a] = (bm[0][a] + bm[1][a]) % 2;
    }

    int ans = N * M;

    // Start with o.
    set<int> chidx;
    for (int a = 0; a < colpar.size(); a++) {
      if (colpar[a] != (a + 1) % 2) {
        chidx.insert(a);
      }
    }
    ans = min(ans, (int)chidx.size());
    // Start with e.
    chidx.clear();
    for (int a = 0; a < colpar.size(); a++) {
      if (colpar[a] != a % 2) {
        chidx.insert(a);
      }
    }
    ans = min(ans, (int)chidx.size());

    cout << ans;
  } else if (min(N, M) == 3) {
    vector<int> colpar[2];
    colpar[0].resize(bm[0].size());
    colpar[1].resize(bm[0].size());
    for(int a = 0; a < bm[0].size(); a++) {
      colpar[0][a] = (bm[0][a] + bm[1][a]) % 2;
      colpar[1][a] = (bm[1][a] + bm[2][a]) % 2;
    }

    int ans = N * M;

    // Start with o on top.
    set<int> chidx[2];
    for (int a = 0; a < colpar[0].size(); a++) {
      if (colpar[0][a] != (a + 1) % 2) {
        chidx[0].insert(a);
      }
    }

    // o on bottom?
    chidx[1] = chidx[0];
    for (int a = 0; a < colpar[1].size(); a++) {
      if (colpar[1][a] != (a + 1) % 2) {
        chidx[1].insert(a);
      }
    }
    ans = min(ans, (int)chidx[1].size());

    // e on bottom?
    for (int a = 0; a < colpar[1].size(); a++) {
      if (colpar[1][a] != a % 2) {
        chidx[0].insert(a);
      }
    }
    ans = min(ans, (int)chidx[0].size());

    // Start with e on top.
    chidx[0].clear();
    for (int a = 0; a < colpar[0].size(); a++) {
      if (colpar[0][a] != a % 2) {
        chidx[0].insert(a);
      }
    }

    // o on bottom?
    chidx[1] = chidx[0];
    for (int a = 0; a < colpar[1].size(); a++) {
      if (colpar[1][a] != (a + 1) % 2) {
        chidx[1].insert(a);
      }
    }
    ans = min(ans, (int)chidx[1].size());

    // e on bottom?
    for (int a = 0; a < colpar[1].size(); a++) {
      if (colpar[1][a] != a % 2) {
        chidx[0].insert(a);
      }
    }
    ans = min(ans, (int)chidx[0].size());

    cout << ans;
  } else {
    cout << -1;
  }

  return 0;
}
