#include <bits/stdc++.h>
#define MAXINT 10000000
class Graph{
	private:
		unsigned int vertex_number;
		unsigned int edges_number;
		unsigned int s_vertex;
		unsigned int t_vertex;
	    	unsigned int flow; 
		std::vector<std::vector<int>> edges;
		int **graph_;
		int **graph_aux;

		std::vector<unsigned int> cut;

	public:
		Graph(unsigned int, unsigned int);
		void read_input();
		void print_solution();
		void print_graph();
		void get_solution();
		void create_graph();
		unsigned int ford_fulkerson();
		unsigned int update_graph(std::vector<std::vector<unsigned int>> path);
		std::vector<unsigned int> get_cut(std::vector<std::vector<unsigned int>> path);
		std::vector<std::vector<unsigned int>> dfs();
		std::vector<std::vector<unsigned int>> get_path(std::vector<std::vector<unsigned int>> path);

};
