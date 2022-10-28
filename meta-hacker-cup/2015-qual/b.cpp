#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

char Adv (char x)
{
	if (x == '<')
		return '^';
	if (x == '^')
		return '>';
	if (x == '>')
		return 'v';
	if (x == 'v')
		return '<';
}

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int T, M, N;
	cin >> T;

	char prog[128][5];
	prog['^'][0] = '^';
	prog['>'][0] = '>';
	prog['v'][0] = 'v';
	prog['<'][0] = '<';
	for (int a = 1;a <= 4;a++)
	{
		for (int b = 0;b < 128;b++)
			prog[b][a] = 'F';
		prog['^'][a] = Adv (prog['^'][a - 1]);
		prog['>'][a] = Adv (prog['>'][a - 1]);
		prog['v'][a] = Adv (prog['v'][a - 1]);
		prog['<'][a] = Adv (prog['<'][a - 1]);
	}

	char ref[4] = {'v', '<', '^', '>'};

	char maze[100][100];
	int dx[4] = {0, 1, 0, -1},
		dy[4] = {-1, 0, 1, 0};
	int dist[40000];
	for (int k = 1;k <= T;k++)
	{
		cin >> M >> N;
		vector<int> edge[40000];

		int start, goal;
		for (int a = 0;a < M;a++)
		{
			cin.get ();
			for (int b = 0;b < N;b++)
			{
				maze[a][b] = cin.get ();
				if (maze[a][b] == 'S')
					start = a * 100 + b;
				if (maze[a][b] == 'G')
					goal = a * 100 + b;
			}
		}

		for (int i = 0;i < 4;i++)
		{
			for (int a = 0;a < M;a++)
			{
				for (int b = 0;b < N;b++)
				{
					for (int c = 0;c < 4;c++)
					{
						int row = a + dy[c], col = b + dx[c];
						if (!(row >= 0 && row < M && col >= 0 && col < N && (maze[row][col] == '.' || maze[row][col] == 'S' || maze[row][col] == 'G')))
							continue;
						bool flag = true;
						for (int d = 0, e, f;d < 4;d++)
						{
							e = row, f = col;
							while (e >= 0 && e < M && f >= 0 && f < N)
							{
								if (maze[e][f] == '#')
									break;
								if (prog[maze[e][f]][i + 1] == ref[d])
								{
									flag = false;
									break;
								}
								else if (prog[maze[e][f]][i + 1] == '^' || prog[maze[e][f]][i + 1] == '>' || prog[maze[e][f]][i + 1] == '<' || prog[maze[e][f]][i + 1] == 'v')
									break;
								e += dy[d];
								f += dx[d];
							}
							if (flag == false)
								break;
						}
						if (flag)
							edge[i * 10000 + a * 100 + b].push_back ((i + 1) % 4 * 10000 + row * 100 + col);
					}
				}
			}
		}

		//run dijkstras
		priority_queue< pair<int, int> > pq;
		pq.push (make_pair (0, start));
		memset (dist, 63, sizeof (dist));
		dist[start] = 0;
		while (!pq.empty ())
		{
			pair<int, int> top = pq.top ();
			pq.pop ();

			if (dist[top.second] != top.first)
				continue;

			for (int a = 0;a < edge[top.second].size ();a++)
				if (dist[edge[top.second][a]] > top.first + 1)
					dist[edge[top.second][a]] = top.first + 1,
					pq.push (make_pair (top.first + 1, edge[top.second][a]));
		}

		int ans = min (min (dist[goal], dist[10000 + goal]), min (dist[20000 + goal], dist[30000 + goal]));
		if (ans < 1e9)
			cout << "Case #" << k << ": " << ans << "\n";
		else
			cout << "Case #" << k << ": impossible\n";
	}

	return 0;
}