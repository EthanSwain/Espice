#include "Circuit.h"

Circuit::Circuit(){
    ground = nullptr;
}

Circuit::~Circuit(){
    // Circuit doesn't own its Nodes/Components (same convention main.cpp
    // uses today) -- just drop our own bookkeeping.
    nodes.clear();
    components.clear();
    node_index.clear();
}

void Circuit::add_node(Node* node){
    nodes.push_back(node);
}

void Circuit::add_component(Component* component){
    components.push_back(component);
}

void Circuit::set_ground(Node* node){
    ground = node;
}

Node* Circuit::get_node(string name){
    for(int i = 0; i < (int)nodes.size(); i++){
        if(nodes[i]->get_name() == name){
            return nodes[i];
        }
    }
    return nullptr;
}

Component* Circuit::get_component(string name){
    for(int i = 0; i < (int)components.size(); i++){
        if(components[i]->get_name() == name){
            return components[i];
        }
    }
    return nullptr;
}

void Circuit::assign_node_indices(){
    // TODO: fill node_index -- every node except `ground` gets a unique
    // index (0..N-1) to use as its row/column in the system.
}

vector<vector<float>> Circuit::build_conductance_matrix(){
    // TODO: stamp resistor conductances into an N x N matrix using node_index.
    return {};
}

vector<float> Circuit::build_current_vector(){
    // TODO: stamp independent source contributions into a length-N vector.
    return {};
}

vector<float> Circuit::solve_linear_system(vector<vector<float>> A, vector<float> b){
    // TODO: solve A*x = b (e.g. Gaussian elimination). Empty vector = unsolvable.
    return {};
}

void Circuit::apply_solution(const vector<float> &solution){
    // TODO: write solved voltages back onto Nodes and mark them known.
}

bool Circuit::solve(){
    // TODO: orchestrate assign_node_indices() -> build_conductance_matrix()
    // -> build_current_vector() -> solve_linear_system() -> apply_solution().
    return false;
}
