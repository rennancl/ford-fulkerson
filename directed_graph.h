#include <bits/stdc++.h>

class DirectedGraph{
	private:
		unsigned int vertex_number;
		unsigned int edges_number;
		unsigned int s_vertex;
		unsigned int t_vertex;

	public:
		std::vector<std::vector<int>> edges;
		DirectedGraph(unsigned int, unsigned int);
		void dfs();
		void get_st_vertex(); 
		void read_input();
		void get_min_cut(std::vector<int> cut_set);
};
