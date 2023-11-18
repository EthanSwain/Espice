#include "Component.h"
#include "Node.h"
#include <iostream>
#include <stdexcept>  // for std::out_of_range

Component::Component(int num_terminals, string name) {
    set_name(name);
    set_num_terminals(num_terminals);
    initialize_nodes(num_terminals);
}

Component::~Component() {
    for (int i = 0; i < get_num_terminals(); i++) {
        if (Nodes[i] != nullptr) {
            Nodes[i]->remove_component(this); // removes current node from every node it's connected to
        }
    }
    set_num_terminals(0);
    set_name("");
}

void Component::set_num_terminals(int num) {
    num_terminals = num;
}

void Component::set_name(string name) {
    this->name = name;
}

void Component::initialize_nodes(int num_terminals) {
    for (int i = 0; i < num_terminals; i++) {
        Nodes.push_back(nullptr);
    }
}

Node* Component::get_node(int pos) {
    if (pos < num_terminals) {
        return Nodes[pos];
    } else {
        throw out_of_range("ERROR: position entered is higher than number of terminals");
    }
}

void Component::add_node(Node* node, int pos) {
    if (pos < num_terminals) {
        Nodes[pos] = node;
        node->add_component(this);
    } else {
        throw out_of_range("ERROR: position entered is higher than number of terminals");
    }
}

void Component::remove_node(int pos) {
    if (pos < num_terminals) {
        if (Nodes[pos] != nullptr) {
            delete Nodes[pos];
            Nodes[pos] = nullptr;
        }
    } else {
        throw out_of_range("ERROR: position entered is higher than number of terminals");
    }
}

void Component::remove_node_by_name(Node* node) {
    bool is_found = false; // is false if node not found
    if (node == nullptr) {
        throw invalid_argument("ERROR: The Node trying to be removed is NULL");
    } else {
        for (int i = 0; i < num_terminals; i++) {
            if (Nodes[i] == node) {
                is_found = true;
                Nodes[i] = nullptr;
            }
        }
        if (!is_found) {
            throw runtime_error("ERROR: Node being deleted not found");
        }
    }
}