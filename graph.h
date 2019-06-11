#include <bits/stdc++.h>
#define MAXINT 10000000
class Graph{
	private:
		unsigned int vertex_number;
		unsigned int edges_number;
		unsigned int s_vertex;
		unsigned int t_vertex;

	public:
		std::vector<std::vector<int>> edges;
		std::vector<std::vector<int>> graph_;

		Graph(unsigned int, unsigned int);
		std::vector<std::vector<unsigned int>> dfs();
		void get_st_vertex(); 
		void read_input();
		void ford_fulkerson();
		void print_graph();
		void create_graph();
		void get_min_cut(std::vector<int> cut_set);
		unsigned int update_graph(std::vector<std::vector<unsigned int>> path);
		std::vector<std::vector<unsigned int>> get_neighbors(unsigned int);
};
