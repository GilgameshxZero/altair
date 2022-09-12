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

int clen[100001];
int c2, c4, c6, c8;

void proc(int cnt, int dir) {
  if (cnt >= 2) c2 += dir;
  if (cnt >= 4) c4 += dir;
  if (cnt >= 6) c6 += dir;
  if (cnt >= 8) c8 += dir;
}

void upd(int len, int dir) {
  proc(clen[len], -1);
  clen[len] += dir;
  proc(clen[len], 1);
}

int main() {
  ios_base::sync_with_stdio(false);

#ifndef ONLINE_JUDGE
  freopen("b.0.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int N, Q;
  cin >> N;
  int tmp;
  for (int a = 0; a < N; a++) {
    cin >> tmp;
    upd(tmp, 1);
  }
  char c;
  cin >> Q;
  for (int a = 0; a < Q; a++) {
    cin >> c >> tmp;
    upd(tmp, c == '+' ? 1 : -1);
    if (c8 >= 1 || (c6 >= 1 && c2 - c6 >= 1) || c4 >= 2 || (c4 >= 1 && c2 - c4 >= 2)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

  return 0;
}
