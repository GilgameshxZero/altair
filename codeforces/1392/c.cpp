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

  int T;
  cin >> T;

  vector<int> heights;
  while (T--) {
    int N;
    cin >> N;
    heights.resize(N);
    for (int a = 0; a < N; a++) {
      cin >> heights[a];
    }

    int minSub = heights.back();
    ll ops = 0;
    for (int a = heights.size() - 2; a >= 0; a--) {
      if (heights[a] > minSub) {
        ops += heights[a] - minSub;
      }
      minSub = heights[a];
    }
    cout << ops << "\n";
  }

  return 0;
}
