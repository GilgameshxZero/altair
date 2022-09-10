#include <iostream>
#include <cmath>

using namespace std;

int main ()
{
	while (!cin.eof ())
	{
		int a, b;

		cin >> a >> b;
		cin.get ();
		cout << abs (a - b) << "\n";
	}
}