// Finds the maximum bipartite matching in a bipartite graph in O(NM) with
// Kuhn's algorithm. N: Pair of sizes, for the number of nodes on the left &
// right side of bipartite graph. M: Pairs of indices `(i, j)` indicating an
// edge from `i` on the left side (0-indexed) and `j` on the right side
// (0-indexed). Returns: List of indices of edges in `M` which comprise the max
// bipartite matching.
std::vector<std::size_t> maxMatchBipartiteKuhn(
	std::pair<std::size_t, std::size_t> const &N,
	std::vector<std::pair<std::size_t, std::size_t>> const &M) {
	// Iterate over the side of the graph with fewer nodes.
	bool fromLeft{N.first < N.second};
	std::size_t const &fromN{fromLeft ? N.first : N.second},
		toN{fromLeft ? N.second : N.first};

	// Edge arrays store the other node as well as the edge index in M.
	std::vector<std::vector<std::size_t>> fromM(fromN), toM(toN);

	for (auto const &edge : M) {
		fromM[fromLeft ? edge.first : edge.second].push_back(
			fromLeft ? edge.second : edge.first);
		toM[fromLeft ? edge.second : edge.first].push_back(
			fromLeft ? edge.first : edge.second);
	}

	for (std::size_t i{0}; i < fromN; i++) {
		// Repeatedly find augmenting path from i. An augmenting path is an
		// odd-length path with edges alternating in the matching and not in the
		// matching. The first edge along an augmenting path must not be in the
		// matching.
	}
