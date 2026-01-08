//Solution by Yang Yan
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

struct Path
{
	int dest, cost;

	Path ()
	{
		dest = cost = 0;
	}

	Path (int d, int c)
	{
		dest = d;
		cost = c;
	}

	inline bool operator< (const Path& other) const
	{
		return cost > other.cost;
	}
};

const int MAXT = 25000;
vector<Path> road[MAXT], plane[MAXT];
vector<int> cgroup[MAXT];
int cpnt[MAXT], ccpnt, indeg[MAXT], dist[MAXT], zero_in[MAXT], zero_back, zero_front;

void FindCpnt (int cur)
{
	cpnt[cur] = ccpnt;
	cgroup[ccpnt].push_back (cur);
	for (int a = 0;a < road[cur].size ();a++)
		if (cpnt[road[cur][a].dest] == -1)
			FindCpnt (road[cur][a].dest);
}

int main ()
{
	freopen ("roadplane.in", "r", stdin); freopen ("roadplane.out", "w", stdout);

	int T, R, P, S;
	scanf ("%d %d %d %d", &T, &R, &P, &S);

	for (int a = 0, b, c, d;a < R;++a)
	{
		scanf ("%d %d %d", &b, &c, &d);
		b--; c--;
		road[b].push_back (Path (c, d));
		road[c].push_back (Path (b, d));
	}
	for (int a = 0, b, c, d;a < P;++a)
	{
		scanf ("%d %d %d", &b, &c, &d);
		b--; c--;
		plane[b].push_back (Path (c, d));
	}

	memset (cpnt, -1, sizeof (cpnt));
	ccpnt = 0;
	for (int a = 0;a < T;++a)
		if (cpnt[a] == -1)
			FindCpnt (a),
			ccpnt++;

	for (int a = 0;a < T;++a)
		for (int b = 0;b < (int)plane[a].size ();++b)
			indeg[cpnt[plane[a][b].dest]]++;
	for (int a = 0;a < ccpnt;++a)
		if (indeg[a] == 0)
			zero_in[zero_back++] = a;

	const int MDIST = (int)1e9;
	memset (dist, 63, sizeof (dist));
	dist[S - 1] = 0;
	priority_queue<Path> pq;
	int x, y;
	Path top;
	while (zero_front < zero_back)
	{
		int cur_group = zero_in[zero_front++];
		for (int a = 0;a < (int)cgroup[cur_group].size ();++a)
			if (dist[cgroup[cur_group][a]] < MDIST)
				pq.push (Path (cgroup[cur_group][a], dist[cgroup[cur_group][a]]));

		while (!pq.empty ())
		{
			top = pq.top ();
			pq.pop ();
			if (dist[top.dest] != top.cost)
				continue;

			for (int a = 0;a < (int)road[top.dest].size ();++a)
			{
				x = road[top.dest][a].dest;
				y = road[top.dest][a].cost;
				if (dist[x] > top.cost + y)
					dist[x] = top.cost + y,
					pq.push (Path (x, dist[x]));
			}
			for (int a = 0;a < (int)plane[top.dest].size ();++a)
			{
				x = plane[top.dest][a].dest;
				y = plane[top.dest][a].cost;
				if (dist[x] > top.cost + y)
					dist[x] = top.cost + y;
			}
		}

		for (int a = 0;a < (int)cgroup[cur_group].size ();++a)
		{
			for (int b = 0, c = cgroup[cur_group][a];b < (int)plane[c].size ();++b)
			{
				if (--indeg[cpnt[plane[c][b].dest]] == 0)
					zero_in[zero_back++] = cpnt[plane[c][b].dest];
			}
		}
	}

	for (int a = 0;a < T;++a)
		if (dist[a] < MDIST)
			printf ("%d\n", dist[a]);
		else
			puts ("NO PATH");

	return 0;
}