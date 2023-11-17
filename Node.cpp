#include "Node.h"
#include <iostream>

Node::Node(string name){
    set_name(name);
    set_voltage(0);
    num_components =0;
}

Node::~Node(){
    for(int i =0; i< num_components;i++){
        components[i]->remove_node_by_name(this);
        num_components --;
    }
    set_voltage(0);
    set_name("");
}

void Node::set_name(string name){
    name = name;
}

void Node::set_voltage(float volts){
    voltage_level = volts;
}

void Node::add_component(Component *Component){
    num_components ++;
    components.push_back(Component);
}

Component* Node::get_component(int pos){
    if(pos > num_components){
        cout<<"ERROR: invalid component position \n";
        return NULL;
    } else {
        return components[pos];
    }
}

void Node::remove_component(Component *Component){
    bool is_found = false;
    for(int i =0; i< num_components; i++){
        if(components[i] == Component){
            components.erase(components.begin() +i);
            num_components --;
            is_found = true;
        }
    }
    if(!is_found){
        cout<<"ERROR: component not found \n";
    }
}