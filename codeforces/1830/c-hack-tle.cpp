#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define nf endl
#define ll long long
#define pb push_back
#define _ << ' ' <<

#define INF (ll)1e18
#define mod 998244353
#define maxn 110

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    #if !ONLINE_JUDGE && !EVAL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #endif

    int t = 1;
    cout << t << endl;
    while(t--){
        int n = (int)3e5-2;
        cout << n << " " << n / 2 << "\n";
        for(int i = 0 ; i < n / 2 ; i++) {
            cout << i + 1 << " " << i + (n / 2) + 1 << "\n";
        }
    }
    return 0;

    return 0;
}
