#include <iostream>
using namespace std;

unsigned short n, m, x[100000], **arr;

int main ()
{
	freopen ("Text.txt", "r", stdin);

	cin >> n >> m;

	for (int a = 0;a < n;a++)
		cin >> x[a];

	//Construct tree.
	arr = new unsigned short *[100000];

	for (int a = 0;a < 100000;a++)
		arr[a] = new unsigned short[100000];

	return 0;

	for (int a = 0;a < 100000;a++)
		delete[] arr[a];

	delete[] arr;
}