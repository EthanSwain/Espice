#include "Component.h"
#include <iostream>
Component::Component(int num_terminals, string name){
    set_name(name);
    set_num_terminals(num_terminals);
    initalize_nodes(num_terminals);

}

Component::~Component(){
    //TODO figure out delete logic for node and component
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

