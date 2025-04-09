#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <deque>
#include <stdexcept>
#include <deque>

#include "includes/system.h"
#include "includes/state.h"
#include "includes/preprocessor.h"
#include "includes/graph.h"
#include "includes/a_star.h"

string origin;
string destination;

void get_origin_destination_systems(Graph* g, State*& origin_S, State*& destination_S) {
    // Type*& var permite modificar punteros fuera de la función
    origin_S->currentSystem = g->get_system(origin);
    destination_S->currentSystem = g->get_system(destination);
}

int main(int argc, char* argv[]) {
    if (argc != 2){
        throw invalid_argument("Error: you have not passed the fileRoute parameter");
    }

    Graph g = read_file(argv[1], &origin, &destination);

    cout << origin << " - " << destination << endl;
    cout << "=== A* Algorithm is starting ===" << endl;

    try{
        //g.print_graph();
        State* origin_S = new State();
        State* destination_S = new State();
        get_origin_destination_systems(&g, origin_S, destination_S);
        
        State* a_state = a_star(g, origin_S, destination_S);

        if (!a_state){
            cout << " A*: no possible solution found" << endl;
            return -1;
        }

        deque<State*>path;
        while (a_state){
            path.push_front(a_state);
            if (a_state == nullptr) continue;
            a_state = a_state->prev;
        }
        
        cout << "\tPath: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i]->currentSystem->get_name() << '(' << path[i]->currentSystem->get_security() << ')';
            if (i < path.size() - 1)
                cout << " -> ";
        }
        cout << " with a total jumps of: " << path.size() << endl;

        delete origin_S;
        delete destination_S;
        cout << "=== A* Algorithm has ended ===" << endl;
    } catch (const out_of_range& e) {
        cerr << "Error" << e.what() << "\n";
        return -1;
    }
    return 0;
}

