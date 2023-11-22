#include "DC_voltage.h"
#include <iostream>

DC_voltage::DC_voltage(int num_terminals, string name, string type, float init_voltage)
    : Component(num_terminals,name,type), voltage_level(init_voltage){

}

DC_voltage::~DC_voltage(){

}

void DC_voltage::set_voltage_level(float volts){
    this->voltage_level = volts;
}