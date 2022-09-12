#include <fstream>

char breed[1000000];

int main ()
{
	std::ifstream in;
	std::ofstream out;
	int ccow, crowded, id[50000], ans = -1;

	in.open ("proximity.in");
	in >> ccow >> crowded;

	for (int a = 0;a < ccow;a++)
		in >> id[a];

	in.close ();

	//Initialize breed[].
	for (int a = 0;a <= crowded;a++)
		breed[id[a] - 1]++;
	
	//Check if any breed > 1.
	for (int a = 0;a < 1000000;a++)
	{
		if (breed[a] > 1)
		{
			if (a > ans)
				ans = a + 1;
		}
	}

	for (int a = crowded + 1;a < ccow;a++)
	{
		breed[id[a - crowded - 1] - 1]--;
		breed[id[a] - 1]++;

		if (breed[id[a] - 1] > 1)
			if (id[a] > ans)
				ans = id[a];
	}

	out.open ("proximity.out");
	out << ans << "\n";
	out.close ();
}