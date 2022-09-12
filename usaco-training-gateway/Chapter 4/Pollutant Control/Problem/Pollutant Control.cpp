/*
ID: yangchess1
LANG: C++
PROB: milk6
*/

/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

Backup this program every so often in the Backup files in case something goes wrong later.

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

//These two structures represent a network graph. They are used with the MaxFlow function.
struct NetworkVertice;
struct NetworkEdge;

struct NetworkEdge
{
	NetworkVertice *destination;
	unsigned long long int edge_cap;
};

struct NetworkVertice
{
	vector<NetworkEdge> neighbor;
};

//Typical edge array.
struct Truck
{
	unsigned long long int origin, order, sum_cost, destination;
	vector<int> cost, index;
};

//unsigned int MaxFlow (const NetworkVertice *net_vert, const unsigned int vstart, const unsigned int vend, const unsigned int cvert); determines the maximum flow of a graph from the vertice 'start' to the 'end'. This graph can be directed. 'flow_mat' will indicate a flow from [a] to [b]. 'cap_mat' will indicate the capacity of the flow from [a] to [b]. Make sure none of the passed parameters are equal to UINT_MAX as a safety precaution, because UINT_MAX is used as a special value in the function. This function requires the structures NetworkEdge and NetworkVertice to represent a network graph. Also, make sure you have a backup of NetworkVertice *net_vert, because this function will edit the variable.
unsigned long long int MaxFlow (NetworkVertice *net_vert, const unsigned long long int vstart, const unsigned long long int vend, const unsigned long long int cvert)
{
	NetworkEdge temp_edge;
	bool *vvisited;
	unsigned long long int current_vert, max_vert, max_cap, total_flow, *path_cap, *vparent;
	unsigned long long int a, b, c, d, e;

	//Initialize arrays for later use in a modified Dijkastra's algorithm.
	total_flow = 0;
	vvisited = new bool[cvert];
	vparent = new unsigned long long int[cvert];
	path_cap = new unsigned long long int[cvert];

	//Start a seemingly infinite loop, with the terminating condition if no paths can be found from the start vertice to the end vertice positioned in the middle of the loop.
	while (true)
	{
		//Find the path with the largest capacity from the start point to the end. To do this, we can use a version of Dijkstra's algorithm, but find the path with the largest capacity.
		{
			for (a = 0;a < cvert;a++)
			{
				vvisited[a] = false;
				vparent[a] = numeric_limits<unsigned long long int>::max (); //We use UINT_MAX to signify a special value.
				path_cap[a] = numeric_limits<unsigned long long int>::max (); //path_cap represents the capacity of the path from vstart to a.
			}

			vvisited[vstart] = true;
			current_vert = vstart;

			//Loop through all the vertices.
			for (a = 1;a < cvert && current_vert != vend;a++)
			{
				c = net_vert[current_vert].neighbor.size ();

				//Update all path_caps that end on a neighbor of vertice b.
				for (b = 0;b < c;b++)
				{
					d = net_vert[current_vert].neighbor.at (b).edge_cap;

					//Find the vertice that the bth NetworkEdge of the current_vert goes to.
					for (e = 0;e < cvert;e++)
						if (net_vert[current_vert].neighbor.at (b).destination == &net_vert[e])
							break;

					//Check which part of the path from vstart to b has a lower capacity. These two parts are 1: from vstart to current_vert and 2: from current_vert to a neighbor b.
					if ((path_cap[current_vert] == numeric_limits<unsigned long long int>::max ()) /*A special value. This probably means that current_vert = vstart.*/ && (d > path_cap[e] || path_cap[e] == numeric_limits<unsigned long long int>::max ()))
					{
						path_cap[e] = net_vert[current_vert].neighbor.at (b).edge_cap;
						vparent[e] = current_vert;
					}
					else if ((path_cap[current_vert] > d) && (d > path_cap[e] || path_cap[e] == numeric_limits<unsigned long long int>::max ()))
					{
						path_cap[e] = net_vert[current_vert].neighbor.at (b).edge_cap;
						vparent[e] = current_vert;
					}
					else if ((path_cap[current_vert] <= d) && (path_cap[current_vert] > path_cap[e] || path_cap[e] == numeric_limits<unsigned long long int>::max ()))
					{
						path_cap[e] = path_cap[current_vert];
						vparent[e] = current_vert;
					}
				}

				//Choose the next vertice to visit based on the largest path_cap.
				max_cap = 0;
				max_vert = numeric_limits<unsigned long long int>::max ();

				for (b = 0;b < cvert;b++)
				{
					if (vvisited[b] == false && path_cap[b] > max_cap && path_cap[b] != numeric_limits<unsigned long long int>::max ())
					{
						max_cap = path_cap[b];
						max_vert = b;
					}
				}

				if (max_vert == numeric_limits<unsigned long long int>::max () && max_cap == 0)
					break;

				vvisited[max_vert] = true;
				current_vert = max_vert;
			}
		}
		
		if (max_vert == numeric_limits<unsigned long long int>::max () && max_cap == 0)
			break;

		//The break condition of the larger while loop: if we couldn't find a path from the start vertice to the end.
		if (vparent[vend] == numeric_limits<unsigned long long int>::max ())
			break;

		//Add this bottleneck to the total flow from vstart to vend.
		total_flow += path_cap[vend];

		//Reduce all flows along this path by the bottleneck, and add a reverse flow with the bottleneck.
		{
			a = vend;

			while (a != vstart)
			{
				//Find the NetworkEdge from vparent[a] to a.
				c = net_vert[vparent[a]].neighbor.size ();

				for (b = 0;b < c;b++)
					if (net_vert[vparent[a]].neighbor.at (b).destination == &net_vert[a])
						break;

				if (net_vert[vparent[a]].neighbor.at (b).edge_cap > path_cap[vend])
					net_vert[vparent[a]].neighbor.at (b).edge_cap -= path_cap[vend];
				else
					net_vert[vparent[a]].neighbor.erase (net_vert[vparent[a]].neighbor.begin () + b);

				//Find the NetworkEdge from a to vparent[a].
				c = net_vert[a].neighbor.size ();

				for (b = 0;b < c;b++)
					if (net_vert[a].neighbor.at (b).destination == &net_vert[vparent[a]])
						break;

				if (b == c) //No such NetworkEdge, so add one.
				{
					temp_edge.destination = &net_vert[vparent[a]];
					temp_edge.edge_cap = path_cap[vend];
					net_vert[a].neighbor.push_back (temp_edge);
				}
				else //NetworkEdge from a to vparent[a] exists as a's bth NetworkEdge.
					net_vert[a].neighbor.at (b).edge_cap += path_cap[vend];

				a = vparent[a];
			}
		}
	}

	//Deallocate the free store.
	delete[] vvisited;
	delete[] vparent;
	delete[] path_cap;

	//Once we break, we are done. Return the total flow.
	return total_flow;
}

