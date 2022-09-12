/*
ID: yangchess1
PROG: lamps
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
#define N 1000000
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
 
vector <int> onElements;
vector <int> offElements;
 
vector <bool> applyButtonEffect(int button, vector<bool> v){
    switch (button) {
    case 0:
        for ( int i = 1; i < v.size(); i++ ) v [i] = !v [i];
        break;
    case 1:
        for ( int i = 1; i < v.size(); i += 2 ) v [i] = !v [i];
        break;
    case 2:
        for ( int i = 2; i < v.size(); i += 2 ) v [i] = !v [i];
        break;
    case 3:
        for ( int i = 1; i < v.size(); i += 3 ) v [i] = !v [i];
        break;
    default:
        break;
    }
 
    return v;
}
 
bool isMatchWithFinal(vector <bool> v){
    for ( int i = 0; i < onElements.size(); i++ ) {
        if (v [onElements [i]] == false) return false;
    }
 
    for ( int i = 0; i < offElements.size(); i++ ) {
        if (v [offElements [i]]) return false;
    }
 
    return true;
}
 
int main () {
 
    freopen ("lamps.in", "r", stdin);
    freopen ("lamps.out", "w", stdout);
 
    int n; scanf ("%d", &n);
 
    queue < vector<bool> > q;
    vector <bool> firstElement;
 
    // all lights are on 
    for ( int i = 0; i <= n; i++ ) firstElement.push_back(true);
 
    // we will try with BFS
    q.push(firstElement);
 
    int c; scanf ("%d", &c);
    // using a switch more than once in unnecessary 
    c = min (c, 4);
 
    int elem;
    while ( scanf ("%d", &elem) && elem != -1 ) {
        onElements.push_back(elem);
    }
 
    while ( scanf ("%d", &elem) && elem != -1 ) {
        offElements.push_back(elem);
    }
 
    // marking, if an element is visited 
    map< vector<bool>, bool> visited;
    visited [firstElement] = true;
 
    // we will get the whole output sorted, and without duplicacy 
    set< vector<bool> > output;
 
    if(isMatchWithFinal(firstElement)) output.insert(firstElement);
 
    int loop = 1; // how many steps we will make for a certain 'c' value 
    for ( int i = 0; i < c; i++ ) loop *= (4 - i);
    if(c == 0) loop = 0;    // if c = 0, there is not steps 
 
    while ( !q.empty() ) {
        vector <bool> popElem;
        popElem = q.front();
        q.pop();
 
        if(isMatchWithFinal(popElem))output.insert(popElem);
 
        if(loop) {
            vector <bool> newState;
            for ( int i = 0; i < 4; i++ ) {
                newState = applyButtonEffect (i, popElem);
                if(!visited [newState]) {
                    visited [newState] = true;
                    q.push(newState);
                }
                loop--;
            }
        }
 
    }
 
    if(output.size() == 0){
        printf ("IMPOSSIBLE\n");
    } else {
        set< vector<bool> >::iterator it;
        for(it = output.begin(); it != output.end(); it++) {
            for (int i = 1; i < (*it).size(); i++ ) {
                if ( (*it) [i] ) printf ("%d", 1);
                else printf ("%d", 0);
            }
            printf ("\n");
        }
    }
 
    return 0;
}
/*
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
	char chr;
	int a, b, c;

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