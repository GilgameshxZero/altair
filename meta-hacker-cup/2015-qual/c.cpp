#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int T;
	cin >> T;

	for (int k = 0;k < T;k++)
	{
		int G[3];
		cin >> G[0] >> G[1] >> G[2];

		int N;
		cin >> N;

		int	food[20][3];
		for (int a = 0;a < N;a++)
			cin >> food[a][0] >> food[a][1] >> food[a][2];

		bool flag = false;
		for (int a = 0;a < (1 << N);a++)
		{
			int T[3] = {0, 0, 0};
			for (int b = 0, c = a;b < 20;b++, c >>= 1)
				if (c & 1)
					T[0] += food[b][0], T[1] += food[b][1], T[2] += food[b][2];
			if (T[0] == G[0] && T[1] == G[1] && T[2] == G[2])
			{
				flag = true;
				break;
			}
		}

		cout << "Case #" << k + 1 << ": " << (flag ? "yes\n" : "no\n");
	}

	return 0;
}