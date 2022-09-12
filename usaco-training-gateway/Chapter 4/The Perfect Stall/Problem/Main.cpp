/*
ID: yangchess1
LANG: C++
PROB: stall4
*/

/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

When submitting the program, define DEBUG 0. When debugging, define DEBUG 1. In the program, for debugging information, use if (DEBUG){...} such that when it is submitted we don't have that code there.

Use this code to immediately terminate if the time is too much to handle: if (clock() > 0.95 * CLOCKS_PER_SEC) break;

Backup this program every so often in the Backup.txt files in case something goes wrong later.

Useful constants: INT_MAX, INT_MIN, UINT_MAX, _I64_MIN, _I64_MAX, _UI64_MAX.
*/

#include <algorithm>
#include <bitset>
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

const unsigned int	MAX_COW	= 200;

//unsigned int MaxFlow (bool **flow_mat, unsigned int **cap_mat, const unsigned int start, const unsigned int end, const unsigned int cvert); determines the maximum flow of a graph from the vertice 'start' to the 'end'. This graph can be directed. 'flow_mat' will indicate a flow from [a] to [b]. 'cap_mat' will indicate the capacity of the flow from [a] to [b]. Make sure none of the passed parameters are equal to UINT_MAX as a safety precaution, because UINT_MAX is used as a special value in the function. Note that this function can only operate on graphs with 2 directed edges between every node. See another version of this function for other graph times and representations.
template<const unsigned int array_size>
unsigned int MaxFlow (const bool p_edge_adj[][array_size], const unsigned int p_edge_cap[][array_size], const unsigned int vstart, const unsigned int vend, const unsigned int cvert)
{
	bool *vvisited, **edge_adj;
	unsigned int current_vert, max_cap, max_vert, total_flow, *vparent, *path_cap, **edge_cap;
	unsigned int a, b;

	//Initialize local arrays for storage of the adjacency matrix and the flow of arcs on the graph. Also, initialize arrays for later use in a modified Dijkastra's algorithm.
	{
		total_flow = 0;
		vvisited = new bool[cvert];
		vparent = new unsigned int [cvert];
		path_cap = new unsigned int [cvert];
		edge_adj = new bool *[cvert];
		edge_cap = new unsigned int *[cvert];

		for (a = 0;a < cvert;a++)
		{
			edge_adj[a] = new bool[cvert];
			edge_cap[a] = new unsigned int[cvert];

			for (b = 0;b < cvert;b++)
			{
				edge_adj[a][b] = p_edge_adj[a][b];
				edge_cap[a][b] = p_edge_cap[a][b];
			}
		}
	}

	//Start a seemingly infinite loop, with the terminating condition if no paths can be found from the start vertice to the end vertice positioned in the middle of the loop.
	while (true)
	{
		//Find the path with the largest capacity from the start point to the end. To do this, we can use a version of Dijkstra's algorithm, but find the path with the largest capacity.
		{
			for (a = 0;a < cvert;a++)
			{
				vvisited[a] = false;
				vparent[a] = UINT_MAX; //We use UINT_MAX to signify a special value.
				path_cap[a] = UINT_MAX; //path_cap represents the capacity of the path from vstart to a.
			}

			vvisited[vstart] = true;
			current_vert = vstart;

			//Loop through all the vertices.
			for (a = 1;a < cvert && current_vert != vend;a++)
			{
				//Update all path_caps that end on a neighbor of vertice b.
				for (b = 0;b < cvert;b++)
				{
					if (edge_adj[current_vert][b] == true && vvisited[b] == false && b != vstart)
					{
						//Check which part of the path from vstart to b has a lower capacity. These two parts are 1: from vstart to current_vert and 2: from current_vert to a neighbor b.
						if ((path_cap[current_vert] == UINT_MAX) /*A special value. This probably means that current_vert = vstart.*/ && (edge_cap[current_vert][b] > path_cap[b] || path_cap[b] == UINT_MAX))
						{
							path_cap[b] = edge_cap[current_vert][b];
							vparent[b] = current_vert;
						}
						else if ((path_cap[current_vert] > edge_cap[current_vert][b]) && (edge_cap[current_vert][b] > path_cap[b] || path_cap[b] == UINT_MAX))
						{
							path_cap[b] = edge_cap[current_vert][b];
							vparent[b] = current_vert;
						}
						else if (path_cap[current_vert] <= (edge_cap[current_vert][b]) && (path_cap[current_vert] > path_cap[b] || path_cap[b] == UINT_MAX))
						{
							path_cap[b] = path_cap[current_vert];
							vparent[b] = current_vert;
						}
					}
				}

				//Choose the next vertice to visit based on the largest path_cap.
				max_cap = 0;
				max_vert = UINT_MAX;

				for (b = 0;b < cvert;b++)
				{
					if (vvisited[b] == false && path_cap[b] > max_cap && path_cap[b] != UINT_MAX)
					{
						max_cap = path_cap[b];
						max_vert = b;
					}
				}

				if (max_vert == UINT_MAX && max_cap == 0)
					break;

				vvisited[max_vert] = true;
				current_vert = max_vert;
			}
		}
		
		if (max_vert == UINT_MAX && max_cap == 0)
			break;

		//The break condition of the larger while loop: if we couldn't find a path from the start vertice to the end.
		if (vparent[vend] == UINT_MAX)
			break;

		//Add this bottleneck to the total flow from vstart to vend.
		total_flow += path_cap[vend];

		//Reduce all flows along this path by the bottleneck, and add a reverse flow with the bottleneck.
		{
			a = vend;

			while (a != vstart)
			{
				if (edge_cap[vparent[a]][a] > path_cap[vend])
					edge_cap[vparent[a]][a] -= path_cap[vend];
				else
				{
					edge_adj[vparent[a]][a] = false;
					edge_cap[vparent[a]][a] = 0;
				}

				if (edge_adj[a][vparent[a]] == false)
				{
					edge_adj[a][vparent[a]] = true;
					edge_cap[a][vparent[a]] = path_cap[vend];
				}
				else
					edge_cap[a][vparent[a]] += path_cap[vend];

				a = vparent[a];
			}
		}
	}

	//Deallocate the free store.
	{
		delete[] vvisited;
		delete[] vparent;
		delete[] path_cap;

		for (a = 0;a < cvert;a++)
		{
			delete[] edge_adj[a];
			delete[] edge_cap[a];
		}
		
		delete[] edge_adj;
		delete[] edge_cap;
	}

	//Once we break, we are done. Return the total flow.
	return total_flow;
}

