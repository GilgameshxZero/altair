#include <fstream>
#include <algorithm>
#include <bitset>
#include <string>
#include <vector>
#include <functional>
#include <set>
#include <map>

using namespace std;
typedef long long ll;

int n, k, p;
ll ans;
map< pair<int, int>, int > rook;
map< int, int > rmap, cmap, rpcnt, cpcnt;
vector<int> rval, cval, rpa, cpa;
vector< pair< pair<int, int>, int > > inq;
vector< pair< pair<int, int>, pair<int, int> > > mq;

void Add (int b, int c, int pow)
{
	static map< int, int >::iterator it;

	it = cpcnt.find (rpa[b]);
	if (it != cpcnt.end ())
		ans -= it->second;
	it = rpcnt.find (cpa[c]);
	if (it != rpcnt.end ())
		ans -= it->second;

	if (rpa[b] == cpa[c])
		ans++;

	it = rpcnt.find (rpa[b]);
	it->second--;
	it = cpcnt.find (cpa[c]);
	it->second--;

	rpa[b] ^= pow;
	cpa[c] ^= pow;

	it = rpcnt.find (rpa[b]);
	if (it == rpcnt.end ())
		rpcnt.insert (make_pair (rpa[b], 1));
	else
		it->second++;

	it = cpcnt.find (cpa[c]);
	if (it == cpcnt.end ())
		cpcnt.insert (make_pair (cpa[c], 1));
	else
		it->second++;

	it = cpcnt.find (rpa[b]);
	if (it != cpcnt.end ())
		ans += it->second;
	it = rpcnt.find (cpa[c]);
	if (it != rpcnt.end ())
		ans += it->second;

	if (rpa[b] == cpa[c])
		ans--;
}

int main () {
	ifstream in ("input.txt");
	ofstream out ("output.txt");

	in >> n >> k >> p;

	for (int a = 0, b, c, d; a < k; a++)
	{
		in >> b >> c >> d;
		inq.push_back (make_pair (make_pair (b, c), d));
		rval.push_back (b);
		cval.push_back (c);
	}

	for (int a = 0, b, c, d, e;a < p;a++)
	{
		in >> b >> c >> d >> e;
		rval.push_back (b);
		cval.push_back (c);
		rval.push_back (d);
		cval.push_back (e);
		mq.push_back (make_pair (make_pair (b, c), make_pair (d, e)));
	}

	sort (rval.begin (), rval.end ());
	sort (cval.begin (), cval.end ());

	rmap.insert (make_pair (rval[0], 0));
	cmap.insert (make_pair (cval[0], 0));

	for (int a = 1; a < rval.size (); a++)
		if (rval[a] != rval[a - 1])
			rmap.insert (make_pair (rval[a], rmap.size ()));
	for (int a = 1; a < cval.size (); a++)
		if (cval[a] != cval[a - 1])
			cmap.insert (make_pair (cval[a], cmap.size ()));

	rpa.resize (rmap.size ());
	cpa.resize (cmap.size ());
	ans = (ll)n * n;
	rpcnt.insert (make_pair (0, n));
	cpcnt.insert (make_pair (0, n));

	for (int a = 0, b, c; a < k; a++)
	{
		b = rmap.find (inq[a].first.first)->second;
		c = cmap.find (inq[a].first.second)->second;
		rook.insert (make_pair (make_pair (b, c), inq[a].second));
		Add (b, c, inq[a].second);
	}

	for (int a = 0, b, c, d, e;a < mq.size ();a++)
	{
		b = mq[a].first.first;
		c = mq[a].first.second;
		d = mq[a].second.first;
		e = mq[a].second.second;
		
		static map< pair<int, int>, int >::iterator it;
		static int rr, rc, pow, rr2, rc2;
		rr = rmap.find (b)->second;
		rc = cmap.find (c)->second;
		rr2 = rmap.find (d)->second;
		rc2 = cmap.find (e)->second;
		it = rook.find (make_pair (rr, rc));
		pow = it->second;
		rook.erase (it);
		rook.insert (make_pair (make_pair (rr2, rc2), pow));

		Add (rr, rc, pow);
		Add (rr2, rc2, pow);

		out << (ll)n * n - ans << '\n';
	}

	in.close ();
	out.close ();

	return 0;
}