
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

//#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_utility.hpp>


using namespace boost;

typedef adjacency_list<> Graph;

enum {A, B, C, D, E, N};
const int num_vertice = N;
const char* name = "ABCDE";

typedef std::pair<int, int> Edge;

std::vector<Edge> edgev = {
	Edge(A, B), Edge(A, D), Edge(C, A), Edge(D, C), Edge(C, E), Edge(B, D), Edge(D, E)
};

int main()
{
	Graph g(edgev.begin(), edgev.end(), N);

	print_graph(g, name);

	return 0;
}
