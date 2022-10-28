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
		reverse (temp.begin (), temp.end ());
		cout << temp << "\n";
	}

	return 0;
}