#include "directed_graph.h"

DirectedGraph::DirectedGraph(unsigned int vertex_number,unsigned  int edges_number){
	this->edges_number = edges_number;
    this->vertex_number = vertex_number;
}

void DirectedGraph::read_input(){
    for(unsigned int i = 0; i < edges_number; i++){
		std::vector<int> edge;
		int value;
		for(unsigned int j = 0; j < 3; j++){
			std::cin >> value;
			edge.push_back(value);
		}
		this->edges.push_back(edge);
	}
    return;

}

void DirectedGraph::get_st_vertex(){
    std::vector<int> s_candidates, t_candidates;
    
    for(unsigned int i = 0; i < vertex_number; i++){
        t_candidates.push_back(1);
        s_candidates.push_back(1);
    }

    for(unsigned int i = 0; i < edges_number; i++){
		std::vector<int> edge = edges[i];
        t_candidates[edge[0]] = 0; 
        s_candidates[edge[1]] = 0;
    }
    
    for(unsigned int i = 0; i < vertex_number; i++){
        // std::cout << i << " " << t_candidates[i] << "-----";
        // std::cout << i << " " << s_candidates[i] << std::endl;
    }

    for(unsigned int i = 0; i < vertex_number; i++){
        if(t_candidates[i]) this->t_vertex = i;
        if(s_candidates[i]) this->s_vertex = i;
    }

    std::cout << "Vertice de source: " << this->s_vertex <<std::endl;
    std::cout << "Vertice de sink: " << this->t_vertex  << std::endl;
     
}

void DirectedGraph::get_min_cut(std::vector<int> cut_set){
    int cut_value;

    std::vector<int> candidates;
    for(unsigned int i = 0; i < vertex_number; i++){
        candidates.push_back(0);
    }
    
    for(unsigned int i = 0; i < cut_set.size(); i++){
        candidates[cut_set[i]] = 1;
    }

    for(unsigned int i = 0; i < edges_number; i++){
		std::vector<int> edge = edges[i];
        if(candidates[edge[0]]) cut_value+= edge[3]; 
    }

    return;
}
