/*
ID: yangchess1
LANG: C++
PROB: prime3
*/

/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

When submitting the program, define DEBUG 0. When debugging, define DEBUG 1. In the program, for debugging information, use if (DEBUG){...} such that when it is submitted we don't have that code there.

Backup this program every so often in the Backup.txt files in case something goes wrong later.

Max's and mins: numeric_limits<type_name>::min().
*/

#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define DEBUG 0
//#define DEBUG 1

bool is_prime[100001]; //Here we define the is_prime array to compute whether a number is prime. This is convenient so we don't have to recompute each time we need to know, since we have computed all the primes already at the beginning of main (). This is very memory inefficient, but that's not the main problem.

//Store primes in a structure like this; although not very memory efficient, will simplify the programming progress and reduce run times a little.
struct DigitPrime
{
	int dig[5];
	int prime;
};

//Because using qsort on multidimensional arrays is messy and I don't really get it (believe me I tried to implement it but the *'s confused me), we are going to store solutions in a structure so that qsort will operate on a single array.
struct Solution
{
	int solution[5][5];
};

//This function is used in the qsort to sort the solutions into order for output.
int sol_cmp (const void *a, const void *b)
{
	const Solution sol1 = *reinterpret_cast<Solution *>(const_cast<void *>((a))), sol2 = *reinterpret_cast<Solution *>(const_cast<void *>((b)));

	for (int a = 0;a < 5;a++)
	{
		for (int b = 0;b < 5;b++)
		{
			if (sol1.solution[a][b] > sol2.solution[a][b])
				return 1;
			else if (sol1.solution[a][b] < sol2.solution[a][b])
				return -1;
		}
	}

	return 0;
}

