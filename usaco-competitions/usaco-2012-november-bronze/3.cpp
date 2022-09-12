#include <fstream>
#include <string>

char grid[5][5];
bool visited[5][5];

void DFS (int gsize, int start_x, int start_y, std::string path, int *lg_len)
{
	bool flag;
	int a;

	path += grid[start_x][start_y];
	visited[start_x][start_y] = true;

	//Check if the path is a balanced one, and record if true and longer.
	if (path.length () % 2 == 0)
	{
		flag = false;

		for (a = 0;a < path.length () / 2;a++)
			if (path[a] == ')')
				flag = true;

		for (a = path.length () / 2;a < path.length ();a++)
			if (path[a] == '(')
				flag = true;

		if (flag == false)
			if ((*lg_len) < path.length ())
				(*lg_len) = path.length ();
	}

	//Start DFS on its neighbors
	if (start_x > 0 && visited[start_x - 1][start_y] == false)
		DFS (gsize, start_x - 1, start_y, path, lg_len);
	if (start_y > 0 && visited[start_x][start_y - 1] == false)
		DFS (gsize, start_x, start_y - 1, path, lg_len);
	if (start_x < gsize - 1 && visited[start_x + 1][start_y] == false)
		DFS (gsize, start_x + 1, start_y, path, lg_len);
	if (start_y < gsize - 1 && visited[start_x][start_y + 1] == false)
		DFS (gsize, start_x, start_y + 1, path, lg_len);

	visited[start_x][start_y] = false;
}

int main ()
{
	std::ifstream in ("hshoe.in");
	std::ofstream out ("hshoe.out");
	int gsize, lg_len = 0;
	int a, b;

	for (a = 0;a < 5;a++)
		for (b = 0;b < 5;b++)
			visited[a][b] = false;

	in >> gsize;

	for (a = 0;a < gsize;a++)
	{
		//Discard the newline.
		in.get ();

		for (b = 0;b < gsize;b++)
			grid[a][b] = in.get ();
	}

	in.close ();

	//Start a DFS.
	DFS (gsize, 0, 0, "", &lg_len);

	out << lg_len << "\n";
	out.close ();

	return 0;
}