int main ()
{
	std::ifstream in ("stall4.in");
	std::ofstream out ("stall4.out");
	bool edge_adj[MAX_COW * 2 + 2][MAX_COW * 2 + 2];
	unsigned int ccow, cstall, edge_weight[MAX_COW * 2 + 2][MAX_COW * 2 + 2];
	unsigned int a, b, c;

	for (a = 0;a < MAX_COW * 2 + 2;a++)
	{
		for (b = 0;b < MAX_COW * 2 + 2;b++)
		{
			edge_adj[a][b] = false;
			edge_weight[a][b] = 0;
		}
	}

	in >> ccow >> cstall;
	
	//Node 0 is the 'source' node, and node MAX_COW * 2 + 1 is the 'sink'. Use the MaxFlow algorithm, but the Maximum Matching extension.
	for (a = 1;a < ccow + 1;a++)
	{
		edge_adj[0][a] = true;
		edge_weight[0][a] = 1;
	}

	for (a = MAX_COW + 1;a < MAX_COW * 2 + 1;a++)
	{
		edge_adj[a][MAX_COW * 2 + 1] = true;
		edge_weight[a][MAX_COW * 2 + 1] = 1;
	}

	for (a = 0;a < ccow;a++)
	{
		in >> b;

		for (;b > 0;b--)
		{
			in >> c;
			edge_adj[a + 1][MAX_COW + c] = true;
			edge_weight[a + 1][MAX_COW + c] = 1;
		}
	}

	in.close ();
	out << MaxFlow (edge_adj, edge_weight, 0, MAX_COW * 2 + 1, MAX_COW * 2 + 2) << "\n";
	out.close ();

	return 0;
}