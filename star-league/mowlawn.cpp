//Solution by Yang Yan
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

struct QElem
{
	ll val, maxv;
};

ll eff[100000], dp[100000], pre[100000];

void Push (vector<QElem> &top, vector<QElem> &bot, ll val)
{
	top.push_back (QElem ());
	top.back ().val = val;
	if (top.size () > 1)
		top.back ().maxv = max (val, top[top.size () - 2].maxv);
	else
		top.back ().maxv = val;
}

void Pop (vector<QElem> &top, vector<QElem> &bot)
{
	if (top.empty () && bot.empty ())
		return;
	else if (!bot.empty ())
		bot.pop_back ();
	else
	{
		while (!top.empty ())
		{
			bot.push_back (QElem ());
			bot.back ().val = top.back ().val;
			if (bot.size () > 1)
				bot.back ().maxv = max (top.back ().val, bot[bot.size () - 2].maxv);
			else
				bot.back ().maxv = top.back ().val;
			top.pop_back ();
		}
		bot.pop_back ();
	}
}

ll GetMax (vector<QElem> &top, vector<QElem> &bot)
{
	if (top.empty () && bot.empty ())
		return (ll)1e15;
	else if (top.empty ())
		return bot.back ().maxv;
	else if (bot.empty ())
		return top.back ().maxv;
	else
		return max (top.back ().maxv, bot.back ().maxv);
}

int main ()
{
	freopen ("mowlawn.in", "r", stdin); freopen ("mowlawn.out", "w", stdout);

	int N, K;
	cin >> N >> K;
	
	for (int a = 0;a < N;a++)
		cin >> eff[a];

	pre[0] = eff[0];
	for (int a = 1;a < N;a++)
		pre[a] = eff[a] + pre[a - 1];

	dp[0] = eff[0];
	
	vector<QElem> top, bot;
	if (K == 1)
		Push (top, bot, -pre[0]);
	else
		Push (top, bot, 0);
	for (int a = 1;a < N;a++)
	{
		Push (top, bot, dp[a - 1] - pre[a]);
		if (a > K)
			Pop (top, bot);
		dp[a] = pre[a] + GetMax (top, bot);
	}

	cout << dp[N - 1] << "\n";

	return 0;
}