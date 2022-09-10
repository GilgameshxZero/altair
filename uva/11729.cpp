#include <algorithm>
#include <iostream>

int main ()
{
	std::pair<int, int> j[1000];
	int cs, ans, pre[1000];

	//freopen ("Input.txt", "r", stdin);

	std::cin >> cs;

	for (int a = 0;cs != 0;a++)
	{
		for (int b = 0;b < cs;b++)
			std::cin >> j[b].second >> j[b].first;
		
		std::sort (j, j + cs);
		ans = j[cs - 1].first + j[cs - 1].second;
		pre[cs - 1] = j[cs - 1].second;

		for (int b = cs - 2;b >= 0;b--)
		{
			pre[b] = pre[b + 1] + j[b].second;
			ans = std::max (ans, pre[b] + j[b].first);
		}

		std::cout << "Case " << a + 1  << ": " << ans << "\n";
		std::cin >> cs;
	}

	return 0;
}