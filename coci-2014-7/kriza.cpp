#include <iostream>
#include <cstdio>
using namespace std;

int rot[100000], bref[100000];

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int N, K, bpos;
	long long cylen, finmod, first;

	cin >> N >> K;

	for (int a = 0;a < N;a++)
		cin >> rot[a],
		bref[--rot[a]] = a;

	cylen = 0;
	bpos = bref[N - 1];
	for (int a = 0;a < N;a++)
	{
		if (a == (K % N))
			finmod = cylen;

		if (bpos <= bref[a])
			cylen += bref[a] - bpos,
			bpos = bref[a];
		else
			cylen += bref[a] - bpos + N,
			bpos = bref[a];
	}

	first = 0;
	bpos = 0;
	for (int a = 0;a < N;a++)
	{
		if (bpos <= bref[a])
			first += bref[a] - bpos,
			bpos = bref[a];
		else
			first += bref[a] - bpos + N,
			bpos = bref[a];
	}

	//cout << first << " " << cylen << "\n";
	cout << cylen * (K / N - 1) + first + finmod << "\n";

	return 0;
}