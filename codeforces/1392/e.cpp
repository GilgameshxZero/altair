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

int ans[200000][32];

int main() {
  ios_base::sync_with_stdio(false);

#ifndef ONLINE_JUDGE
  freopen("e.0.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  ll N;
  cin >> N;

  vector<ll> digs;
  ll prod = 1;
  vector<vector<ll>> grid;
  grid.resize(N);

  for(ll a = 0; a < N; a++) {
    grid[a].resize(N);
  }

  set<ll> diags;
  map<ll, vector<pair<ll, ll>>> rev;
  ll split = 0;
  while (diags.size() < N) {
    for (ll a = 0; a <= (1 << (split)); a++) {
      ll diag = (a * N) / (1 << (split));
      if (diags.find(diag) != diags.end()) {
        continue;
      }

      diags.insert(diag);

      ll r = 0, c = diag, label = 0, maxLab = 0;
      for (; c >= 0; r++, c--, label = r % (N / (split + 1))) {
        if (r >= N || c >= N) {
          continue;
        }
        grid[r][c] = label * prod;
        maxLab = max(label, maxLab);

        if (rev.find(grid[r][c]) == rev.end()) {
          rev[grid[r][c]] = vector<pair<ll, ll>>();
        }
        rev[grid[r][c]].push_back(make_pair(r, c));
      }
      digs.push_back(maxLab + 1);
      prod *= maxLab + 1;
    }
    split++;
  }

  for (int a = 0; a < N; a++) {
    for (int b = 0; b < N; b++) {
      cout << grid[a][b] << " ";
    }
    cout << "\n";
  }
  cout.flush();

  return 0;
}
