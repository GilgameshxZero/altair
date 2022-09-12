/*
ID: yangchess1
PROG: sort3
LANG: C++
*/
#include <fstream>
using namespace std;
int number, amount[3] = {0, 0, 0};				//Number of records to be sorted and amount of 1, 2, and 3s
int exchanges = 0;										//Answer: number of exchanges of nodes needed (at least)
int a, b, c, d, e, f;										//Test variables
bool w, x, y, z;
short records[1000];									//Things to be sorted
bool sorted[1000];
void smart (int a);
int main ()
{
	ifstream input;										//Input and output variables
	ofstream output;

	input.open ("sort3.in");							//Input number of nodes and nodes of 1, 2, 3
	input >> number;

	for (a = 0;a < number;a++)
	{
		input >> records[a];
		records[a] = records[a];
		
		for (b = 0;b < 3;b++)							//Add to amount accordingly
			if (records[a] == b + 1)
				amount[b]++;
	}

	input.close ();
	output.open ("sort3.out");

	for (a = 0;a < number;a++)						//Look for smart exchanges (two successes at a time)
		smart (a);

	for (a = 0;a < number;a++)						//Test for not smart exchanges
	{
		for (b = a;b < number;b++)
		{
			if (a != b && records[a] != records[b] && sorted[a] == false && sorted[b] == false)	//If not the same and not the same node
			{
				c = d = 0;

				for (f = 0;f < records[a] - 1;f++)//Set lower range for the right place for node a
					c += amount[f];

				for (e = 0;e < records[b] - 1;e++)//Set lower bound for the right place for node b
					d += amount[e];

				w = !(a >= c && a < c + amount[records[a] - 1]);
				x = !(b >= d && b < d + amount[records[b] - 1]);
				y = (a >= d && a < d + amount[records[b] - 1]);
				z = (b >= c && b < c + amount[records[a] - 1]);
				if ((w && x) && (y || z))	//Test if not smart exchange will be successful
				{
					exchanges++;						//Mark one exchange

					records[a] ^= records[b];		//Switch records
					records[b] ^= records[a];
					records[a] ^= records[b];

					if (a >= d && a < d + amount[records[b] - 1])	//Test for two separate cases of smart exchange
						smart (b);

					if (b >= c && b < c + amount[records[a] - 1])
						smart (a);
				}
			}
		}
	}

	output << exchanges << "\n";
	output.close ();

	return 0;
}
void smart (int a)
{
	int b, c, d, e;

	c = 0;

	for (b = 0;b < records[a] - 1;b++)			//Set lower range for if the node is already in the right place
		c += amount[b];

	if (!(a >= c && a < c + amount[records[a] - 1]))	//Test if node is in the right place
	{
		for (b = 0;b < number;b++)					//If not, search other nodes for smart exchanges
		{
			if (a != b && records[a] != records[b])
			{
				d = 0;

				for (e = 0;e < records[b] - 1;e++)	//Set lower bound for the right place for node b
					d += amount[e];

				if ((a >= d && a < d + amount[records[b] - 1]) && (b >= c && b < c + amount[records[a] - 1]))	//Test if smart exchange will be successful
				{	
					exchanges++;						//Mark one exchange
					sorted[a] = true;						//Mark sorted
					sorted[b] = true;

					records[a] ^= records[b];		//Switch records
					records[b] ^= records[a];
					records[a] ^= records[b];
				}
			}
		}
	}
}