/*
ID: yangchess1
PROG: camelot
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
 
const int MAXN = 26, MAXM = 40, INF = 20000;
const int DX[8] = {-2, -2, -1, -1, +1, +1, +2, +2},
     DY[8] = {-1, +1, -2, +2, -2, +2, -1, +1};
struct Node {
     int x, y;
     bool k;
     Node(int px, int py, bool pk) {
          x = px; y = py; k = pk;
     }
};
int N, M;
int dis[MAXN][MAXM][2], kdis[MAXN][MAXM];
int cost[MAXN][MAXM], kcost[MAXN][MAXM];
 
bool inq[MAXN][MAXM][2];
void bfs(int px, int py)
{
     memset(inq, 0, sizeof(inq));
     for (int i = 0; i < N; i++)
          for (int j = 0; j < M; j++)
               dis[i][j][0] = dis[i][j][1] = INF;
     queue<Node> q;
     q.push(Node(px, py, 0)); dis[px][py][0] = 0;
     while (!q.empty()) {
          Node u = q.front(); q.pop();
          inq[u.x][u.y][u.k] = false;
          int udis = dis[u.x][u.y][u.k];
          for (int i = 0; i < 8; i++) {
               Node v(u.x + DX[i], u.y + DY[i], u.k);
               if (v.x < 0 || v.x >= N || v.y < 0 || v.y >= M) continue;
               if (dis[v.x][v.y][v.k] > udis + 1) {
                     dis[v.x][v.y][v.k] = udis + 1;
                     if (!inq[v.x][v.y][v.k]) {
                          q.push(v); inq[v.x][v.y][v.k] = true;
                     }
               }
          }
          if (!u.k && dis[u.x][u.y][1] > udis + kdis[u.x][u.y]) {
               dis[u.x][u.y][1] = udis + kdis[u.x][u.y];
               if (!inq[u.x][u.y][1]) {
                    q.push(Node(u.x, u.y, 1)); inq[u.x][u.y][1] = true;
               }
          }
     }
}
 
int main()
{
     freopen("camelot.in", "r", stdin);
     freopen("camelot.out", "w", stdout);
     scanf("%d %d", &M, &N);
     int px, py;
     char inp[5];
     scanf("%s %d", inp, &py); px = inp[0] - 'A'; py--;
     for (int i = 0; i < N; i++)
          for (int j = 0; j < M; j++)
               kcost[i][j] = kdis[i][j] = max(abs(px - i), abs(py - j));
 
     while (scanf("%s%d", inp, &py) == 2) {
          px = inp[0] - 'A'; py--;
          bfs(px, py);
          for (int i = 0; i < N; i++)
               for (int j = 0; j < M; j++) {
                    cost[i][j] += dis[i][j][0];
                    kcost[i][j] = min(kcost[i][j], dis[i][j][1] - dis[i][j][0]);
               }
      }
     int ans = INF;
     for (int i = 0; i < N; i++)
          for (int j = 0; j < M; j++)
               ans = min(ans, cost[i][j] + kcost[i][j]);
 
     printf("%d\n", ans);
     fclose(stdin); fclose(stdout);
     return 0;
}/*
#include <fstream>
#include <queue>

const int MAX_CSQR = 780;
const int INFINITY = 200000000;
int ndist[30][26][30][26];

struct Square
{
	int x, y, dist;
};

void NDistBFS (int x, int y, int crow, int ccol)
{
	std::queue<Square> queue;
	Square a, b;
	bool visited[30][26];
	int p, q;

	for (p = 0;p < 30;p++)
		for (q = 0;q < 26;q++)
			visited[p][q] = false;

	a.x = x;
	a.y = y;
	a.dist = 0;
	queue.push (a);

	while (!queue.empty ())
	{
		a = queue.front ();
		queue.pop ();

		if (a.x < 0 || a.x >= crow || a.y < 0 || a.y >= ccol)
			continue;

		if (visited[a.x][a.y] == false || (ndist[x][y][a.x][a.y] > a.dist || ndist[a.x][a.y][x][y] > a.dist))
		{
			b.dist = a.dist + 1;
			b.x = a.x + 1;
			b.y = a.y + 2;
			queue.push (b);
			b.x = a.x + 2;
			b.y = a.y + 1;
			queue.push (b);
			b.x = a.x + 2;
			b.y = a.y - 1;
			queue.push (b);
			b.x = a.x + 1;
			b.y = a.y - 2;
			queue.push (b);
			b.x = a.x - 1;
			b.y = a.y - 2;
			queue.push (b);
			b.x = a.x - 2;
			b.y = a.y - 1;
			queue.push (b);
			b.x = a.x - 2;
			b.y = a.y + 1;
			queue.push (b);
			b.x = a.x - 1;
			b.y = a.y + 2;
			queue.push (b);
		}

		if (ndist[x][y][a.x][a.y] > a.dist || ndist[a.x][a.y][x][y] > a.dist)
			ndist[x][y][a.x][a.y] = ndist[a.x][a.y][x][y] = a.dist;
		
		visited[a.x][a.y] = true;
	}
}

int KDist (int x1, int y1, int x2, int y2)
{
	int a, b;

	if (x1 > x2)
		a = x1 - x2;
	else
		a = x2 - x1;
	if (y1 > y2)
		b = y1 - y2;
	else
		b = y2 - y1;

	if (a > b)
		return a;

	return b;
}

int main ()
{
	std::ifstream in ("camelot.in");
	std::ofstream out ("camelot.out");
	int crow, ccol, cknight, kingpos[2], knightpos[MAX_CSQR][2], close_ndist = INFINITY, small_dist = INFINITY, sumndist, a, b, c, d;
	char tchr;

	for (a = 0;a < 30;a++)
		for (b = 0;b < 26;b++)
			for (c = 0;c < 30;c++)
				for (d = 0;d < 26;d++)
					ndist[a][b][c][d] = INFINITY;
	
	in >> crow >> ccol >> tchr >> kingpos[0];
	kingpos[1] = tchr - 64;

	for (a = 0;!in.eof ();a++)
	{
		in >> tchr >> knightpos[a][0];
		knightpos[a][1] = tchr - 64;
	}

	cknight = a - 1;
	in.close ();

	if (cknight == 0)
	{
		out << "0\n";
		out.close ();

		return 0;
	}

	NDistBFS (kingpos[0] - 1, kingpos[1] - 1, crow, ccol);

	for (a = 0;a < cknight;a++)
		NDistBFS (knightpos[a][0] - 1, knightpos[a][1] - 1, crow, ccol);

	for (a = 0;a < cknight;a++)
	{
		d = KDist (kingpos[0] - 1, kingpos[1] - 1, knightpos[a][0] - 1, knightpos[a][1] - 1);

		if (d < close_ndist)
			close_ndist = d;
	}

	for (a = 0;a < crow;a++)
	{
		for (b = 0;b < ccol;b++)
		{
			sumndist = 0;

			for (c = 0;c < cknight;c++)
				sumndist += ndist[knightpos[c][0] - 1][knightpos[c][1] - 1][a][b];

			if (sumndist + close_ndist < small_dist)
				small_dist = sumndist + close_ndist;

			d = KDist (kingpos[0] - 1, kingpos[1] - 1, a, b);
			if (sumndist + d < small_dist)
				small_dist = sumndist + d;

			for (c = 0;c < cknight;c++)
				if (sumndist + ndist[kingpos[0] - 1][kingpos[1] - 1][a][b] + ndist[knightpos[c][0] - 1][knightpos[c][1] - 1][kingpos[0] - 1][kingpos[1] - 1] - ndist[knightpos[c][0] - 1][knightpos[c][1] - 1][a][b] < small_dist)
					small_dist = sumndist + ndist[kingpos[0] - 1][kingpos[1] - 1][a][b] + ndist[knightpos[c][0] - 1][knightpos[c][1] - 1][kingpos[0] - 1][kingpos[1] - 1] - ndist[knightpos[c][0] - 1][knightpos[c][1] - 1][a][b];
		}
	}

	out << small_dist << "\n";
	out.close ();

	return 0;
}*/
