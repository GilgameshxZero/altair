#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int n;
	cin >> n;

	for (;n > 0;n--)
	{
		string temp;
		cin >> temp;

		int c = 0;
		for (int a = 0;a < temp.length ();a++)
			c += ((temp[a] == 'a') || (temp[a] == 'e') || (temp[a] == 'i') || (temp[a] == 'o') || (temp[a] == 'u'));
		if (c & 1)
			cout << "PESAR\n";
		else cout << "DOKHTAR\n";
	}

	return 0;
}