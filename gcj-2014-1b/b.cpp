#include <iostream>
using namespace std;

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int T;
	unsigned long long ans;
	cin >> T;

	for (int x = 0;x < T;x++)
	{
		int A, B, K;
		ans = 0;
		cin >> A >> B >> K;

		for (int a = 0, b;a < A;a++)
		{
			for (b = 0;b < B;b++)
				if ((a & b) < K)
					ans++;
		}

		cout << "Case #" << x + 1 << ": " << ans << "\n";
	}

	return 0;
}