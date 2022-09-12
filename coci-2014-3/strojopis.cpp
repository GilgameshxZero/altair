#include <string>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	string s;
	cin >> s;

	int cor[128];
	cor['1'] = 0;cor['Q'] = 0;cor['A'] = 0;cor['Z'] = 0;
	cor['2'] = 1;cor['W'] = 1;cor['S'] = 1;cor['X'] = 1;
	cor['3'] = 2;cor['E'] = 2;cor['D'] = 2;cor['C'] = 2;
	cor['4'] = 3;cor['R'] = 3;cor['F'] = 3;cor['V'] = 3;
	cor['5'] = 3;cor['T'] = 3;cor['G'] = 3;cor['B'] = 3;
	cor['6'] = 4;cor['Y'] = 4;cor['H'] = 4;cor['N'] = 4;
	cor['7'] = 4;cor['U'] = 4;cor['J'] = 4;cor['M'] = 4;
	cor['8'] = 5;cor['I'] = 5;cor['K'] = 5;cor[','] = 5;
	cor['9'] = 6;cor['O'] = 6;cor['L'] = 6;cor['.'] = 6;
	cor['0'] = 7;cor['P'] = 7;cor['['] = 7;cor[']'] = 7;
	cor[';'] = 7;cor['\''] = 7;cor['/'] = 7;cor['-'] = 7;
	cor['='] = 7;

	int cnt[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	for (int a = 0;a < s.length ();a++)
	{
		cnt[cor[s[a]]]++;
	}

	for (int a = 0;a < 8;a++)
		cout << cnt[a] << "\n";

	return 0;
}