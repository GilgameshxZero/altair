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
  freopen("b.0.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int T;
  cin >> T;
  while (T--) {
    int N, M;
    cin >> N >> M;
    cin.get();

    int ans = 0;
    for (int a = 0; a < N; a++) {
      string s;
      cin >> s;

      if (a != N - 1) {
        ans += s[M - 1] == 'R';
      } else {
        for (int b = 0; b < M - 1; b++) {
          ans += s[b] == 'D';
        }
      }
    }

    cout << ans << "\n";
  }

  return 0;
}
