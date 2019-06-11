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
    for(unsigned int i = 0; i < vertex_number; i++){
        for(unsigned int j = 0; j < vertex_number; j++){
            std::cout << this->graph_[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return;
}

std::vector<std::vector<unsigned int>> Graph::get_neighbors(unsigned int vertex){
    std::vector<std::vector<unsigned int>> neighbors;
    for(unsigned int j = 0; j < vertex_number; j++){
        if(this->graph_[vertex][j] > 0){
            std::vector<unsigned int> temp_edge;
            temp_edge.push_back(j);
            temp_edge.push_back(this->graph_[vertex][j]);
            neighbors.push_back(temp_edge);
        }
    }
    return neighbors;
}

std::vector<std::vector<unsigned int>> Graph::dfs(){
    std::vector<bool> visited;
    bool t_visited = false;

    std::vector<std::vector<unsigned int>> path;


    for(unsigned int i = 0; i < vertex_number; i++){
        visited.push_back(false);
    }
    std::stack<int> vertex_stack;
    vertex_stack.push(s_vertex);

    while(!vertex_stack.empty()){
        int vertex = vertex_stack.top(); 
        vertex_stack.pop();
        if(!visited[vertex]){
            visited[vertex] = true;
            std::vector<std::vector<unsigned int>> neighbors = this->get_neighbors(vertex);
            for(unsigned int j = 0; j < neighbors.size(); j++){
                vertex_stack.push(neighbors[j][0]);
                

                //here is not the place to put this function
                std::vector<unsigned int> temp_edge;
                temp_edge.push_back(vertex);
                temp_edge.push_back(neighbors[j][0]);
                temp_edge.push_back(neighbors[j][1]);
                path.push_back(temp_edge);
                
                if(neighbors[j][0] == t_vertex){
                    t_visited = true;
                    break;
                }
            }
        }
    }

    //get path from edges collected
    
    std::vector<std::vector<unsigned int>> path_;
    if(!t_visited){
        return path_;
    }

    unsigned int target = t_vertex;
    for(unsigned int i = 0; ; i++){
        
        if(i == path.size()) i = 0;
        if(path[i][1] == target){
            path_.push_back(path[i]);
            target = path[i][0];
            if(path[i][0] == s_vertex) break;
        }
    }
    return path_;
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

unsigned int Graph::update_graph(std::vector<std::vector<unsigned int>> path){
    unsigned int a;
    return a;
}

void Graph::ford_fulkerson(){
    std::cout << "Vertice de source: " << this->s_vertex <<std::endl;
    std::cout << "Vertice de sink: " << this->t_vertex  << std::endl;
    unsigned int flow = 0; 
    unsigned int min_path_flow = MAXINT;

    while(1){
        std::vector<std::vector<unsigned int>> path = dfs();
        if(path.empty()) break;
    	min_path_flow = MAXINT;

        for(unsigned int i = 0; i < path.size(); i++){
            if(path[i][2] < min_path_flow) min_path_flow = path[i][2];
        }
        for(unsigned int i = 0; i < path.size(); i++){
            this->graph_[path[i][0]][path[i][1]] -= min_path_flow;
        }
        flow += min_path_flow;

    }
    std::cout << flow << std::endl;
    return;

    //update_graph
    
    
    // for(unsigned int i = 0; i < path.size(); i++){
    //     for(unsigned int j = 0; j < 3; j++){
    //         std::cout << path[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    //get how much we can increase the flow from the path info
}