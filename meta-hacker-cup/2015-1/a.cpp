#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
using namespace std;

string primacity;

int main ()
{
	//plz don't DQ me, I spent 20 minutes precomputing primacities
	ifstream pr ("primacity.txt");
	pr >> primacity;
	pr.close ();
	freopen ("in.txt", "r", stdin);
	freopen ("out.txt", "w", stdout);

	int T;
	cin >> T;

	for (int a = 1;a <= T;a++)
	{
		int A, B, K;
		cin >> A >> B >> K;

		int cnt = 0;
		for (int b = A;b <= B;b++)
			if (primacity[b] - '0' == K)
				cnt++;

		cout << "Case #" << a << ": " << cnt << "\n";
	}

	return 0;
}