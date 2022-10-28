#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main ()
{
	string s;
	cin >> s;

	int m3 = 0;
	bool zero = false;
	for (int a = 0;a < s.length ();a++)
	{
		m3 = (m3 + s[a] - '0') % 3;
		if (s[a] == '0')
			zero = true;
	}

	if (!zero || m3 != 0)
	{
		cout << "-1";
		return 0;
	}

	sort (s.begin (), s.end ());
	reverse (s.begin (), s.end ());
	cout << s;

	return 0;
}