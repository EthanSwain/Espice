//parent class for all components to be used in Espice
#ifndef COMPONENT_H
#define COMPONENT_h
#include <string>
#include <vector>
#pragma once
using namespace std;
class Node;
class Component{
    private:
        int num_terminals; // number of terminals a component has
        string name; // name of component
        vector<Node*> Nodes;  //inplement when node class is created
        void initialize_nodes(int num_terminals); //initalizes and empty vector of Nodes

    public:
        string comp_type;
        Component(int num_terminals =0, string name ="new component",string type = "Generic");
        ~Component();
        void set_type(string type);
        void set_num_terminals(int num);
        void set_name(string name);
        int get_num_terminals()const {return num_terminals;}
        string get_name()const {return name;}
        Node* get_node(int pos);
        void add_node(Node* node,int pos);
        void remove_node(int pos);
        void remove_node_by_name(Node* node);
};

#endif