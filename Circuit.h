//owns the nodes/components that make up a circuit and solves for unknown node voltages
#ifndef CIRCUIT_H
#define CIRCUIT_H
#include <string>
#include <vector>
#include <map>
#include "Node.h"
#include "Component.h"
using namespace std;

// NOTE: plain nodal analysis (a G-matrix built from conductances alone) can't
// represent an ideal voltage source directly. Modified Nodal Analysis (MNA)
// handles this by adding one extra unknown (the branch current) and one extra
// row/column per voltage source. Deciding how DC_voltage sources get stamped
// into the system is left as a TODO below.

class Circuit{
    private:
        vector<Node*> nodes;
        vector<Component*> components;
        Node* ground;
        map<Node*,int> node_index; // maps each non-ground node to its row/column in the system

        void assign_node_indices();
        // TODO: walk `nodes`, skip `ground`, and give every other node a unique
        // index in `node_index` (0..N-1) for use as a row/column in the system.

        vector<vector<float>> build_conductance_matrix();
        // TODO: build the N x N conductance (G) matrix. For each Resistor,
        // "stamp" its conductance (1/resistance) into the rows/columns of the
        // two nodes it's connected to (add on the diagonal entries, subtract
        // on the off-diagonal entries; skip terminals connected to ground).

        vector<float> build_current_vector();
        // TODO: build the length-N right-hand-side vector. For each independent
        // source (e.g. DC_voltage), stamp its contribution here -- see the MNA
        // note above; a pure nodal G-matrix may not be enough on its own.

        vector<float> solve_linear_system(vector<vector<float>> A, vector<float> b);
        // TODO: solve A*x = b for x (e.g. Gaussian elimination). Return an
        // empty vector if the system is singular / can't be solved.

        void apply_solution(const vector<float> &solution);
        // TODO: write each solved voltage back onto its Node (Node::set_voltage)
        // and mark it known (Node::set_is_known(true)).

    public:
        Circuit();
        ~Circuit();

        void add_node(Node* node);
        void add_component(Component* component);
        void set_ground(Node* node); // reference node, held at 0V and excluded from the unknowns

        Node* get_node(string name);
        Component* get_component(string name);

        bool solve();
        // TODO: orchestrate assign_node_indices() -> build_conductance_matrix()
        // -> build_current_vector() -> solve_linear_system() -> apply_solution().
        // Return false if the circuit couldn't be solved (e.g. no ground set,
        // singular system).
};

#endif
