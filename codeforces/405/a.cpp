#include <iostream>
#include <cstring>
using namespace std;

int main ()
{
	//freopen ("Text.txt", "r", stdin);

	int n, col[100], row[100];
	cin >> n;
	memset (row, 0, 100 * sizeof(int));
	memset (col, 0, 100 * sizeof(int));

	for (int a = 0, b;a < n;a++)
	{
		cin >> b;
		for (int c = 0;c < b;c++)
			row[c]++;
	}

	for (int a = 0;a < 100;a++)
		for (int b = 0;b < row[a];b++)
			col[n - 1 - b]++;

	for (int a = 0;a < n - 1;a++)
		cout << col[a] << " ";

	cout << col[n - 1];

	return 0;
}