#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

struct DPParam
{
	ll lowcost, //lowest cost for subtree
		othercost; //lowest cost if not using `invalid`
	int invalid; //value for lowcost
};

vector<DPParam> dp;
vector< vector<int> > ch;
vector<int> par;
vector<ll> trans (200003); //transition states for value assigned to cur and children values
ll norm, cost;
ll mncost = 1e15, mnsec = 1e15;
int mnind;

void Solve (int cur)
{
	if (ch[cur].size () == 0)
	{
		dp[cur].lowcost = 1;
		dp[cur].invalid = 1;
		dp[cur].othercost = 2;
		return;
	}

	norm = 0;
	for (int a = 0;a < 3 + ch[cur].size ();a++)
		trans[a] = 0;
	for (int a = 0;a < ch[cur].size ();a++)
	{
		Solve (ch[cur][a]);
		norm += dp[ch[cur][a]].lowcost;
		trans[dp[ch[cur][a]].invalid] += (-dp[ch[cur][a]].lowcost + dp[ch[cur][a]].othercost);
	}

	//keep track of min cost, the min cost's index, and the second min cost
	mncost = mnsec = 1e15;
	for (int a = 1;a < 3 + ch[cur].size ();a++)
	{
		cost = a + norm + trans[a];
		
		if (cost < mnsec)
		{
			mnsec = cost;
			if (mnsec < mncost)
			{
				mnind = a;
				swap (mnsec, mncost);
			}
		}
	}

	dp[cur].lowcost = mncost;
	dp[cur].invalid = mnind;
	dp[cur].othercost = mnsec;
}

int main ()
{
	//freopen ("in.txt", "r", stdin);
	//freopen ("out.txt", "w", stdout);

	int T;
	cin >> T;

	dp.reserve (200000);
	ch.reserve (200000);
	par.reserve (200000);

	for (int a = 1;a <= T;a++)
	{
		int N;
		cin >> N;

		dp.clear ();
		dp.resize (N);
		ch.clear ();
		ch.resize (N);
		par.resize (N);

		int t;
		cin >> t;
		for (int b = 1;b < N;b++)
		{
			cin >> t;
			t--;
			par[b] = t;
			ch[t].push_back (b);
		}

		par[0] = -1;
		Solve (0);
		cout << "Case #" << a << ": " << dp[0].lowcost << "\n";
	}

	return 0;
}