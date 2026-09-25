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
        map<Node*,int> node_index; // maps each non-ground node to its unknown-voltage row/column
        map<Component*,int> vsource_index; // maps each DC_voltage to its branch-current row/column

        void assign_node_indices();
        // walks `nodes`, skips `ground`, gives every other node a unique index
        // (0..N-1) -- these are the unknown node-voltage rows/columns.

        void assign_vsource_indices();
        // walks `components`, finds every DC_voltage, gives each a unique index
        // (0..M-1). These become extra unknown-branch-current rows/columns
        // appended after the N node-voltage rows, per Modified Nodal Analysis
        // (see note above) since an ideal voltage source has no conductance
        // to stamp directly into a plain G-matrix.

        vector<vector<float>> build_conductance_matrix();
        // builds the (N+M) x (N+M) MNA system matrix. Resistors stamp
        // conductance (1/resistance) into the node-voltage rows/columns
        // (add on the diagonal, subtract off-diagonal; skip terminals tied to
        // ground). DC_voltage sources stamp +/-1 into the row/column pairing
        // their branch-current unknown with each of their two node terminals.

        vector<float> build_current_vector();
        // builds the length-(N+M) right-hand-side vector. The node-voltage
        // rows are 0 (no independent current sources exist yet); each
        // DC_voltage's branch-current row holds its source voltage.

        vector<float> solve_linear_system(vector<vector<float>> A, vector<float> b);
        // solves A*x = b via Gaussian elimination with partial pivoting.
        // Returns an empty vector if the system is singular.

        void apply_solution(const vector<float> &solution);
        // writes each solved node voltage back onto its Node (Node::set_voltage)
        // and marks it known (Node::set_is_known(true)). Branch-current
        // unknowns (the tail of `solution`) aren't stored anywhere yet.

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
