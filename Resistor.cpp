#include "Resistor.h"
#include "Node.h"
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

void Resistor::set_voltage_drop(float volts){
    this->voltage_drop = volts;
}

void Resistor::set_current_known(bool known){
    this->current_is_known = known;
}

bool Resistor::calc_current(int high_term,int low_term){
    Node *high_node = get_node(high_term);
    Node *low_node  = get_node(low_term);
    if(high_node->get_known() && low_node->get_known()){
       float volt_diff = (high_node->get_volts() - low_node->get_volts());
       float current = volt_diff/(this->resistance);
       set_current(current);
        return true;
    } else {
        return false;
    }
}

bool Resistor::calc_voltage_drop(){
    if(get_current_known()){
        set_voltage_drop((get_current() * get_resistance()));
        return true;
    } else{
        return false;
    }
}