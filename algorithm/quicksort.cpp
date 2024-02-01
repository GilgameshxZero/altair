#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

void QuickSort (vector<int>& x, int f, int l) //Inclusive.
{
	if (f >= l)
		return;

	//Randomly select pivot and move to end.
	int k = rand () % (l - f + 1) + f;
	swap (x[k], x[l]);

	//Partition by pivot.
	int m = f;
	for (int a = f;a < l;a++)
		if (x[a] < x[l])
			swap (x[a], x[m++]);

	//Swap pivot to correct place.
	swap (x[l], x[m]);

	//Sort both partitions.
	QuickSort (x, f, m - 1);
	QuickSort (x, m + 1, l);
}

int main ()
{
	srand (time (NULL));
	for (int a = 0;a < 100;a++)
	{
		cout << "Running test " << a + 1 << "...";
		//Create random array.
		vector<int> x[2];
		x[0].resize (100000);
		for (int a = 0;a < 100000;a++)
			x[0][a] = rand ();
		x[1] = x[0];

		int k[3];
		k[0] = clock ();
		QuickSort (x[0], 0, 99999);
		k[1] = clock ();
		sort (x[1].begin (), x[1].end ());
		k[2] = clock ();

		if (x[0] != x[1])
		{
			cout << "Break!";
			cin.get ();
			break;
		}

		cout << " Match!\n"
			<< "QuickSort: " << k[1] - k[0]
			<< "\nstd::sort: " << k[2] - k[1] << "\n\n";
	}
}