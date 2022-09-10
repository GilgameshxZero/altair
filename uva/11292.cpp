#include <algorithm>
#include <iostream>

int chead, cknight, diam[20000], height[20000];

int main ()
{
	int cost, j, a;

	//freopen ("input.txt", "r", stdin);
	std::cin >> chead >> cknight;

	while (!(chead == 0 && cknight == 0))
	{
		cost = 0;

		for (a = 0;a < chead;a++)
			std::cin >> diam[a];
		for (a = 0;a < cknight;a++)
			std::cin >> height[a];

		std::sort (height, height + cknight);
		std::sort (diam, diam + chead);

		j = 0;
		for (a = 0;a < chead;a++)
		{
			for (;height[j] < diam[a] && j < cknight;j++);

			if (j == cknight)
			{
				std::cout << "Loowater is doomed!\n";
				break;
			}

			cost += height[j++];
		}

		if (a == chead)
			std::cout << cost << "\n";

		std::cin >> chead >> cknight;
	}

	return 0;
}