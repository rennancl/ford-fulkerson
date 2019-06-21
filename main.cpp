#include "graph.h"

int main(){
	unsigned int vertex_number;
	unsigned int edges_number;
	std::cin >> vertex_number;
	std::cin >> edges_number;
	
	Graph graph(vertex_number, edges_number);
	graph.read_input();
	graph.create_graph();
// graph.print_graph();
// graph.get_st_vertex();
	graph.get_solution();
	graph.print_solution();

	return 0;
}
