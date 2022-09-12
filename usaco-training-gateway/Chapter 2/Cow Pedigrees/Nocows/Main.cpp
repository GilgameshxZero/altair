/*
ID: yangchess1
PROG: nocows
LANG: C++
*/
//Again, my version won't work somehow

#include <fstream>
#include <string>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
//
//int main ()
//{
//	ifstream in;
//	ofstream out;
//	unsigned short nodes, height, trees[101][202], smalltrees[101][202], multiplier, a, b, c;
//
//	for (a = 0;a < 101;a++)
//		for (b = 0;b < 202;b++)
//			trees[a][b] = smalltrees[a][b] = 0;
//
//	trees[1][1] = 1;
//
//	in.open ("nocows.in");
//	in >> nodes >> height;
//	in.close ();
//
//	for (a = 2;a <= height;a++)
//	{
//		for (b = 1;b <= nodes;b += 2)
//		{
//			for (c = 1;c <= b - 1 - c;c += 2)
//			{
//				if (c != b - 1 - c)
//					multiplier = 2;
//				else
//					multiplier = 1;
//
//				trees[a][b] += multiplier * (trees[a - 1][c] * trees[a - 1][b - 1 - c]
//				+ trees[a - 1][c] * smalltrees[a - 2][b - 1 - c]
//				+ trees[a - 1][b - 1 - c] * smalltrees[a - 2][c]);
//				
//				trees[a][b] %= 9901;
//			}
//		}
//		for (c = 0;c <= nodes;c++)
//		{
//			smalltrees[a - 1][c] += trees[a - 1][c] + smalltrees[a - 2][c];
//			smalltrees[a - 1][c] %= 9901;
//		}
//	}
//
//	out.open ("nocows.out");
//	out << trees[height][nodes] << "\n";
//	out.close ();
//
//	return 0;
//}

using namespace std;
int N, K, dp[203][103];
int DP(int n, int k)
{
    if (dp[n][k] >= 0)
        return dp[n][k];
    if (n == 1 && k > 0)
        return dp[n][k] = 1;
    dp[n][k] = 0;
    for (int i = 1; i < n-1; i+=2)
    {
        dp[n][k] += (DP(i, k-1)*DP(n-1-i, k-1));
        dp[n][k] %= 9901;
    }
    return dp[n][k];
}
int main()
{
    freopen("nocows.in", "r", stdin);
    freopen("nocows.out", "w", stdout);
    scanf("%d %d", &N, &K);
    memset(dp, -1, sizeof(dp));
    printf("%d\n", (DP(N, K)-DP(N, K-1)+9901)%9901);
    return 0;
}