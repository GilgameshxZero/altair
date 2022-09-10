#include <stdio.h>
int arr[400005]; int mini[400005]; int dp[400005]; int backsum[400005]; 
int main()
{
    freopen("input0.txt", "r", stdin);
    freopen("output.txt", "w", stdout); 
    int g, x;
    for (g=0; g<=200000; g++) 
    {mini[g]=1e9;} 
    int a; scanf("%d", &a); if (a==0) {puts("0"); return 0;}
    for (g=1; g<=a; g++) scanf("%d", &arr[g]); 
    for (g=a; g>=1; g--) backsum[g]=arr[g]+backsum[g+1]; 
    int b; scanf("%d", &b); 
    for (g=0; g<b; g++)
    {
        int c,d; scanf("%d %d", &c, &d);
        if (d==0) continue; 
        int l; if (c-d+1<=0) l=0; else l=c-d+1; 
        for (x=l; x<=c; x++) {if (d<mini[x]) mini[x]=d; }
    }
    for (g=a; g>=1; g--)
    {
        dp[g]=dp[g+1]; 
        if (mini[g]==1e9 || mini[g]<=0) continue; 
        int t=backsum[g]-backsum[mini[g]+g]+dp[mini[g]+g];
        if (t>dp[g])dp[g]=t; 
    }
    printf("%d", dp[1]); return 0; 
}
