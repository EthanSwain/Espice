#ifndef RESISTOR_H
#define RESISTOR_H

#include "Component.h"
class Node;
class Resistor : public Component{
    private:
        float resistance; // resistance of the resistor
        float current; //current through the resistor + is from 0->1
    public:
    bool current_known;
    Resistor(int num_terminals  = 2,string name = "New Resistor",string type = "Resistor", float resistance = 0);
    ~Resistor();
    void set_current(float current);
    float get_current() const {return current;}
    void set_resistance(float resistance);
    float get_resistance() const {return resistance;}
    bool calc_current(int high_term,int low_term); //returns true if current can be calculated
    float calc_voltage_drop(int known_terminal); // takes in known terminal positon and reutnr voltage drip
};  

#endif