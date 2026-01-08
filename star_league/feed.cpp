//Solution by Yang Yan
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;

struct Shop
{
	ll x, mfeed, cost;
};

struct SWParam
{
	ll cost, lmin;
	ll id, lid;

	SWParam (ll a, ll b)
	{
		cost = a;
		id = b;
	}

	bool operator< (const SWParam& other) const
	{
		return cost > other.cost;
	}
};

bool CompX (const Shop& a, const Shop& b)
{
	return a.x < b.x;
}

ll GetMinCost (vector<SWParam>& top, vector<SWParam>& bot)
{
	if (top.empty ())
	{
		if (bot.empty ())
			return (ll)1e15;
		else
			return bot.back ().lmin;
	}
	else
	{
		if (bot.empty ())
			return top.back ().lmin;
		else
			return min (top.back ().lmin, bot.back ().lmin);
	}
}

ll GetMinID (vector<SWParam>& top, vector<SWParam>& bot)
{
	if (top.empty ())
	{
		if (bot.empty ())
			return (ll)1e15;
		else
			return bot.back ().lid;
	}
	else
	{
		if (bot.empty ())
			return top.back ().lid;
		else
		{
			if (top.back ().lmin > bot.back ().lmin)
				return bot.back ().lid;
			else
				return top.back ().lid;
		}
	}
}

void Push (vector<SWParam>& top, vector<SWParam>& bot, ll cost, ll id)
{
	SWParam p (cost, id);
	if (!top.empty ())
		p.lmin = min (cost, top.back ().lmin);
	else
		p.lmin = cost;
	if (p.lmin == cost)
		p.lid = id;
	else
		p.lid = top.back ().lid;
	top.push_back (p);
}

void Pop (vector<SWParam>& top, vector<SWParam>& bot)
{
	if (!bot.empty ())
		bot.pop_back ();
	else
	{
		SWParam p (0, 0);
		while (!top.empty ())
		{
			p.cost = top.back ().cost;
			p.id = top.back ().id;
			if (bot.empty ())
				p.lmin = p.cost;
			else
				p.lmin = min (p.cost, bot.back ().lmin);
			if (p.lmin == p.cost)
				p.lid = p.id;
			else
				p.lid = bot.back ().lid;
			bot.push_back (p);
			top.pop_back ();
		}
		bot.pop_back ();
	}
}

Shop stops[500];
ll dp[2][10001];

int main ()
{
	ios_base::sync_with_stdio (false); freopen ("feed.in", "r", stdin); freopen ("feed.out", "w", stdout);

	ll K, E, N;
	cin >> K >> E >> N;

	for (int a = 0;a < N;a++)
		cin >> stops[a].x >> stops[a].mfeed >> stops[a].cost;

	sort (stops, stops + N, CompX);

	for (int a = 0;a <= K;a++)
		dp[0][a] = dp[1][a] = (ll)1e15;
	for (int a = 0, b = min (K, stops[0].mfeed);a <= b;a++)
		dp[0][a] = (ll)a * stops[0].cost;

	vector<SWParam> top, bot;
	ll z, c;
	for (int a = 1, x, y, b;a < N;a++)
	{
		x = a & 1, y = x ^ 1;
		z = stops[a].x - stops[a - 1].x;
		top.clear ();
		bot.clear ();
		c = -stops[a].mfeed;
		for (b = 0;b <= K;b++, c++)
		{
			//add ID = b
			Push (top, bot, z * b * b + dp[y][b] - stops[a].cost * b, b);

			//get smallest cost that has valid ID
			while (GetMinID (top, bot) < c)
				Pop (top, bot);
			dp[x][b] = stops[a].cost * b + GetMinCost (top, bot);
			if (dp[x][b] >= (ll)1e15)
				break;
		}
	}

	cout << dp[(N - 1) & 1][K] + K * K * (E - stops[N - 1].x) << "\n";

	return 0;
}