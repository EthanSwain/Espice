
#ifndef COMPONENT_H
#define COMPONENT_h
#include <string>
#include <vector>
using namespace std;
class Component{
    private:
        int num_terminals; // number of terminals a component has
        string name; // name of component
        //vector<*Node> Nodes;  //inplement when node class is created
    public:
    int get_num_terminals();
    string get_name();
    //*Node get_node(int pos);
};

#endif