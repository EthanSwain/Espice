#ifndef DC_VOLTAGE_H
#define DC_VOLTAGE_H

#include "Component.h"

class DC_voltage : public Component{
    private:
        float voltage_level;
    public:
        DC_voltage(int num_terminals = 2, string name = "new source", string type ="Voltage source", float init_volt =0);
        ~DC_voltage();
        float get_voltage_level() const {return voltage_level;}
        void set_voltage_level(float volts);

};

#endif