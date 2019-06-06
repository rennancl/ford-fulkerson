#include "directed_graph.h"

int main(){
	unsigned int vertex_number;
    unsigned int edges_number;
    std::cin >> vertex_number;
    std::cin >> edges_number;
	
	DirectedGraph graph(vertex_number, edges_number);
	graph.read_input();
	graph.get_st_vertex();


	// for(unsigned int i = 0; i < edges_number; i++){
	// 	std::vector<double> edge = graph.edges[i];
	// 	for(unsigned int j = 0; j < 3; j++){
	// 		std::cout << edge[j] << " ";
	// 	}
	// 	std::cout << std::endl;
	// }

	return 0;
}
