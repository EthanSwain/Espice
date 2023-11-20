#ifndef RESISTOR_H
#define RESISTOR_H

#include "Component.h"

class Resistor : public Component{
    private:
        float resistance;
    public:
    Resistor(int num_terminals  = 2,string name = "New Resistor",string type = "Resistor", float resistance = 0);
    ~Resistor();
    void set_resistance(float resistance);
    float get_resistance() const {return resistance;}
    //maybe add functions to calculate

};

#endif