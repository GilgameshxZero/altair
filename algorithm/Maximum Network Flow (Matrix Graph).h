//p_edge_adj is the adjacency chart for the vertices, and p_edge_cap is the edge capacity of flows in the graph. vstart is the start node, vend is the end node, and cvert is the number of vertices. This function can operate on directed graphs, but only with a maximum of two flows between every pair of vertices, one in each direction. It is very memory and run-time efficient.
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