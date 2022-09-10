#include <algorithm>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 25413;
const int INF = 2000000000;

struct Node
{
	int num;
	vector<int> next;
};

int cdict, parent[MAXN];
char **dict;
Node graph[MAXN];

int BSearch (char *s, int low, int high)
{
	if (low == high - 1)
	{
		if (strcmp (dict[low], s) == 0)
			return low;
		else
			return -1;
	}
	else
	{
		int a = strcmp (s, dict[(high + low) / 2]);
		if (a >= 0)
			return BSearch (s, (high + low) / 2, high);
		if (a < 0)
			return BSearch (s, low, (high + low) / 2);
	}
}

void Dijkstra (int source)
{
	int curr = source, dist[MAXN], min;
	bool in_tree[MAXN];

	for (int a = 0;a < cdict;a++)
	{
		parent[a] = -1;
		dist[a] = INF;
		in_tree[a] = false;
	}
	parent[source] = source;
	dist[source] = 0;

	for (int a = 1;a < cdict;a++)
	{
		in_tree[curr] = true;

		//Update.
		for (int b = 0;b < graph[curr].next.size ();b++)
		{
			if (in_tree[graph[curr].next[b]] == false && dist[graph[curr].next[b]] > dist[curr] + 1)
			{
				dist[graph[curr].next[b]] = dist[curr] + 1;
				parent[graph[curr].next[b]] = curr;
			}
		}

		//Choose.
		min = INF;
		for (int b = 0;b < cdict;b++)
		{
			if (dist[b] < min && in_tree[b] == false)
			{
				min = dist[b];
				curr = b;
			}
		}

		if (min == INF)
			break;
	}
}

bool Comp (char *a, char *b)
{
	return strcmp(a, b) < 0;
}

int main ()
{
	//freopen ("Text.txt", "r", stdin);
	ios::ios_base::sync_with_stdio (false);

	int start, end, i;
	char temp[17];

	dict = new char *[MAXN];
	for (int a = 0;a < MAXN;a++)
		dict[a] = new char[17];

	while (scanf("%[^\n]%*c", dict[cdict++]) == 1);
	cdict--;

	for (int a = 0;a < cdict;a++)
		graph[a].num = a;

	std::sort (dict, dict + cdict, Comp);

	/*for (int a = 0;a < cdict;a++)
		cout << dict[a] << "\n";*/

	//Construct.
	for (int a = 0;a < cdict;a++)
	{
		int l = strlen (dict[a]);

		//Insert.
		/*for (int b = 0;b <= l;b++)
		{
			for (int c = 'a';c <= 'z';c++)
			{
				for (int d = 0;d < b;d++)
					temp[d] = dict[a][d];
				temp[b] = c;
				for (int d = b;d <= l;d++)
					temp[d + 1] = dict[a][d];
				i = BSearch (temp, 0, cdict);
				if (i != -1)
					graph[a].next.push_back (i);
			}
		}*/

		//Modify.
		for (int b = 0;b < l;b++)
		{
			for (int c = 'a';c <= 'z';c++)
			{
				if (c != dict[a][b])
				{
					strcpy (temp, dict[a]);
					temp[b] = c;
					i = BSearch (temp, 0, cdict);
					if (i != -1)
						graph[a].next.push_back (i);
				}
			}
		}

		//Delete.
		/*for (int b = 0;b < l;b++)
		{
			for (int d = 0;d < b;d++)
				temp[d] = dict[a][d];
			for (int d = b + 1;d <= l;d++)
				temp[d - 1] = dict[a][d];
			i = BSearch (temp, 0, cdict);
			if (i != -1)
				graph[a].next.push_back (i);
		}*/
	}

	bool first = true;

	while (true)
	{
		memset (temp, 0, 17 * sizeof (char));
		scanf ("%s", temp);

		if (strcmp (temp, "") == 0)
			break;

		start = BSearch (temp, 0, cdict);
		scanf ("%s", temp);
		end = BSearch (temp, 0, cdict);

		if (first == false)
			printf ("\n\n");

		if (start == -1 || end == -1)
		{
			printf ("No solution.");
			first = false;
			continue;
		}

		if (start == end)
		{
			if (graph[start].next.size () == 0)
				printf ("No solution.");
			else
				printf ("%s\n%s\n%s", dict[start], dict[graph[start].next[0]], dict[end]);

			first = false;
			continue;
		}

		Dijkstra (end);
		i = start;

		if (parent[i] == -1)
		{
			printf ("No solution.");
			first = false;
			continue;
		}

		while (i != end)
		{
			printf ("%s\n", dict[i]);
			i = parent[i];
		}
		
		printf ("%s", dict[end]);
		first = false;
	}

	printf ("\n");

	//Free up memory.
	for (int a = 0;a < MAXN;a++)
		delete[] dict[a];

	delete[] dict;

	return 0;
}