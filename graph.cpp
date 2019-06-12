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
    std::vector<unsigned int> parent;

    std::vector<std::vector<unsigned int>> path;
    std::stack<int> vertex_stack;
    vertex_stack.push(s_vertex);

    for(unsigned int i = 0; i < vertex_number; i++){
        visited.push_back(false);
        parent.push_back(-1);
    }
    parent[s_vertex] = s_vertex;

    while(!vertex_stack.empty()){
        int vertex = vertex_stack.top(); 
        vertex_stack.pop();
        if(!visited[vertex]){
            visited[vertex] = true;
            std::vector<std::vector<unsigned int>> neighbors = this->get_neighbors(vertex);
            for(unsigned int j = 0; j < neighbors.size(); j++){
                vertex_stack.push(neighbors[j][0]);
                std::vector<unsigned int> temp_edge;
                temp_edge.push_back(vertex);
                temp_edge.push_back(neighbors[j][0]);
                temp_edge.push_back(neighbors[j][1]);
                path.push_back(temp_edge);

                parent[neighbors[j][0]] = vertex;

                //this modification does not make everything perfect, but it does solve the problem in some cases
                //this problem can be solved by adding the parent vector
                if(neighbors[j][0] == t_vertex) return path;
            }
        }
    }
    return path;
}
std::vector<std::vector<unsigned int>> Graph::get_path(std::vector<std::vector<unsigned int>> path){
    
    //theres a problem with this function, its not fiding the path in a good way
    //i need to solve this, maybe using BFS instead of DFS
    std::vector<std::vector<unsigned int>> path_;

    bool t_visited = false;
    for(unsigned int i = 0;  i < path.size(); i++){
        if(path[i][1] == t_vertex){
            t_visited = true;
            break;
        }
    }


    if(!t_visited){
        return path_;
    }

    for(unsigned int i = 0;  i < path.size(); i++){
        std::cout << path[i][0] << "-" << path[i][1] << std::endl;
    }
    std::cout << "-------------" << std::endl;
    unsigned int target = t_vertex;
    
    std::vector<unsigned int> parent;
    for(unsigned int i = 0; i < vertex_number; i++){
        parent.push_back(-1);
    }
    for(unsigned int i = path.size(); i > 0; i--){
        parent[path[i-1][1]] = path[i-1][0];
    }
    parent[s_vertex] = s_vertex;

    for(unsigned int i = 0; i < vertex_number; i++){
        std::cout << parent[i] << std::endl;
    }
    std::cout << "Source" << s_vertex << std::endl;

    
    
    
    for(unsigned int i = 0; ; i++){
    //problema está aqui
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
        if(t_candidates[i]) this->t_vertex = i;
        if(s_candidates[i]) this->s_vertex = i;
    }
     
}

std::vector<unsigned int> Graph::get_cut(std::vector<std::vector<unsigned int>> path){
    std::vector<unsigned int> cut;
    std::vector<bool> visited;
    for(unsigned int i = 0; i < vertex_number; i++){
        visited.push_back(false);
    }

    cut.push_back(s_vertex); //what if i'd use a set?
    visited[s_vertex] = true;
    for(unsigned int i = 0;  i < path.size(); i++){
        if(!visited[path[i][1]]){
            cut.push_back(path[i][1]);
            visited[path[i][1]] = true;
        }
    }
    return cut;
}

unsigned int Graph::update_graph(std::vector<std::vector<unsigned int>> path){
    unsigned int min_path_flow = MAXINT;
    for(unsigned int i = 0; i < path.size(); i++){
        if(path[i][2] < min_path_flow) min_path_flow = path[i][2];
    }
    for(unsigned int i = 0; i < path.size(); i++){
        this->graph_[path[i][0]][path[i][1]] -= min_path_flow;
        this->graph_[path[i][1]][path[i][0]] += min_path_flow;
    }    
    return min_path_flow;
}

unsigned int Graph::ford_fulkerson(){
    unsigned int flow = 0; 
    while(1){
        std::vector<std::vector<unsigned int>> path = get_path(dfs());
        if(path.empty()) break; //enquanto há caminho
        flow += update_graph(path); //incrementa o fluxo
    }
    return flow;
}

void Graph::print_solution(){
    unsigned int flow = ford_fulkerson();
    std::vector<unsigned int> cut = get_cut(dfs());
    std::cout << cut.size() << std::endl;
    for(unsigned i = 0; i < cut.size(); i++){
        std::cout << cut[i] << " ";
    }
    std::cout << std::endl;
    std::cout << flow << std::endl;
}