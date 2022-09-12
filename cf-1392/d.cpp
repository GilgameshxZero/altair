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
  freopen("d.0.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int T;
  cin >> T;
  while (T--) {
    int N;
    string S;
    cin >> N >> S;
    S.push_back(S[0]);
    S.push_back(S[1]);
    S.push_back(S[2]);
    S.push_back(S[3]);

    int bCutoff, finalAns = 1000000000;
    for (int start = 0; start < 4; start++) {
      for (int a = 0; a < 32; a++) {
        ans[0][a] = 1000000000;
      }
      ans[0][2] = (S[start] == 'R');
      ans[0][3] = (S[start] == 'L');

      for (int a = 1; a < N; a++) {
        for (int b = 4; b < 32; b++) {
          ans[a][b] = ans[a - 1][b / 2] + (S[start + a] == ((b % 2) ? 'L' : 'R'));
        }

        bCutoff = min(min(ans[a - 1][6], ans[a - 1][12]),
                      min(ans[a - 1][14], ans[a - 1][28]));
        ans[a][2] = bCutoff + (S[start + a] == 'R');
        ans[a][3] = bCutoff + (S[start + a] == 'L');
      }

      bCutoff = min(min(ans[N - 1][6], ans[N - 1][12]),
                    min(ans[N - 1][14], ans[N - 1][28]));
      finalAns = min(finalAns, bCutoff);
    }
    cout << finalAns << "\n";
  }

  return 0;
}
