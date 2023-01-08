//run tests between n^2 and nlogn

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> lis, seq, len, x;

int DP ()
{
	lis[0] = 1;
	int ans = 1;
	for (int a = 1;a < 10000;a++)
	{
		lis[a] = 1;
		for (int b = 0;b < a;b++)
			if (x[b] < x[a])
				lis[a] = max (lis[a], 1 + lis[b]);
		ans = max (ans, lis[a]);
	}

	return ans;
}

int Faster ()
{
	seq[0] = x[0];
	len[0] = 1;
	int k = 1;
	for (int a = 1, b;a < 10000;a++)
	{
		if (x[a] < seq[0])
			seq[0] = x[a];
		else if (x[a] > seq[k - 1])
		{
			seq[k] = x[a];
			len[k] = len[k - 1] + 1;
			k++;
		}
		else
		{
			b = lower_bound (seq.begin (), seq.begin () + k, x[a]) - seq.begin (); //first elem equal or greater to
			seq[b] = x[a];
		}
	}

	return len[k - 1];
}

int main ()
{
	srand (time (NULL));

	lis.resize (10000);
	seq.resize (10000);
	len.resize (10000);

	//compare 500 sequences of length 10000 each, randomly generated
	x.resize (10000);
	for (int a = 0, b, c, m, n, o;a < 500;a++)
	{
		cout << "Running test " << a + 1 << "... ";
		for (int d = 0;d < 10000;d++)
			x[d] = rand ();
		b = clock ();
		c = DP ();
		m = clock ();
		n = Faster ();
		o = clock ();
		if (c != n)
		{
			cout << "No match!\n";
			break;
		}
		cout << "Match!\n"
			<< "N^2 time: " << (m - b) << "\n"
			<< "NlogN time: " << (o - m) << "\n\n";
	}

	return 0;
}