#include "Resistor.h"
#include <iostream>

Resistor::Resistor(int num_terminals,string name,string type, float resistance) 
    : Component(num_terminals,name,type), resistance(resistance){
    set_current(0);
}

Resistor::~Resistor(){

}

void Resistor::set_current(float current){
    this->current = current;
} 

void Resistor::set_resistance(float resistance){
    this->resistance = resistance;
}

bool Resistor::calc_current(int high_term,int low_term){
    Node *high_node = get_node(high_term);
    Node *low_node  = get_node(low_term);
    if(high_node->get_known() && low_node->get_known()){
        

        return true;
    } else {
        return false;
    }
}