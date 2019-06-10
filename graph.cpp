#include "graph.h"

Graph::Graph(unsigned int vertex_number,unsigned  int edges_number){
	this->edges_number = edges_number;
    this->vertex_number = vertex_number;
}

void Graph::read_input(){
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

void Graph::create_graph(){
    for(unsigned int i = 0; i < vertex_number; i++){
        std::vector<std::vector<int>> edge;
        this->graph.push_back(edge);
    }
    
    for(unsigned int i = 0; i < this->edges.size(); i++){
        std::vector<int> edge = this->edges[i];
        std::vector<int> temp_edge;
        int weight = edge[2];

        temp_edge.push_back(edge[1]);
        temp_edge.push_back(weight);
        this->graph[edge[0]].push_back(temp_edge);


        //adicionar essa parte considera que o grafo não é direcionado, ao comentar o grafo se torna direcionado
        // temp_edge[0] = edge[0];
        // temp_edge[1] = weight;
        // this->graph[edge[1]].push_back(temp_edge);
    }
    
    for(unsigned int i = 0; i < vertex_number; i++){
        std::vector<int> neighbors;
        for(unsigned int j = 0; j < vertex_number; j++){
            neighbors.push_back(0);
        }
        this->graph_.push_back(neighbors);
    }

    for(unsigned int i = 0; i < this->edges.size(); i++){
        std::vector<int> edge = this->edges[i];
        this->graph_[edge[0]][edge[1]] = edge[2];
    }
    return;
}

void Graph::print_graph(){
    for(unsigned int i = 0; i < graph.size(); i++){
        std::cout << "Vizinhos de " << i << ": ";
        std::vector<std::vector<int>> neighbors = this->graph[i];
        for(unsigned int j = 0; j < neighbors.size(); j++){
            std::cout << neighbors[j][0] << " ";
        }
        std::cout << std::endl;
    }
    return;

    for(unsigned int i = 0; i < vertex_number; i++){
        for(unsigned int j = 0; j < vertex_number; j++){
            std::cout << this->graph_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void Graph::dfs(){
    std::vector<bool> visited;
    for(unsigned int i = 0; i < vertex_number; i++){
        visited.push_back(false);
    }
    std::stack<int> vertex_stack;
    vertex_stack.push(0);

    while(!vertex_stack.empty()){
        int vertex = vertex_stack.top(); 
        vertex_stack.pop();
        if(!visited[vertex]){
            visited[vertex] = true;
            std::vector<std::vector<int>> neighbors = this->graph[vertex];
            for(unsigned int j = 0; j < neighbors.size(); j++){
                vertex_stack.push(neighbors[j][0]);
            }
        }
    }

    for(unsigned int i = 0; i < vertex_number; i++){
        std::cout << visited[i] << std::endl;
    }
    return;
}

void Graph::get_st_vertex(){
    //essa função será responsável também por realizar a futura modelagem do problema


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
     
}

void Graph::get_min_cut(std::vector<int> cut_set){
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

void Graph::ford_fulkerson(){
    std::cout << "Vertice de source: " << this->s_vertex <<std::endl;
    std::cout << "Vertice de sink: " << this->t_vertex  << std::endl;
}