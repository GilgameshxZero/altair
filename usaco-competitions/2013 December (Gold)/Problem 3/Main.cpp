#include <cstdio>
#include <iostream>
using namespace std;

int pos[100000], pos2[100000], ans[100000], calc[100000];

int main ()
{
	freopen ("shufflegold.in", "r", stdin);
	freopen ("shufflegold.out", "w", stdout);

	int N, M, Q;
	cin >> N >> M >> Q;

	for (int a = 0;a < M;a++)
		cin >> pos[a],
		pos2[pos[a] - 1] = a;

	ans[0] = pos2[0];
	for (int a = 1;a < M;a++)
		ans[a] = pos2[ans[a - 1] + 1];

	calc[0] = M;
	for (int a = 1;a < M;a++)
		calc[a] = pos[calc[a - 1] - 1];

	for (int a = 0, b;a < Q;a++)
	{
		cin >> b;
		b = N - b; //reverse, from 0 to N - 1
		if (b >= M && b < N - M + 1)
			cout << b + 1 << "\n";
		else if (b < M)
			cout << ans[b] + 1 << "\n";
		else if (b >= N - M + 1)
			cout << calc[b - (N - M)] + N - M + 1 << "\n";
	}

	return 0;
}