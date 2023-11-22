#include "Component.h"
#include "Node.h"
#include <iostream>

Node::Node(string name){
    set_name(name);
    set_voltage(0);
    num_components = 0;
    set_is_known(false);
}

Node::~Node(){
    for(int i = 0; i < num_components; i++){
        components[i]->remove_node_by_name(this);
        num_components--;
    }
    set_voltage(0);
    set_name("");
}

void Node::set_name(string name){
    this->name = name; 
}

void Node::set_voltage(float volts){
    voltage_level = volts;
}

void Node::add_component(Component *Component){
    num_components++;
    components.push_back(Component);
}

Component* Node::get_component(int pos){
    if(pos >= num_components){
        cout << "ERROR: invalid component position \n";
        return nullptr;
    } else {
        return components[pos];
    }
}
void Node::set_is_known(bool found){
    this->is_known = found;
}
void Node::remove_component(Component *Component){
    bool is_found = false;
    for(int i = 0; i < num_components; i++){
        if(components[i] == Component){
            components.erase(components.begin() + i);
            num_components--;
            is_found = true;
            break;  // Once found, no need to continue the loop
        }
    }
    if(!is_found){
        cout << "ERROR: component not found \n";
    }
}