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

//#define DEBUG 0
#define DEBUG 1

//Use Dijkstra's to find shortest path from 1 to N, recording vertices O(62500). Try doubling each edge and use Dijkstra's each time, which is ~250 * O(62500) = O(1562500). So, run time is O(N^3), which should be in time.

bool visited[250];

void DijkstraAlgorithmDirectedRecorded (bool neighbor[250][250], unsigned long long distance[250][250], unsigned int parent[250], const unsigned int source, const unsigned int cvertices)
{
	unsigned long long small_dist;
	unsigned int current_vert, small_vert;
	unsigned int a, b;

	//Initialization.
	current_vert = source;

	for (a = 0;a < cvertices;a++)
		visited[a] = false;

	visited[current_vert] = true;
	distance[current_vert][current_vert] = 0;
	parent[0] = numeric_limits<unsigned int>::max ();

	//Start the algorithm.
	for (a = 1;a < cvertices;a++)
	{
		//Update all the distances to the neighbors of the current pasture.
		for (b = 0;b < cvertices;b++)
		{
			//If the pasture is a neighbor of the curent pasture and has not been visited yet. Note the order of neighbor[current_ver][b] is important because the graph is directed.
			if (neighbor[current_vert][b] == true && visited[b] == false)
			{
				//Check if the pasture has a shorter sum (distance to the current + the distance of the current to the source) than already listed. Again, the order is important.
				if (distance[current_vert][b] + distance[source][current_vert] < distance[source][b])
				{
					distance[source][b] = distance[current_vert][b] + distance[source][current_vert];
					parent[b] = current_vert;
				}

				if (source == current_vert)
					parent[b] = current_vert;
			}
		}

		//Pick the closest neighbor not visited, and set it as the next current pasture.
        small_dist = numeric_limits<unsigned long long>::max ();

		for (b = 0;b < cvertices;b++)
		{
			if (visited[b] == false && distance[source][b] < small_dist)
			{
				small_dist = distance[source][b];
				small_vert = b;
			}
		}

		visited[small_vert] = true;
		current_vert = small_vert;
	}
}

void DijkstraAlgorithmDirected (bool neighbor[250][250], unsigned long long distance[250][250], const unsigned int source, const unsigned int cvertices)
{
	unsigned long long small_dist;
	unsigned int current_vert, small_vert;
	unsigned int a, b;

	//Initialization.
	current_vert = source;

	for (a = 0;a < cvertices;a++)
		visited[a] = false;

	visited[current_vert] = true;
	distance[current_vert][current_vert] = 0;

	//Start the algorithm.
	for (a = 1;a < cvertices;a++)
	{
		//Update all the distances to the neighbors of the current pasture.
		for (b = 0;b < cvertices;b++)
		{
			//If the pasture is a neighbor of the curent pasture and has not been visited yet. Note the order of neighbor[current_ver][b] is important because the graph is directed.
			if (neighbor[current_vert][b] == true && visited[b] == false)
			{
				//Check if the pasture has a shorter sum (distance to the current + the distance of the current to the source) than already listed. Again, the order is important.
				if (distance[current_vert][b] + distance[source][current_vert] < distance[source][b])
					distance[source][b] = distance[current_vert][b] + distance[source][current_vert];
			}
		}

		//Pick the closest neighbor not visited, and set it as the next current pasture.
        small_dist = numeric_limits<unsigned long long>::max ();

		for (b = 0;b < cvertices;b++)
		{
			if (visited[b] == false && distance[source][b] < small_dist)
			{
				small_dist = distance[source][b];
				small_vert = b;
			}
		}

		visited[small_vert] = true;
		current_vert = small_vert;
	}
}

unsigned long long dist[250][250], dist_mem[250][250];
unsigned int parent[250];
bool adj[250][250];
size_t array_size = 250 * 250 * sizeof(unsigned long long);

int main ()
{
	std::ifstream in ("rblock.in");
	std::ofstream out ("rblock.out");
	unsigned long long sdist, ans = 0;
	unsigned int curr_path;
	int cfield, cpath;

	in >> cfield >> cpath;

	for (int a = 0, b;a < cfield;a++)
	{
		for (b = 0;b < cfield;b++)
		{
			adj[a][b] = false;
			dist_mem[a][b] = numeric_limits<unsigned long long>::max ();
		}
	}

	for (int a, b, c;cpath > 0;cpath--)
	{
		in >> a >> b >> c;
		adj[a - 1][b - 1] = adj[b - 1][a - 1] = true;
		dist_mem[a - 1][b - 1] = dist_mem[b - 1][a - 1] = c;
	}

	in.close ();

	memcpy (dist, dist_mem, array_size);
	DijkstraAlgorithmDirectedRecorded (adj, dist, parent, 0, cfield);
	sdist = dist[0][cfield - 1];
	curr_path = cfield - 1;

	//Try changing all path lengths.
	while (parent[curr_path] != numeric_limits<unsigned int>::max ())
	{
		//Restore dist array.
		memcpy (dist, dist_mem, array_size);

		//Double this path.
		dist[curr_path][parent[curr_path]] = dist[parent[curr_path]][curr_path] = 2 * dist[curr_path][parent[curr_path]];

		//Run Dijkstra's, then compare shortest distances.
		DijkstraAlgorithmDirected (adj, dist, 0, cfield);

		if (dist[0][cfield - 1] > ans)
			ans = dist[0][cfield - 1];

		//Update path.
		curr_path = parent[curr_path];
	}

	out << ans - sdist << "\n";
	out.close ();

	return 0;
}