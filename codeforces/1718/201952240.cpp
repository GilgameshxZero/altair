#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp(x) make_pair(x)
#define ll long long
#define pll pair <ll, ll>
#define pii pair <int, int>
#define all(x) x.begin(), x.end()
// #define size(x) x.size()
#define debug(x) cerr << "DEBUG : " << #x << " -> " << x << '\n';  
const long long N = 2e5 + 5, mod = 1e9 + 7, inf = 2e18 + 5, maxseglen = 2e5 + 5, K = 18;
// vector <int> adj[N];


void solve () {
    int n; cin >> n;
    vector <ll> a (n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    map <ll, bool> mp = {{0, true}};
    ll sum = 0, ans = n;
    for (int i = 0; i < n; i++) {
        sum ^= a[i];
        if (mp[sum]) {
            ans--;
            mp.clear();
            sum = 0;
            mp[0] = 1;
        }
        mp[sum] = 1;
    }
    
    cout << ans << '\n';
}   


int main(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int I_I = 1; 
    cin >> I_I;
    while (I_I--)
        solve();
    return 0^0;
}
/*
1
10
27 27 34 32 2 31 23 56 52 4
1
5
1822 1799 57 23 55
1
4
5 5 5 5


*/  
