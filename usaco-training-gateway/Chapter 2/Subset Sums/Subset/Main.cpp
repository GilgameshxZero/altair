/*
ID: yangchess1
PROG: subset
LANG: C++
*/
//Find the number of ways the set {1, 2, 3, 4, ..., number} can be separated into two subsets that have the same sum

//Headers and definitions
#include <fstream>
using namespace std;

//Globals

//Prototypes

//Functions
int main ()
{
	ifstream in;			//Input and output variables
	ofstream out;
	long long answer[391];
	int number, sum;
	int a, b;

	in.open ("subset.in");			//Input n, the additive sum
	in >> number;
	in.close ();
	out.open ("subset.out");

	if ((number * (number + 1) / 2) % 2 == 1)			//If there is not a solution
	{
		out << "0\n";
		out.close ();
		return 0;
	}

	sum = number * (number + 1) / 4;			//Find the sum of each subset

	for (a = 0;a < 391;a++)			//Initialize
		answer[a] = 0;

	answer[0] = 1;

	for (a = 1;a <= number;a++)			//Solve the problem
		for (b = sum;b >= a;b--)
			answer[b] += answer[b - a];

	out << answer[sum] / 2 << "\n";
	out.close ();

	return 0;
}