//These two structures represent a network graph. They are used with the MaxFlow function.
struct NetworkVertice;
struct NetworkEdge;

struct NetworkEdge
{
	NetworkVertice *destination;
	unsigned int edge_cap;
};

struct NetworkVertice
{
	vector<NetworkEdge> neighbor;
};

//unsigned int MaxFlow (const NetworkVertice *net_vert, const unsigned int vstart, const unsigned int vend, const unsigned int cvert); determines the maximum flow of a graph from the vertice 'start' to the 'end'. This graph can be directed. 'flow_mat' will indicate a flow from [a] to [b]. 'cap_mat' will indicate the capacity of the flow from [a] to [b]. Make sure none of the passed parameters are equal to UINT_MAX as a safety precaution, because UINT_MAX is used as a special value in the function. This function requires the structures NetworkEdge and NetworkVertice to represent a network graph. Also, make sure you have a backup of NetworkVertice *net_vert, because this function will edit the variable.
unsigned int MaxFlow (NetworkVertice *net_vert, const unsigned int vstart, const unsigned int vend, const unsigned int cvert)
{
	NetworkEdge temp_edge;
	bool *vvisited;
	unsigned int current_vert, max_vert, max_cap, total_flow, *path_cap, *vparent;
	unsigned int a, b, c, d, e;

	//Initialize arrays for later use in a modified Dijkastra's algorithm.
	total_flow = 0;
	vvisited = new bool[cvert];
	vparent = new unsigned int[cvert];
	path_cap = new unsigned int [cvert];

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
					if ((path_cap[current_vert] == UINT_MAX) /*A special value. This probably means that current_vert = vstart.*/ && (d > path_cap[e] || path_cap[e] == UINT_MAX))
					{
						path_cap[e] = net_vert[current_vert].neighbor.at (b).edge_cap;
						vparent[e] = current_vert;
					}
					else if ((path_cap[current_vert] > d) && (d > path_cap[e] || path_cap[e] == UINT_MAX))
					{
						path_cap[e] = net_vert[current_vert].neighbor.at (b).edge_cap;
						vparent[e] = current_vert;
					}
					else if ((path_cap[current_vert] <= d) && (path_cap[current_vert] > path_cap[e] || path_cap[e] == UINT_MAX))
					{
						path_cap[e] = path_cap[current_vert];
						vparent[e] = current_vert;
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