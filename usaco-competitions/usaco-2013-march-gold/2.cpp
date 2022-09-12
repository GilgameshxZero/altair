#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

struct CritPt
{
	int x, line, hei;
	bool type; //0=end, 1=start

	CritPt ()
	{
		x = line = type = 0;
	}

	CritPt (int a, int b, bool c, int d)
	{
		x = a;
		line = b;
		type = c;
		hei = d;
	}

	const bool operator< (const CritPt &other) const
	{
		if (x == other.x)
		{
			if (type == other.type)
				return hei < other.hei;
			else
				return type > other.type;
		}
		return x < other.x;
	}
};

struct Line
{
	int x1, y1, x2, y2;
};

const int MAXN = 100000, MAXHEAP = 131072 + 1;
int N, heap[MAXHEAP], hsize, ccpt, heap_pos[100000], cur_line, ans; //heap starts at 1
Line l[100000];
CritPt cpt[200000];

double Eval (Line &x, int time)
{
	double m = (double)(x.y2 - x.y1) / (x.x2 - x.x1);
	return x.y1 + m * (time - x.x1);
}

void HeapUp (int ind, int time)
{
	while (ind != 1)
	{
		if (Eval (l[heap[ind]], time) > Eval (l[heap[ind / 2]], time))
		{
			swap (heap_pos[heap[ind]], heap_pos[heap[ind / 2]]);
			swap (heap[ind], heap[ind / 2]);
			ind /= 2;
		}
		else
			break;
	}
}

void HeapDown (int ind, int time)
{
	while (true)
	{
		if (ind * 2 <= hsize && Eval (l[heap[ind]], time) < Eval (l[heap[ind * 2]], time))
		{
			if (ind * 2 + 1 <= hsize && Eval (l[heap[ind * 2]], time) < Eval (l[heap[ind * 2 + 1]], time))
			{
				swap (heap_pos[heap[ind]], heap_pos[heap[ind * 2 + 1]]);
				swap (heap[ind], heap[ind * 2 + 1]);
				ind = ind * 2 + 1;
			}
			else
			{
				swap (heap_pos[heap[ind]], heap_pos[heap[ind * 2]]);
				swap (heap[ind], heap[ind * 2]);
				ind *= 2;
			}
		}
		else if (ind * 2 + 1 <= hsize && Eval (l[heap[ind]], time) < Eval (l[heap[ind * 2 + 1]], time))
		{
			swap (heap_pos[heap[ind]], heap_pos[heap[ind * 2 + 1]]);
			swap (heap[ind], heap[ind * 2 + 1]);
			ind = ind * 2 + 1;
		}
		else
			break;
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("hillwalk.in", "r", stdin);
	std::freopen ("hillwalk.out", "w", stdout);

	cin >> N;

	for (int a = 0;a < N;a++)
		cin >> l[a].x1 >> l[a].y1 >> l[a].x2 >> l[a].y2,
		cpt[ccpt++] = CritPt (l[a].x1, a, 1, l[a].y1),
		cpt[ccpt++] = CritPt (l[a].x2, a, 0, l[a].y2);

	sort (cpt, cpt + ccpt);
	cur_line = 0;

	for (int a = 0;a < ccpt;a++)
	{
		if (cpt[a].line == 42)
			a=a;
		if (cpt[a].line == 9642)
			a=a;
		if (cpt[a].type == 1 && Eval (l[cpt[a].line], cpt[a].x) <= Eval (l[cur_line], cpt[a].x)) //add line to heap, if it is below cur_line
		{
			if (cpt[a].line == 12033)
				a=a;
			heap[++hsize] = cpt[a].line;
			heap_pos[cpt[a].line] = hsize;
			HeapUp (hsize, cpt[a].x);
		}
		else if (cpt[a].type == 0 && heap_pos[cpt[a].line] != 0) //remove line and check for line on top if that is cur_line
		{
			if (cpt[a].line == 12033)
				a=a;
			l[cpt[a].line].y1 = l[cpt[a].line].y2 = 1e9+1;
			HeapUp (heap_pos[cpt[a].line], cpt[a].x);
			heap[1] = heap[hsize];
			heap_pos[heap[hsize]] = 1;
			heap_pos[cpt[a].line] = 0;
			hsize--;
			HeapDown (1, cpt[a].x);
			if (cpt[a].line == cur_line)
			{
				//cout << Eval (l[cur_line], cpt[a].x) << " " << Eval (l[heap[1]], cpt[a].x) << "\n";
				if (heap[1] == 9642)
					a=a;
				if (Eval (l[cur_line], cpt[a].x) < Eval (l[heap[1]], cpt[a].x))
					a=a;
				ans++;
				if (hsize == 0)
					break;
				cur_line = heap[1];
			}
		}
	}

	cout << ans << "\n";

	return 0;
}