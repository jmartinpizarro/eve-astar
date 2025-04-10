#include <algorithm>
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
        int unsec1 = 0, unsec2 = 0;
        if (!a_state){
            cout << " A*: no possible solution found" << endl;
            return -1;
        }

        deque<State*>path;
        while (a_state){
            path.push_front(a_state);
            if (a_state->currentSystem->get_security() <= 0.4){
                unsec1++;
            }
            if (a_state == nullptr) continue;
            a_state = a_state->prev;
        }

        cout << "=== A* second iteration has started" << endl;
        // homemade solution to the problem of expansion order 
        // (destionation&origin) || (origin&destination) may have different orders, it is
        // choosen the best
        a_state = a_star(g, destination_S, origin_S);

        // in theory here we know that here there will be always a solution!
        if (!a_state){ 
            cout << " A*: no possible solution found" << endl;
            return -1;
        }

        deque<State*>path2;
        while (a_state){
            path2.push_front(a_state);
            if (a_state->currentSystem->get_security() <= 0.4){
                unsec2++;
            }
            if (a_state == nullptr) continue;
            a_state = a_state->prev;
        }

        // if the path2 is smaller and has less <= 0.4 systems, replace it as the new path
        if (path2.size() <= path.size() && unsec2 <= unsec1) {
            reverse(path2.begin(), path2.end());
            path = path2;
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

