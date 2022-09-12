#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef pair<int, int> pii;

#define pb push_back

vector<pii> g[10000];
vector<int> res;
int d[10000];
bool u[10000];
int cnt[10000];

inline int foo(char a, char b)
{
    return (a-'0')*100+(b-'0');
}

void dfs(int v)
{
    u[v]=true;
    for(int i=0; i<g[v].size(); i++)
    {
        if(!u[g[v][i].first])
        dfs(g[v][i].first);
    }
}

void euler(int v)
{
    while(cnt[v]<g[v].size())
    {
        euler(g[v][cnt[v]++].first);
    }
    res.pb(v);
}

inline char qwe(int v)
{
    return (v%100)+'0';
}

int main()
{
    /*
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    /**/
    int n;
    sf(n);
    char s[4];
    int a,b;
    for(int i=0; i<n; i++)
    {
        scanf(" %s", s);
        a=foo(s[0],s[1]);
        b=foo(s[1],s[2]);
        g[a].pb(pii(b,0));
        d[b]++;
    }
    int f=0;
    int first=a;
    for(int i=0; i<10000; i++)
    {
        if(d[i]!=g[i].size())
        {
            if(abs(d[i]-(int)g[i].size())>1)
            {
                cout << "NO";
                return 0;
            }
            f++;
        }
        
        if(g[i].size()>d[i])
        first=i;
    }
    if(f>2)
    {
                cout << "NO";
        return 0;
    }
    dfs(first);
    for(int i=0; i<10000; i++)
    {
        if(g[i].size()||d[i])
        {
            if(!u[i])
            {
                cout << "NO";
                return 0;
            }
        }
    }
    euler(first);
                cout << "YES";
    printf("%c", (res[res.size()-1]/100)+'0');
    for(int i=res.size()-1; i>=0; i--)
    {
        printf("%c", qwe(res[i]));
    }
    return 0;
}