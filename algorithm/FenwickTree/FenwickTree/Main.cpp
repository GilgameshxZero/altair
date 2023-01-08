/*
Note than fen[0] is assumed to not be used.
Care with integer overflow.
*/
#include <vector>

using namespace std;

//adds k to the element at pos x
void FenAdd (vector<int>& fen, int k, int x)
{
	for (;x < fen.size ();x += (x & -x))
		fen[x] += k;
}

//sums all elements before and including x
int FenSum (vector<int>& fen, int x)
{
	int r = 0;
	for (;x > 0;x -= (x & -x))
		r += fen[x];
	return r;
}

int main ()
{
	return 0;
}