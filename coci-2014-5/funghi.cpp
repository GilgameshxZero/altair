#include <iostream>
using namespace std;

int main ()
{
	int k[12];
	for (int a = 0;a < 8;a++)
		cin >> k[a];
	for (int a = 0;a < 4;a++)
		k[8 + a] = k[a];
	int ans = 0;
	for (int a = 0;a < 8;a++)
	{
		int sum = 0;
		for (int b = a;b < a + 4;b++)
			sum += k[b];
		ans = max (ans, sum);
	}
	cout << ans;
	return 0;
}