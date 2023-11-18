#include "Component.h"
#include <iostream>
Component::Component(int num_terminals, string name){
    set_name(name);
    set_num_terminals(num_terminals);
    initalize_nodes(num_terminals);

}

Component::~Component(){
    for(int i =0; i < get_num_terminals(); i++){
        Nodes[i]->remove_component(this); // removes current node from every node its connected to
    }
    set_num_terminals(0);
    set_name("");
    delete this;

}

void Component::set_num_terminals(int num){
    num_terminals = num;
}

void Component::set_name(string name){
    name = name;
}

void Component::initalize_nodes(int num_terminals){
    for(int i = 0; i< num_terminals; i++){
        Nodes.push_back(NULL);
    }
}

Node* Component::get_node(int pos){
    if(pos<= num_terminals){
        return Nodes[pos];
    } else {
        cout<<"ERROR: position entered is higher than number of terminals \n";
    }

}

void Component::add_node(Node* node,int pos){
    if(pos<= num_terminals){
        Nodes[pos] = node;
        node->add_component(this);
    } else{
         cout<<"ERROR: position entered is higher than number of terminals \n";
    }
}

void Component::remove_node(int pos){
    if(pos<= num_terminals){
        if(Nodes[pos] != NULL){
            delete Nodes[pos];
            Nodes[pos] = NULL;
        }
    } else{
         cout<<"ERROR: position entered is higher than number of terminals \n";
    }
}

void Component::remove_node_by_name(Node* node){
    bool is_found = false; // is false if node not found
    if(node == NULL){
        cout<<"ERROR: The Node trying to be removed is NULL \n";
    } else {
        for(int i =0; i< num_terminals; i++){
            if(Nodes[i] == node){
                is_found = true;
                Nodes[i] = NULL;
            }
        }
        if(!is_found){
            cout<<"ERROR: Node being deleted not found";
        }
    }
};

