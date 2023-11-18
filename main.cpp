#include <iostream>
#include <string>
#include "Component.h"
#include "Node.h"
using namespace std;
int main() {
    Component *test_comp = new Component(2,"test resist 1");
    Component *test_res = new Component(2,"test resist 2");
    Component *test_vss = new Component(2,"test vs");
    vector<Node*> Nodes;
    vector<Component*> comps;

    Node *node_1 = new Node("node 1");
    node_1->set_voltage(5.0);
    Node *node_2 = new Node("node 2");
    node_2->set_voltage(4.0);
    Node *node_3 = new Node("node 3");
    node_3->set_voltage(3.3);
    Nodes.push_back(node_1);
    Nodes.push_back(node_2);
    Nodes.push_back(node_3);

    comps.push_back(test_comp);
    comps.push_back(test_res);
    comps.push_back(test_vss);  

    test_comp->add_node(node_1,0);
    test_comp->add_node(node_2,1);
    test_res->add_node(node_2,0);
    test_res->add_node(node_3,1);
    test_vss->add_node(node_3,0);
    test_vss->add_node(node_3,1);
    
    cout<<"start comp test \n";
    for(int i =0; i< 3; i++){
        for(int k = 0; k <2; k++){
            cout<<comps[i]->get_name() <<" is connected to " << comps[i]->get_node(k)->get_name() << " with voltage " << comps[i]->get_node(k)->get_volts() << "\n";
        }
    }

    cout<<"start Node test \n";
    for(int i =0; i< 3; i++){
        for(int k = 0; k <2; k++){
            cout<<Nodes[i]->get_name() <<" is connected to " << Nodes[i]->get_component(k)->get_name() <<"\n";
        }
    }
    
}   