bool TruckComp (Truck x, Truck y)
{
	return (x.sum_cost < y.sum_cost);
}

int main ()
{
	std::ifstream in ("milk6.in");
	std::ofstream out ("milk6.out");
	vector<Truck> trucks; //A list of the edges, used in the minimum-cut algorithm.
	vector<unsigned long long int> solution;
	Truck temp_truck;
	NetworkEdge temp_edge;
	NetworkVertice vertices[32], backup[32];
	unsigned long long int cvert, cedge, min_cost = 0;
	unsigned long long int a, b, c, d, e;

	in >> cvert >> cedge;

	for (a = 0;a < cedge;a++)
	{
		in >> b >> c >> d;
		temp_edge.destination = &vertices[c - 1];
		temp_edge.edge_cap = d * 1001 + 1; //(edge_cap) * 1001 + 1 to all edge caps because we want the least amount of edges in a tie of equal cost. The multiplication ensures that the +1 does not get large enough to interfere with the original edge_cap (which could get as big as 1 * 1001, while there could only be a max of 1000 +1's), but does make a difference to determine the route with the smallest number of edges.
		temp_truck.origin = b - 1;
		temp_truck.order = vertices[b - 1].neighbor.size ();
		temp_truck.cost.push_back (d * 1001 + 1);
		temp_truck.index.push_back (a);
		temp_truck.destination = c - 1;
		temp_truck.sum_cost = d * 1001 + 1;
		vertices[b - 1].neighbor.push_back (temp_edge);
		trucks.push_back (temp_truck);
		temp_truck.cost.clear ();
		temp_truck.index.clear ();
	}

	in.close ();

	//Modify our vertices graph such that multiple edges flowing the same direction from and to the same vertices will be combined together, as to let the MaxFlow graph function properly. Keep track of these changes in our edges array, trucks.
	for (a = 0;a < trucks.size ();a++)
	{
		//Check if trucks[a] has the same origin and destination as other trucks.
		for (b = a + 1;b < trucks.size ();b++)
		{
			if (trucks[a].origin == trucks[b].origin && trucks[a].destination == trucks[b].destination)
			{
				//Combine trucks[b]'s stats into trucks[a].
				for (c = 0;c < trucks[b].cost.size ();c++)
					trucks[a].cost.push_back (trucks[b].cost[c]);

				for (c = 0;c < trucks[b].index.size ();c++)
					trucks[a].index.push_back (trucks[b].index[c]);

				trucks[a].sum_cost += trucks[b].sum_cost;

				//Update the actual edge to match trucks[a]'s stats.
				vertices[trucks[a].origin].neighbor[trucks[a].order].edge_cap = trucks[a].sum_cost;

				//Delete trucks[b] and the actual edge and adjust all trucks[n].order's.
				vertices[trucks[b].origin].neighbor.erase (vertices[trucks[b].origin].neighbor.begin () + trucks[b].order);

				for (c = 0;c < trucks.size ();c++)
				{
					if (trucks[c].origin == trucks[b].origin && trucks[c].order > trucks[b].order)
						trucks[c].order--;
				}

				trucks.erase (trucks.begin () + b--);
			}
		}
	}

	cedge = trucks.size ();

	//Save a backup of our vertices array, because MaxFlow will mess it up each time the function is run.
	for (a = 0;a < cvert;a++)
		backup[a] = vertices[a];

	//Sort the edges (trucks, in this case, as this is the only list of edges we maintain).
	sort (trucks.begin (), trucks.end (), TruckComp);

	//Try removing each edge in increasing cost order. If it reduces the max flow by it's cost, then we remove it permanantly and add it to our set of edges to remove.
	b = MaxFlow (vertices, 0, cvert - 1, cvert);
	for (a = 0;a < cvert;a++)
		vertices[a] = backup[a];

	for (a = 0;a < trucks.size ();a++)
	{
		//Remove the edge.
		temp_edge = vertices[trucks[a].origin].neighbor[trucks[a].order];
		vertices[trucks[a].origin].neighbor.erase (vertices[trucks[a].origin].neighbor.begin () + trucks[a].order);
		backup[trucks[a].origin].neighbor.erase (backup[trucks[a].origin].neighbor.begin () + trucks[a].order);

		c = MaxFlow (vertices, 0, cvert - 1, cvert);
		for (d = 0;d < cvert;d++)
			vertices[d] = backup[d];

		if (b - c == trucks[a].sum_cost)
		{
			//Update all 'order's.
			for (e = 0;e < trucks.size ();e++)
			{
				if (trucks[e].origin == trucks[a].origin && trucks[e].order > trucks[a].order)
					trucks[e].order--;
			}

			for (e = 0;e < trucks[a].index.size ();e++)
				solution.push_back (trucks[a].index[e] + 1);
			
			min_cost += (trucks[a].sum_cost - trucks[a].index.size ()) / 1001;
			trucks.erase (trucks.begin () + a--);
			b = c;
		}
		else
		{
			//Add the edge back in.
			vertices[trucks[a].origin].neighbor.insert (vertices[trucks[a].origin].neighbor.begin () + trucks[a].order, temp_edge);
			backup[trucks[a].origin].neighbor.insert (backup[trucks[a].origin].neighbor.begin () + trucks[a].order, temp_edge);
		}
	}

	sort (solution.begin (), solution.end ());

	out << min_cost << " " << solution.size () << "\n";

	for (a = 0;a < solution.size ();a++)
		out << solution[a] << "\n";

	out.close ();

	return 0;
}