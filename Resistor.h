#ifndef RESISTOR_H
#define RESISTOR_H

#include "Component.h"
class Node;
class Resistor : public Component{
    private:
        float resistance; // resistance of the resistor
        float current; //current through the resistor + is from 0->1
        float voltage_drop;
        bool current_is_known;
    public:
    Resistor(int num_terminals  = 2,string name = "New Resistor",string type = "Resistor", float resistance = 0);
    ~Resistor();
    void set_current_known(bool known);
    bool get_current_known() const {return current_is_known;}
    void set_current(float current);
    float get_current() const {return current;}
    void set_resistance(float resistance);
    float get_resistance() const {return resistance;}
    void set_voltage_drop(float volts);
    float get_voltage_drop() const{return voltage_drop;}
    bool calc_current(int high_term,int low_term); //returns true if current can be calculated
    bool calc_voltage_drop(); // takes in known terminal positon and reutnr voltage drip
};  

#endif