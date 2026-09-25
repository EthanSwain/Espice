#include <iostream>
#include <string>
#include "Component.h"
#include "Node.h"
#include "Resistor.h"
#include "DC_voltage.h"
#include "Circuit.h"
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
    test_vss->add_node(node_1,1);
    
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

    cout<<"\nstart Circuit solve test (voltage divider) \n";
    // 10V source across node_a/ground, R1 from node_a to node_b, R2 from node_b to ground.
    // Expected: node_a = 10V, node_b = 10 * R2/(R1+R2) = 10 * 2000/3000 = 6.6667V
    Node *gnd = new Node("ground");
    Node *node_a = new Node("node_a");
    Node *node_b = new Node("node_b");

    DC_voltage *v1 = new DC_voltage(2, "V1", "Voltage source", 10.0);
    v1->add_node(node_a, 0); // +
    v1->add_node(gnd, 1);    // -

    Resistor *r1 = new Resistor(2, "R1", "Resistor", 1000.0);
    r1->add_node(node_a, 0);
    r1->add_node(node_b, 1);

    Resistor *r2 = new Resistor(2, "R2", "Resistor", 2000.0);
    r2->add_node(node_b, 0);
    r2->add_node(gnd, 1);

    Circuit circuit;
    circuit.add_node(gnd);
    circuit.add_node(node_a);
    circuit.add_node(node_b);
    circuit.add_component(v1);
    circuit.add_component(r1);
    circuit.add_component(r2);
    circuit.set_ground(gnd);

    if(circuit.solve()){
        cout << "ground voltage: " << gnd->get_volts() << "\n";
        cout << "node_a voltage: " << node_a->get_volts() << "\n";
        cout << "node_b voltage: " << node_b->get_volts() << "\n";
    } else {
        cout << "circuit solve FAILED\n";
    }

}
