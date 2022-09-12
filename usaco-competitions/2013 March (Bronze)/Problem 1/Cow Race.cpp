#include <fstream>

int main ()
{
	std::ifstream in;
	std::ofstream out;
	int n, m, run[2][1001][2], p = 0, q = 0, bessie = 0, elsie = 0, change = 0, lead = -1;

	in.open ("cowrace.in");
	in >> n >> m;

	for (int a = 0;a < n;a++)
		in >> run[0][a][0] >> run[0][a][1];

	for (int a = 0;a < m;a++)
		in >> run[1][a][0] >> run[1][a][1];

	run[0][n][0] = run[1][m][0] = 0;
	run[0][n][1] = run[1][m][1] = 2000;

	while (!(p == n && q == m))
	{
		if (run[0][p][1] < run[1][q][1])
		{
			bessie += (run[0][p][1]) * run[0][p][0];
			elsie += (run[0][p][1]) * run[1][q][0];
			run[1][q][1] -= run[0][p][1];
			p++;

			if (lead == 0)
			{
				if (elsie > bessie)
					change++;
			}
			else if (lead == 1)
			{
				if (elsie < bessie)
					change++;
			}
			
		}
		else if (run[0][p][1] > run[1][q][1])
		{
			bessie += (run[1][q][1]) * run[0][p][0];
			elsie += (run[1][q][1]) * run[1][q][0];
			run[0][p][1] -= run[1][q][1];
			q++;
			
			if (lead == 0)
			{
				if (elsie > bessie)
					change++;
			}
			else if (lead == 1)
			{
				if (elsie < bessie)
					change++;
			}
		}
		else
		{
			bessie += (run[0][p][1]) * run[0][p][0];
			elsie += (run[1][q][1]) * run[1][q][0];
			p++;
			q++;

			if (lead == 0)
			{
				if (elsie > bessie)
					change++;
			}
			else if (lead == 1)
			{
				if (elsie < bessie)
					change++;
			}
		}

		if (bessie > elsie)
			lead = 0;
		else if (bessie < elsie)
			lead = 1;
	}

	out.open ("cowrace.out");
	out << change << "\n";
	out.close ();

	return 0;
}