/*
ID: yangchess1
PROG: window
LANG: C++
*/
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
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//Linked list to store windows.
//O(1) for first 4 operations, O(62) for operation 5. Total time: O(500*62).
//Split windows by all windows above it.

struct Window
{
	Window *last, *next;
	int x[2], y[2];

	Window ()
	{
		last = next = NULL;
		x[0] = x[1] = y[0] = y[1] = 0;
	}

	int Area ()
	{
		if (x[0] > x[1] || y[0] > y[1])
			return -1;
		return (x[1] - x[0]) * (y[1] - y[0]);
	}
};

int main ()
{
	ios_base::sync_with_stdio (false);
	std::freopen ("window.in", "r", stdin);
	std::freopen ("window.out", "w", stdout);

	Window *wind[128], first, last;
	vector<Window> vis;

	cout << fixed << setprecision (3);

	//Create dummies.
	first.last = NULL;
	first.next = &last;
	last.last = &first;
	last.next = NULL;

	while (!cin.fail ())
	{
		char comm = cin.get (), id;
		cin.get ();
		id = cin.get ();
		cin.get ();

		if (comm == 'w')
		{
			int x[2], y[2];
			cin >> x[0];
			cin.get ();
			cin >> y[0];
			cin.get ();
			cin >> x[1];
			cin.get ();
			cin >> y[1];
			cin.get ();

			if (x[0] > x[1])
				swap (x[0], x[1]);
			if (y[0] > y[1])
				swap (y[0], y[1]);
			
			wind[id] = new Window;
			wind[id]->last = &first;
			wind[id]->next = first.next;
			wind[id]->x[0] = x[0];
			wind[id]->x[1] = x[1];
			wind[id]->y[0] = y[0];
			wind[id]->y[1] = y[1];
			first.next->last = wind[id];
			first.next = wind[id];
		}
		else if (comm == 't')
		{
			wind[id]->last->next = wind[id]->next;
			wind[id]->next->last = wind[id]->last;
			wind[id]->last = &first;
			wind[id]->next = first.next;
			first.next->last = wind[id];
			first.next = wind[id];
		}
		else if (comm == 'b')
		{
			wind[id]->last->next = wind[id]->next;
			wind[id]->next->last = wind[id]->last;
			wind[id]->next = &last;
			wind[id]->last = last.last;
			last.last->next = wind[id];
			last.last = wind[id];
		}
		else if (comm == 'd')
		{
			wind[id]->last->next = wind[id]->next;
			wind[id]->next->last = wind[id]->last;
			delete wind[id];
		}
		else if (comm == 's')
		{
			Window *curr = wind[id]->last, red, create[4];
			
			vis.clear ();
			vis.push_back (*wind[id]);

			while (curr != &first)
			{
				//Split each window.
				int s = vis.size ();
				for (int a = 0;a < s;a++)
				{
					red.x[0] = max (vis[a].x[0], curr->x[0]);
					red.y[0] = max (vis[a].y[0], curr->y[0]);
					red.x[1] = min (vis[a].x[1], curr->x[1]);
					red.y[1] = min (vis[a].y[1], curr->y[1]);
					
					if (red.Area () > 0)
					{
						create[0].x[0] = vis[a].x[0];
						create[0].x[1] = red.x[0];
						create[0].y[0] = red.y[0];
						create[0].y[1] = red.y[1];
						create[1].x[0] = red.x[1];
						create[1].x[1] = vis[a].x[1];
						create[1].y[0] = red.y[0];
						create[1].y[1] = red.y[1];
						create[2].x[0] = vis[a].x[0];
						create[2].x[1] = vis[a].x[1];
						create[2].y[0] = vis[a].y[0];
						create[2].y[1] = red.y[0];
						create[3].x[0] = vis[a].x[0];
						create[3].x[1] = vis[a].x[1];
						create[3].y[0] = red.y[1];
						create[3].y[1] = vis[a].y[1];

						for (int b = 0;b < 4;b++)
							if (create[b].Area () > 0)
								vis.push_back (create[b]);
					}
					else
						vis.push_back (vis[a]);
				}

				//Erase at the same time - faster.
				vis.erase (vis.begin (), vis.begin () + s);

				curr = curr->last;
			}

			int sum = 0;
			for (int a = 0;a < vis.size ();a++)
				sum += vis[a].Area ();

			cout << sum * 100.0 / wind[id]->Area () << "\n";
		}

		cin.get ();
	}

	return 0;
}