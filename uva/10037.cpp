#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int main ()
{
	//freopen ("Text.txt", "r", stdin);
	
	int i, n, t, l, arr[1000];
	string s;
	scanf ("%i", &n);

	for (int a = 0;a < n;a++)
	{
		scanf ("%i", &i);
		s = "";
		t = 0;

		for (int b = 0;b < i;b++)
			scanf ("%i", &arr[b]);

		sort (arr, arr + i);

		while (i > 3)
		{
			if (2 * arr[1] < arr[0] + arr[i - 2])
			{
				s += to_string (arr[0]) + " " + to_string (arr[1]) + "\n" + to_string (arr[0]) + "\n" + to_string (arr[i - 2]) + " " + to_string (arr[i - 1]) + "\n" + to_string (arr[1]) + "\n";
				t += arr[0] + 2 * arr[1] + arr[i - 1];
			}
			else
			{
				s += to_string (arr[0]) + " " + to_string (arr[i - 1]) + "\n" + to_string (arr[0]) + "\n" + to_string (arr[0]) + " " + to_string (arr[i - 2]) + "\n" + to_string (arr[0]) + "\n";
				t += 2 * arr[0] + arr[i - 2] + arr[i - 1];
			}

			i -= 2;
		}

		if (i == 1)
			cout << arr[0] << "\n" << arr[0] << "\n";
		else if (i == 2)
			cout << t + arr[1] << "\n" << s << arr[0] << " " << arr[1] << "\n";
		else if (i == 3)
			cout << t + arr[0] + arr[1] + arr[2] << "\n" << s << arr[0] << " " << arr[2] << "\n" << arr[0] << "\n" << arr[0] << " " << arr[1] << "\n";

		if (a != n - 1)
			printf ("\n");
	}

	return 0;
}