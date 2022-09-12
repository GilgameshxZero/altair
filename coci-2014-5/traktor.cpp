#include <iostream>
#include <cstdio>
using namespace std;

int cnt[2][100001], cdiag[2][200001];

int main ()
{
	//freopen ("in.txt", "r", stdin); freopen ("out.txt", "w", stdout);

	int N, K;
	cin >> N >> K;

	for (int a = 0, b, c;a < N;a++)
	{
		cin >> b >> c;
		cnt[0][c]++; //row
		cnt[1][b]++; //col
		cdiag[0][c - b + 100000]++; //pos diag
		cdiag[1][c + b]++;

		if (cnt[0][c] == K || cnt[1][b] == K || cdiag[0][c - b + 100000] == K || cdiag[1][c + b] == K)
		{
			cout << a + 1;
			break;
		}
	}

	return 0;
}