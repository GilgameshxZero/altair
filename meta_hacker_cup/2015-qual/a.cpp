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
		string s;
		cin >> s;

		vector<string> vec;
		for (int a = 0;a < s.length ();a++)
			for (int b = a + 1;b < s.length ();b++)
				if (!(a == 0 && s[b] == '0'))
					swap (s[a], s[b]),
					vec.push_back (s),
					swap (s[a], s[b]);

		string ms = s, mms = s;
		for (int a = 0;a < vec.size ();a++)
		{
			if (vec[a] > ms)
				ms = vec[a];
			if (vec[a] < mms)
				mms = vec[a];
		}

		cout << "Case #" << k + 1 << ": " << mms << " " << ms << "\n";
	}

	return 0;
}