//the node class is repesetns a net tying terminals together
#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>
#include "Component.h"

class Node{
    private:
        string name;
        vector<Component*> components;
        int num_components;
        float voltage_level;
    public:
        Node(string name ="new node");
        ~Node();
        void set_name(string name);
        void set_voltage(float volts);
        void add_component(Component *Component);
        float get_volts() const {return voltage_level;}
        string get_name() const{return name;}
        Component* get_component(int pos);
        void remove_component(Component *Component);

};

#endif
