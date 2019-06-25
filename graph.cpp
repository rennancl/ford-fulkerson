#include "graph.h"

Graph::Graph(unsigned int vertex_number,unsigned  int edges_number){
	this->edges_number = edges_number;
    this->vertex_number = vertex_number;
    this->flow = MAXINT;

    this->graph_ = (int**) malloc(sizeof(int*)* vertex_number);
    for(unsigned  int i = 0; i < vertex_number; i++){
        this->graph_[i] = (int*) malloc(sizeof(int)* vertex_number);
    }

    this->graph_aux = (int**) malloc(sizeof(int*)* vertex_number);
    for(unsigned int i = 0; i < vertex_number; i++){
        this->graph_aux[i] = (int*) malloc(sizeof(int)* vertex_number);
    }
}

void Graph::read_input(){
    std::vector<int> edge;
    int value;
    edge.push_back(0);
    edge.push_back(0);
    edge.push_back(0);
    for(unsigned int i = 0; i < edges_number; i++){
		for(unsigned int j = 0; j < 3; j++){
			std::cin >> value;
			edge[j] = value;
		}
		this->edges.push_back(edge);
	}
    return;
}

void Graph::create_graph(){
    // std::vector<int> neighbors;
    // for(unsigned int j = 0; j < vertex_number; j++){
    //     neighbors.push_back(0);
    // }
    
    // for(unsigned int i = 0; i < vertex_number; i++){
    //     this->graph_.push_back(neighbors);
    // }

    for(unsigned int i = 0; i < this->edges.size(); i++){
        this->graph_[this->edges[i][0]][this->edges[i][1]] = this->edges[i][2];
        this->graph_[this->edges[i][1]][this->edges[i][0]] = this->edges[i][2];
        this->graph_aux[this->edges[i][0]][this->edges[i][1]] = this->edges[i][2];
        this->graph_aux[this->edges[i][1]][this->edges[i][0]] = this->edges[i][2];

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

std::vector<std::vector<unsigned int>> Graph::dfs(){
    std::vector<bool> visited;
    std::vector<unsigned int> parent;

    std::vector<std::vector<unsigned int>> path;
    std::stack<int> vertex_stack;
    vertex_stack.push(s_vertex);
    int vertex;
    
    for(unsigned int i = 0; i < vertex_number; i++){
        visited.push_back(false);
        parent.push_back(i);
    }
    parent[s_vertex] = s_vertex;


    std::vector<unsigned int> temp_edge;
    temp_edge.push_back(0);
    temp_edge.push_back(0);
    temp_edge.push_back(0);

    while(!vertex_stack.empty()){
        vertex = vertex_stack.top(); 
        vertex_stack.pop();
        for(unsigned int j = 0; j < vertex_number; j++){
            if(this->graph_[vertex][j] > 0 and !visited[j]){
                visited[j] = true;
                vertex_stack.push(j);
                temp_edge[0] = vertex;
                temp_edge[1] = j;
                temp_edge[2] = graph_[vertex][j];
                path.push_back(temp_edge);

                parent[j] = vertex;
                if(j == t_vertex) return path;
            }
        }
    }
    return path;
}
std::vector<std::vector<unsigned int>> Graph::get_path(std::vector<std::vector<unsigned int>> path){
    bool t_visited = false;
    unsigned int target = t_vertex;
    std::vector<std::vector<unsigned int>> path_;
    std::vector<unsigned int> parent;
    std::vector<unsigned int> temp_edge;
    temp_edge.push_back(0);
    temp_edge.push_back(0);
    temp_edge.push_back(0);

    // for(unsigned int i = 0; i < path.size(); i++){
    //     std::cout << path[i][0] << "-" << path[i][1] << std::endl;
    // }
    // std::cout << "CANDIDATOS" << std::endl;

    for(unsigned int i = 0;  i < path.size(); i++){
        if(path[i][1] == t_vertex){
            t_visited = true;
            break;
        }
    }
    if(!t_visited){
        return path_;
    }

    for(unsigned int i = 0; i < vertex_number; i++){
        parent.push_back(i);
    }
    for(unsigned int i = path.size(); i > 0; i--){
        parent[path[i-1][1]] = path[i-1][0];
    }
    parent[s_vertex] = s_vertex;

    for(unsigned int i = 0; i <= vertex_number; i++){
        temp_edge[0] = parent[target];
        temp_edge[1] = target;
        temp_edge[2] = graph_[parent[target]][target];
        path_.push_back(temp_edge);
        if(parent[target] == s_vertex )break;
        target = parent[target];

    }


    // for(unsigned int i = 0; i < path_.size(); i++){
    //     std::cout << path_[i][0] << "-" << path_[i][1] << std::endl;
    // }
    // std::cout << "FIM CAMINHO" << std::endl;

    return path_;
}



std::vector<unsigned int> Graph::get_cut(std::vector<std::vector<unsigned int>> path){
    std::vector<unsigned int> cut;
    std::vector<bool> visited;
    for(unsigned int i = 0; i < vertex_number; i++){
        visited.push_back(false);
    }

    cut.push_back(s_vertex);
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
    std::vector<std::vector<unsigned int>> path;
    while(1){
        path = get_path(dfs());
        if(path.empty()) break; //enquanto há caminho
        flow += update_graph(path); //incrementa o fluxo
    }
    return flow;
}

void Graph::print_solution(){
    std::cout << this->cut.size() << std::endl;
    for(unsigned i = 0; i < this->cut.size(); i++){
        std::cout << this->cut[i] << " ";
    }
    std::cout << std::endl;
    std::cout << this->flow << std::endl;
}

void Graph::get_solution(){
    unsigned int flow_ = 0;
    s_vertex = 0;
    for(unsigned int i = 1; i < vertex_number; i++){
        t_vertex = i;
        flow_ = ford_fulkerson();
        if(flow_ < this->flow){
            this->flow = flow_;
            this->cut = get_cut(dfs());
        }

    for(unsigned int i = 0; i < vertex_number; i++){
        for(unsigned int j = 0; j < vertex_number; j++){
                this->graph_[i][j] = this->graph_aux[i][j];
            }
        }
    }    
}