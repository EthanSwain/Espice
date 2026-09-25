#include "Circuit.h"
#include "Resistor.h"
#include "DC_voltage.h"
#include <cmath>
#include <algorithm>

Circuit::Circuit(){
    ground = nullptr;
}

Circuit::~Circuit(){
    // Circuit doesn't own its Nodes/Components (same convention main.cpp
    // uses today) -- just drop our own bookkeeping.
    nodes.clear();
    components.clear();
    node_index.clear();
    vsource_index.clear();
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
    node_index.clear();
    int idx = 0;
    for(int i = 0; i < (int)nodes.size(); i++){
        if(nodes[i] == ground) continue;
        node_index[nodes[i]] = idx++;
    }
}

void Circuit::assign_vsource_indices(){
    vsource_index.clear();
    int idx = 0;
    for(int i = 0; i < (int)components.size(); i++){
        if(dynamic_cast<DC_voltage*>(components[i]) != nullptr){
            vsource_index[components[i]] = idx++;
        }
    }
}

vector<vector<float>> Circuit::build_conductance_matrix(){
    int n = (int)node_index.size();
    int m = (int)vsource_index.size();
    int size = n + m;
    vector<vector<float>> A(size, vector<float>(size, 0.0f));

    for(int i = 0; i < (int)components.size(); i++){
        Resistor* r = dynamic_cast<Resistor*>(components[i]);
        if(r == nullptr) continue;

        float resistance = r->get_resistance();
        if(resistance == 0.0f) continue; // ideal short: no finite conductance to stamp

        float g = 1.0f / resistance;
        Node* node_a = r->get_node(0);
        Node* node_b = r->get_node(1);

        bool a_grounded = (node_a == ground || node_a == nullptr);
        bool b_grounded = (node_b == ground || node_b == nullptr);
        int a = a_grounded ? -1 : node_index[node_a];
        int b = b_grounded ? -1 : node_index[node_b];

        if(a != -1) A[a][a] += g;
        if(b != -1) A[b][b] += g;
        if(a != -1 && b != -1){
            A[a][b] -= g;
            A[b][a] -= g;
        }
    }

    for(map<Component*,int>::iterator it = vsource_index.begin(); it != vsource_index.end(); ++it){
        DC_voltage* vs = dynamic_cast<DC_voltage*>(it->first);
        int k = n + it->second;
        Node* pos = vs->get_node(0);
        Node* neg = vs->get_node(1);

        bool pos_grounded = (pos == ground || pos == nullptr);
        bool neg_grounded = (neg == ground || neg == nullptr);
        int a = pos_grounded ? -1 : node_index[pos];
        int b = neg_grounded ? -1 : node_index[neg];

        if(a != -1){ A[a][k] += 1.0f; A[k][a] += 1.0f; }
        if(b != -1){ A[b][k] -= 1.0f; A[k][b] -= 1.0f; }
    }

    return A;
}

vector<float> Circuit::build_current_vector(){
    int n = (int)node_index.size();
    int m = (int)vsource_index.size();
    vector<float> b(n + m, 0.0f);

    for(map<Component*,int>::iterator it = vsource_index.begin(); it != vsource_index.end(); ++it){
        DC_voltage* vs = dynamic_cast<DC_voltage*>(it->first);
        int k = n + it->second;
        b[k] = vs->get_voltage_level();
    }

    return b;
}

vector<float> Circuit::solve_linear_system(vector<vector<float>> A, vector<float> b){
    int n = (int)A.size();
    const float eps = 1e-9f;

    for(int col = 0; col < n; col++){
        int pivot_row = col;
        float max_val = fabs(A[col][col]);
        for(int row = col + 1; row < n; row++){
            if(fabs(A[row][col]) > max_val){
                max_val = fabs(A[row][col]);
                pivot_row = row;
            }
        }
        if(max_val < eps){
            return {}; // singular -- no unique solution
        }
        if(pivot_row != col){
            swap(A[col], A[pivot_row]);
            swap(b[col], b[pivot_row]);
        }

        for(int row = col + 1; row < n; row++){
            float factor = A[row][col] / A[col][col];
            for(int k = col; k < n; k++){
                A[row][k] -= factor * A[col][k];
            }
            b[row] -= factor * b[col];
        }
    }

    vector<float> x(n, 0.0f);
    for(int row = n - 1; row >= 0; row--){
        float sum = b[row];
        for(int k = row + 1; k < n; k++){
            sum -= A[row][k] * x[k];
        }
        x[row] = sum / A[row][row];
    }
    return x;
}

void Circuit::apply_solution(const vector<float> &solution){
    for(map<Node*,int>::iterator it = node_index.begin(); it != node_index.end(); ++it){
        Node* node = it->first;
        int idx = it->second;
        node->set_voltage(solution[idx]);
        node->set_is_known(true);
    }
}

bool Circuit::solve(){
    if(ground == nullptr) return false;

    assign_node_indices();
    assign_vsource_indices();

    vector<vector<float>> A = build_conductance_matrix();
    vector<float> b = build_current_vector();

    if(A.empty()){
        // no unknowns at all (e.g. a circuit with only a ground node)
        ground->set_voltage(0.0f);
        ground->set_is_known(true);
        return true;
    }

    vector<float> x = solve_linear_system(A, b);
    if(x.empty()) return false; // singular system

    apply_solution(x);
    ground->set_voltage(0.0f);
    ground->set_is_known(true);
    return true;
}
