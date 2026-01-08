#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;

void TarjansSCCSub(int cur, vector<vector<int>> &edge, vector<bool> &instack, vector<int> &lowlink, vector<int> &index, stack<int> &s, int &cindex, int &cscc) {
	lowlink[cur] = index[cur] = cindex++; //first time visit
	s.push(cur); //so we can find sccs effectively
	instack[cur] = true;

	//see if any children have links backward. if unvisited, visit. if on the current stack, then eval lowlink; if not, then ignore, because it belongs to another scc.
	for (int a = 0; a < edge[cur].size(); a++) {
		if (index[edge[cur][a]] == -1) {
			TarjansSCCSub(edge[cur][a], edge, instack, lowlink, index, s, cindex, cscc);
			lowlink[cur] = min(lowlink[cur], lowlink[edge[cur][a]]);
		} else if (instack[edge[cur][a]])
			lowlink[cur] = min(lowlink[cur], lowlink[edge[cur][a]]);
	}

	if (lowlink[cur] == index[cur]) //we cant go farther back, so this is the conclusion of an scc. pop off stack until we reach x to get scc
	{
		while (s.top() != cur) {
			instack[s.top()] = false;
			s.pop();
		}
		s.pop();
		instack[cur] = false;
		cscc++;
	}
}

//returns the number of SCCs
int TarjansSCC(vector<vector<int>> &edge, vector<int> &scc) {
	vector<bool> instack(edge.size(), false);
	vector<int> index(edge.size(), -1);
	stack<int> s;
	int cindex = 0,
		cscc = 0;

	scc.resize(0);
	scc.resize(edge.size(), 1000000000);
	for (int a = 0; a < edge.size(); a++)
		if (index[a] == -1)
			TarjansSCCSub(a, edge, instack, scc, index, s, cindex, cscc);

	return cscc;
}

int main() {
	ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen("input0.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int T;
	cin >> T;
	
	for (int a = 0; a < T; a++) {
		int M;
		cin >> M;

		vector<pair<int, int>> req(M);
		vector<vector<int>> from(M);
		for (int b = 0; b < M; b++) {
			cin >> req[b].first >> req[b].second;
			req[b].first--;
			req[b].second--;
			from[req[b].first].push_back(b);
			from[req[b].second].push_back(b);
		}

		vector<int> supply(M);
		for (int b = 0; b < M; b++)
			cin >> supply[b];

		int ans = supply[0];
		supply[0] = 0;

		//breakdown
		vector<int> formula(M, 0);
		int servings = 1000000000;
		formula[req[0].first] = formula[req[0].second] = 1;

		vector<vector<int>> edge(M);

		vector<bool> exhaust(M, false),
			dead(M, false);

		vector<int> scc, sccSize;
		int cscc;

		for (int b = 0; b < M; b++) {
			if (supply[b] == 0 && !exhaust[b]) {
				exhaust[b] = true;
				for (int c = 0; c < from[b].size(); c++) {
					edge[b].push_back(from[b][c]);
				}

				if (req[b].first == b || req[b].second == b)
					dead[b] = true;
			}
		}

		//get new dead ingredients//scc size > 1
		TarjansSCC(edge, scc);
		sccSize = vector<int>(M, 0);
		for (int b = 0; b < scc.size(); b++)
			sccSize[scc[b]]++;
		for (int b = 0; b < scc.size(); b++)
			if (sccSize[scc[b]] > 1)
				dead[b] = true;

		while (true) {
			servings = 1000000000;
			for (int b = 0; b < M; b++) {
				if (formula[b] == 0)
					continue;
				servings = min(servings, supply[b] / formula[b]);
			}
			ans += servings;

			if (servings == 0)
				break;

			for (int b = 0; b < M; b++) {
				supply[b] -= servings * formula[b];
				if (supply[b] == 0 && !exhaust[b]) {
					exhaust[b] = true;
					for (int c = 0; c < from[b].size(); c++) {
						edge[b].push_back(from[b][c]);
					}

					if (req[b].first == b || req[b].second == b)
						dead[b] = true;
				}
			}

			//get new dead ingredients//scc size > 1
			TarjansSCC(edge, scc);
			sccSize = vector<int>(M, 0);
			for (int b = 0; b < scc.size(); b++)
				sccSize[scc[b]]++;
			for (int b = 0; b < scc.size(); b++)
				if (sccSize[scc[b]] > 1)
					dead[b] = true;

			//breakdown exhaused ingredients; quit if dead ingredient
			queue<int> todo;
			bool done = false;
			for (int b = 0; b < formula.size(); b++)
				if (formula[b] > 0 && (exhaust[b] || dead[b]))
					todo.push(b);
			while (!todo.empty()) {
				int b = todo.front();
				todo.pop();

				if (formula[b] == 0)
					continue;

				if (dead[b]) {
					done = true;
					break;
				}

				formula[req[b].first] += formula[b];
				formula[req[b].second] += formula[b];
				formula[b] = 0;
				if (exhaust[req[b].first] || dead[req[b].first])
					todo.push(req[b].first);
				if (exhaust[req[b].second] || dead[req[b].second])
					todo.push(req[b].second);
			}

			if (done)
				break;
		}

		cout << "Case #" << a + 1 << ": " << ans << "\n";
	}

	return 0;
}