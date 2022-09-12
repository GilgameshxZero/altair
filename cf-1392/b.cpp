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

  ll T;
  cin >> T;

  vector<ll> arr;
  while (T--) {
    ll N, K;
    cin >> N >> K;
    arr.resize(N);

    ll arrMax = -2000000000;
    for (ll a = 0; a < N; a++) {
      cin >> arr[a];
      arrMax = max(arrMax, arr[a]);
    }

    K--;
    ll newArrMax = -2000000000;
    for (ll a = 0; a < N; a++) {
      arr[a] = arrMax - arr[a];
      newArrMax = max(newArrMax, arr[a]);
    }

    K %= 2;
    if (K == 1) {
      K--;
      for (ll a = 0; a < N; a++) {
        arr[a] = newArrMax - arr[a];
      }
    }

    for (ll a = 0; a < N; a++) {
      cout << arr[a] << " ";
    }
    cout << "\n";
  }

  return 0;
}
