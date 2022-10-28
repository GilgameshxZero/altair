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

  vector<int> cpc;
  while (T--) {
    int N;
    cin >> N;
    cpc.clear();
    cpc.resize(N + 1);

    int tmp, bpc = 0, cbpc = 0;
    while (N--) {
      cin >> tmp;
      ++cpc[tmp];
      if (cpc[tmp] > bpc) {
        bpc = cpc[tmp];
        cbpc = 1;
      } else if (cpc[tmp] == bpc) {
        cbpc++;
      }
    }
    cout << floor(((double)cpc.size() - cbpc - 1) / (bpc - 1)) - 1 << "\n";
  }

  return 0;
}
