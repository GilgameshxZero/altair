/*
ID: yangchess1
PROG: range
LANG: C++
*/
#include<fstream>
using namespace std;
int i,j,n,f[2][251],now,last,maxsquare;
int size[251];
char ch;
int main()
 {
    ifstream fin("range.in");
    ofstream fout("range.out"); 
    fin>>n;
    now=0;last=1;
    for (i=1;i<=n;i++)
    {
        now^=1;last^=1;
        for (j=1;j<=n;j++)
        {
            fin>>ch;
            if (ch=='0') f[now][j]=0;
            else f[now][j]=min(f[now][j-1],min(f[last][j],f[last][j-1]))+1;
            ++size[f[now][j]];
            maxsquare=max(maxsquare,f[now][j]);
        }
    }
    for (i=maxsquare-1;i>1;i--) size[i]+=size[i+1];
    for (i=2;i<=maxsquare;i++) fout<<i<<" "<<size[i]<<endl;
    return 0;
}/*
#include <fstream>
#include <cstring>

const int MAX_FSIDE = 250;

int main ()
{
	std::ifstream in ("range.in");
	std::ofstream out ("range.out");
	int field_side, square_count[MAX_FSIDE], large_square[MAX_FSIDE][MAX_FSIDE], a, b, c, d, e;
	bool field[MAX_FSIDE][MAX_FSIDE];

	//Set all of square_count as 0
	memset (square_count, 0, MAX_FSIDE * sizeof (int));

	//Simple input procedure
	in >> field_side;
	in.get (); //Discard the newline

	for (a = 0;a < field_side;a++)
	{
		for (b = 0;b < field_side;b++)
			field[a][b] = static_cast<bool>(in.get () - 48);

		in.get (); //Newline
	}

	in.close ();

	//Inialize the large_squares for the top and left row/columns to be 1 if it is OK to eat, 0 if not
	for (a = 0;a < field_side;a++)
		large_square[0][a] = static_cast<int>(field[0][a]);

	for (a = 1;a < field_side;a++)
		large_square[a][0] = static_cast<int>(field[a][0]);

	//We find the largest square to the top-left at every corner by DP, and then it'll be easy to compute.
	for (a = 1;a < field_side;a++)
	{
		for (b = 1;b < field_side;b++) //So we compute by row, so that DP works
		{
			//Take the minimum of the number of neighboring 1s up, left, and the large_square[a - 1][b - 1]
			c = 0; //Init up 1 count
			for (e = a;e >= 0;e--)
			{
				if (field[e][b] == false)
					break;
				
				c++;
			}

			d = 0; //Init left 1 count
			for (e = b;e >= 0;e--)
			{
				if (field[a][e] == false)
					break;
				
				d++;
			}

			//Store the min of 1 up count and 1 left count in e, then compare with large[a - 1][b - 1]
			if (c <= d)
				e = c;
			else
				e = d;

			if (e <= large_square[a - 1][b - 1])
				large_square[a][b] = e;
			else
				large_square[a][b] = large_square[a - 1][b - 1] + 1;
		}
	}

	//Iterate through large array, and for every number n, count it as a square for numbers 2 ... n
	for (a = 1;a < field_side;a++)
		for (b = 1;b < field_side;b++)
			for (c = 2;c <= large_square[a][b];c++)
				square_count[c - 1]++;

	//Simple output procedure
	for (a = 2;square_count[a - 1] > 0 && a <= MAX_FSIDE;a++)
		out << a << " " << square_count[a - 1] << "\n";

	out.close ();

	return 0;
}*/