int main ()
{
	std::ifstream in ("prime3.in");
	std::ofstream out ("prime3.out");
	DigitPrime primes[10000];
	Solution solutions[500]; //Honestly, I doubt there will be more than 500 solutions, therefore the arbitrary 500 (actually, the first few times I submitted this I thought it wouldn't be more than 50... but no).
	const int max_sqrt = 316, sm_count = 63;
	int sm_primes[sm_count] = {5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313};
	int dig_sum, tl_num, prime_count = 0, csol = 0, current_square[5][5];
	int a, b, c, d, e, f, g, h, i, j; //A bunch of loop variables that defining within the loop would consume time.

	in >> dig_sum >> tl_num;
	in.close ();

	//Initialize the is_prime array.
	for (a = 0;a < 100001;a++)
		is_prime[a] = false;

	//First, find all the primes between 10000 and 99999.
	for (a = 10001, c = 0, d = 0, e = 10003;a < 99997;a += 6, c = d = 0, e = a + 2)
	{
		//Test if a or a + 2 is prime; this will cover all primes, because 6x + 1 and 6x - 1 are the only primes. To avoid square-rooting a each time, we just test up to sqrt (99998) ~= 316.
		for (b = 0;(b < sm_count) && (c == 0  || d == 0);b++)
		{
			if (a % sm_primes[b] == 0)
				c = 1;

			if (e % sm_primes[b] == 0)
				d = 1;
		}

		//Before adding the prime to the list, check that the digits' sum is the desired sum.
		if (c == 0)
		{
			for (b = 10, f = 0, g = a, h = 4;g >= 1;g /= 10, h--)
			{
				primes[prime_count].dig[h] = g % b; //It's OK to save the digits before the prime is verified, because if the number is not a prime, the next prime will just overwrite these digits.
				f += primes[prime_count].dig[h];
			}

			if (f == dig_sum)
			{
				primes[prime_count++].prime = a;
				is_prime[a] = true;
			}
		}
		
		//Ditto.
		if (d == 0)
		{
			for (b = 10, f = 0, g = e, h = 4;g >= 1;g /= 10, h--)
			{
				primes[prime_count].dig[h] = g % b;
				f += primes[prime_count].dig[h];
			}

			if (f == dig_sum)
			{
				primes[prime_count++].prime = e;
				is_prime[e] = true;
			}
		}
	}

	//Now, we can fill in the square with the primes.
	for (a = 0;a < prime_count;a++)
	{
		//As long as the first digits match we can use this prime for our primary diagonal.
		if (primes[a].dig[0] == tl_num)
		{
			//First we fill in the diagonal from the top-left to the bottom-right.
			for (b = 0;b < 5;b++)
				current_square[b][b] = primes[a].dig[b];

			//Now we fill in the other diagonal, with the limits of the center digit and that the first digit must be odd.
			for (b = 0;b < prime_count;b++)
			{
				if (primes[b].dig[2] == current_square[2][2] && primes[b].dig[0] % 2 == 1)
				{
					current_square[0][4] = primes[b].dig[4];
					current_square[1][3] = primes[b].dig[3];
					current_square[3][1] = primes[b].dig[1];
					current_square[4][0] = primes[b].dig[0];

					//From here, we fill in the primes in the 1st row first. Then, we will fill in the 2nd and 4th column, and then the 5th row. Finally, fill in the 3rd column and the 2nd and 4th rows, and then calculate the remaining squares (the two outside square on the third row) and verify that the 1st and 5th columns and the 3rd row are primes. This order of filling in the square gives the fastest running time (I previously did this wrong, this order is very crucial). Take into consideration the restrictions by which these primes are allowed, such as which digits are allowed to be even, which digits have already been decided, and the ranges of the digits (0-9 or 1-9).
					for (c = 0;c < prime_count;c++) //First row.
					{
						if (primes[c].dig[0] == current_square[0][0] && primes[c].dig[4] == current_square[0][4] && primes[c].dig[1] != 0 && primes[c].dig[2] != 0 && primes[c].dig[3] != 0)
						{
							current_square[0][1] = primes[c].dig[1];
							current_square[0][2] = primes[c].dig[2];
							current_square[0][3] = primes[c].dig[3];

							for (d = 0;d < prime_count;d++) //2nd column.
							{
								if (primes[d].dig[0] == current_square[0][1] && primes[d].dig[1] == current_square[1][1] && primes[d].dig[3] == current_square[3][1])
								{
									current_square[2][1] = primes[d].dig[2];
									current_square[4][1] = primes[d].dig[4];

									for (e = 0;e < prime_count;e++) //4th column.
									{
										if (primes[e].dig[0] == current_square[0][3] && primes[e].dig[1] == current_square[1][3] && primes[e].dig[3] == current_square[3][3])
										{
											current_square[2][3] = primes[e].dig[2];
											current_square[4][3] = primes[e].dig[4];

											//For the 5th row, we don't have to test every prime. We can use the digit sum to test if the number is a prime. The following condition verifies that the calculated digit is 0-9 and odd.
											current_square[4][2] = dig_sum - current_square[4][0] - current_square[4][1] - current_square[4][3] - current_square[4][4];
											if (current_square[4][2] >= 0 && current_square[4][2] < 10 && current_square[4][2] % 2 == 1 && is_prime[current_square[4][0] * 10000 + current_square[4][1] * 1000 + current_square[4][2] * 100 + current_square[4][3] * 10 + current_square[4][4]] == true)
											{
												for (f = 0;f < prime_count;f++) //3rd column.
												{
													if (primes[f].dig[0] == current_square[0][2] && primes[f].dig[2] == current_square[2][2] && primes[f].dig[4] == current_square[4][2])
													{
														current_square[1][2] = primes[f].dig[1];
														current_square[3][2] = primes[f].dig[3];

														for (g = 0;g < prime_count;g++) //2nd row.
														{
															if (primes[g].dig[1] == current_square[1][1] && primes[g].dig[2] == current_square[1][2] && primes[g].dig[3] == current_square[1][3])
															{
																current_square[1][0] = primes[g].dig[0];
																current_square[1][4] = primes[g].dig[4];

																for (h = 0;h < prime_count;h++) //4th row.
																{
																	if (primes[h].dig[1] == current_square[3][1] && primes[h].dig[2] == current_square[3][2] && primes[h].dig[3] == current_square[3][3])
																	{
																		current_square[3][0] = primes[h].dig[0];
																		current_square[3][4] = primes[h].dig[4];

																		//So now we calculate the remaining 2 squares based on digit sum and verify the 1st column, 5th column, and the 3rd row to be prime or not.
																		current_square[2][0] = dig_sum - current_square[0][0] - current_square[1][0] - current_square[3][0] - current_square[4][0];
																		current_square[2][4] = dig_sum - current_square[0][4] - current_square[1][4] - current_square[3][4] - current_square[4][4];

																		//This is just a blob of conditions that verifies what was mentioned above.
																		if (current_square[2][0] > 0 && current_square[2][0] < 10 && current_square[2][4] >= 0 && current_square[2][4] < 10 && is_prime[current_square[0][0] * 10000 + current_square[1][0] * 1000 + current_square[2][0] * 100 + current_square[3][0] * 10 + current_square[4][0]] == true && is_prime[current_square[0][4] * 10000 + current_square[1][4] * 1000 + current_square[2][4] * 100 + current_square[3][4] * 10 + current_square[4][4]] == true && is_prime[current_square[2][0] * 10000 + current_square[2][1] * 1000 + current_square[2][2] * 100 + current_square[2][3] * 10 + current_square[2][4]] == true)
																		{
																			//The square works! Add the current_square to the list of solutions.
																			for (i = 0;i < 5;i++)
																				for (j = 0;j < 5;j++)
																					solutions[csol].solution[i][j] = current_square[i][j];

																			csol++;
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	//If we have no solutions, we can end it here.
	if (csol == 0)
	{
		out << "NONE\n";
		out.close ();

		return 0;
	}

	//Now that we have our solutions (phew) we need to sort them before we output them.
	qsort (solutions, csol, sizeof (Solution), sol_cmp);

	for (int a = 0;a < csol;a++)
	{
		for (int b = 0;b < 5;b++)
		{
			for (int c = 0;c < 5;c++)
				out << solutions[a].solution[b][c];

			out << "\n";
		}

		if (a != csol - 1)
			out << "\n";
	}

	out.close ();

	return 0;
}