#include <iostream>
#include <string>
#include <bitset>
using namespace std;

int node[65536], size, ind[131072];

void UpHeap (int x)
{
	//comp with par
	while (x != 1 && node[x / 2] > node[x])
	{
		swap (ind[node[x / 2]], ind[node[x]]);
		swap (node[x / 2], node[x]);
		x = x / 2;
	}
}

void DownHeap (int x)
{
	while (true)
	{
		if (x * 2 + 1 <= size)
		{
			if (node[x * 2 + 1] < node[x * 2] && node[x] > node[x * 2 + 1])
			{
				swap (ind[node[x * 2 + 1]], ind[node[x]]);
				swap (node[x * 2 + 1], node[x]);
				x = x * 2 + 1;
			}
			else if (node[x * 2 + 1] > node[x * 2] && node[x] > node[x * 2])
			{
				swap (ind[node[x * 2]], ind[node[x]]);
				swap (node[x * 2], node[x]);
				x = x * 2;
			}
		}
		else if (x * 2 == size && node[x * 2] < node[x])
		{
			swap (ind[node[x * 2]], ind[node[x]]);
			swap (node[x * 2], node[x]);
			x *= 2;
		}
		else
			break;
	}
}

int main ()
{
	cout << "(Min)Heap\nRain Corporation - Yang Yan\n013\n\n";
	
	string comm = "";
	memset (node, -1, sizeof (node));
	memset (ind, -1, sizeof (ind));
	size = 0;

	while (comm != "exit")
	{
		cout << "Enter a command (add x, del x, mod x y, size, view, top, exit): ";
		cin >> comm;

		if (comm == "exit")
			return 0;
		else if (comm == "add")
		{
			cin >> node[++size];
			if (ind[node[size]] != -1)
			{
				node[size--] = -1;
				cout << "invalid\n";
				continue;
			}
			ind[node[size]] = size;
			UpHeap (size);
		}
		else if (comm == "del")
		{
			int x;
			cin >> x;
			x = ind[x];

			if (x == -1)
			{
				cout << "invalid\n";
				continue;
			}
			
			if (size > 1)
			{
				//swap our way up to root
				while (x != 1)
				{
					swap (ind[node[x]], ind[node[x / 2]]);
					swap (node[x], node[x / 2]);
					x /= 2;
				}

				ind[node[1]] = -1;
				node[1] = node[size];
				ind[node[1]] = 1;
				node[size--] = -1;
				DownHeap (1);
			}
			else //if size == 1
			{
				ind[node[1]] = -1;
				node[1] = -1;
				size--;
			}
		}
		else if (comm == "mod")
		{
			int x, y;
			cin >> x >> y;
			x = ind[x];

			if (x == -1 || ind[y] != -1)
			{
				cout << "invalid\n";
				continue;
			}

			ind[node[x]] = -1;
			ind[y] = x;

			if (node[x] < y)
			{
				node[x] = y;
				DownHeap (x);
			}
			else
			{
				node[x] = y;
				UpHeap (x);
			}
		}
		else if (comm == "view")
		{
			for (int a = 1;a <= size;a++)
				cout << node[a] << "\t";
			cout << "\n";
		}
		else if (comm == "size")
			cout << size << "\n";
		else if (comm == "top")
		{
			if (size == 0)
			{
				cout << "invalid\n";
				continue;
			}
			cout << node[1] << "\n";
		}
	}
}