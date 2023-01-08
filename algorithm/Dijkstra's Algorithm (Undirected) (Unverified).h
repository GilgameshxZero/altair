#include <climits>

//void DijkstraAlgorithmUndirected (const bool **neighbor, unsigned int **distance, const unsigned int source, const unsigned int cvertices); calculates the distance from the 'source' vertice to every other vertice on an undirected graph. It requires an adjacency matrix 'neighbor', and a distance matrix 'distance'. The distance from that 'source' to every other vertice will be updated in the 'distance' matrix. Make sure that the distance between non-neighbors is INT_MAX.
void DijkstraAlgorithmUndirected (bool **neighbor, unsigned int **distance, const unsigned int source, const unsigned int cvertices)
{
	bool *visited;
	unsigned int current_vert, small_dist, small_vert;
	unsigned int a, b;

	//Initialization.
	visited = new bool[cvertices];
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
			//If the pasture is a neighbor of the curent pasture and has not been visited yet.
			if (neighbor[current_vert][b] == true && visited[b] == false)
			{
				//Check if the pasture has a shorter sum (distance to the current + the distance of the current to the source) than already listed.
				if (static_cast<unsigned long long>(distance[current_vert][b]) + static_cast<unsigned long long>(distance[source][current_vert]) < static_cast<unsigned long long>(distance[source][b]))
					distance[source][b] = distance[b][source] = distance[current_vert][b] + distance[source][current_vert];
			}
		}

		//Pick the closest neighbor not visited, and set it as the next current pasture
        small_dist = INT_MAX;

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

	delete[] visited;
}