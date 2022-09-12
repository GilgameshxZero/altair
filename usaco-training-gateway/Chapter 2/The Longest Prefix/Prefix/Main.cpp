/*
ID: yangchess1
PROG: prefix
LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>
#include <bitset>
#include <utility>
#include <set>
#include <numeric>
#include <ctime>
 
#define Inf 2147483647
#define Pi acos(-1.0)
#define N 200000 + 10
#define P 200 + 5
#define LL long long
 
inline LL Power(int b, int p) { LL ret = 1; for ( int i = 1; i <= p; i++ ) ret *= b; return ret; }
const int dr [] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dc [] = {0, 1, 1, 1, 0, -1, -1, -1};
 
#define F(i, a, b) for( int i = (a); i < (b); i++ )
#define Fs(i, sz) for( size_t i = 0; i < sz.size (); i++ )
#define Fe(i, x) for(typeof (x.begin()) i = x.begin(); i != x.end (); i++)
#define Set(a, s) memset(a, s, sizeof (a))
#define max(a, b)  (a < b ? b : a)
#define min(a, b)  (a > b ? b : a)
 
 
using namespace std;
 
char input [N];
 
char sequence [N];
 
char primitives [P] [10 + 2];
 
int maxi;
 
int primitivesSize [P];
 
int lenPrimitives = 0;
 
int main ()
{
    freopen ("prefix.in", "r", stdin);
    freopen ("prefix.out", "w", stdout);
     
    while ( scanf ("%s", input) && strcmp (input, ".") != 0 ) {
         
        strcpy (primitives [lenPrimitives], input);
             
        primitivesSize [lenPrimitives++] = (int) strlen (input);
         
    }
     
    strcpy(sequence, "");
     
    while ( scanf ("%s", input) != EOF ) {
         
        strcat(sequence, input);
    }
 
    bool isAvailable [N];
 
    Set(isAvailable, false);
 
    isAvailable [0] = true;
 
    int sequenceLength = strlen(sequence);
 
    for ( int i = 0; i < sequenceLength; i++ ) {
 
        if ( isAvailable [i]) {
 
            for ( int j = 0; j < lenPrimitives; j++ ) {
                if (strncmp (sequence + i, primitives [j], (size_t) primitivesSize[j]) == 0) {
                    maxi = max (maxi, i + primitivesSize[j]);
                    isAvailable [i + primitivesSize [j]] = true;
                }
 
            }
        }
    }
     
    printf ("%d\n", maxi);
     
    return 0;
}/*
#include <fstream>
#include <string>
using namespace std;

int largest = 0, number = 0, start;
string perimitives[200];

void calculate (string sequence)
{
	int a, b, length = sequence.length ();
	bool found = false;
	for (a = 1;a <= 10;a++)
	{
		for (b = 0;b < number;b++)
		{
			if (perimitives[b].length () == a && sequence.substr (0,a) == perimitives[b])
			{
				calculate (sequence.substr (a,length - a));
				found = true;
			}
		}
	}

	if (found == false)
	{
		a = start - length;

		if (a > largest)
			largest = a;
	}
}

int main ()
{
	ifstream in;
	ofstream out;
	string sequence, i;

	in.open ("prefix.in");
	in >> i;

	while (i != ".")
	{
		perimitives[number] = i;
		number++;
		in >> i;
	}

	while (in.good ())
	{
		in >> i;
		sequence += i;
	}

	in.close ();
	start = sequence.length ();

	calculate (sequence);

	out.open ("prefix.out");
	out << largest << "\n";
	out.close ();

	return 0;
}*/