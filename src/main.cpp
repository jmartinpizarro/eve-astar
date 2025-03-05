#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unordered_map>
#include <stdexcept>

#include "includes/system.h"
#include "includes/state.h"
#include "includes/preprocessor.h"
#include "includes/graph.h"

string origin;
string destination;

int main(int argc, char* argv[]) {
    if (argc != 2){
        throw invalid_argument("Error: you have not passed the fileRoute parameter");
    }

    Graph g = read_file(argv[1], &origin, &destination);

    cout << origin << " - " << destination << endl;

    try{

        g.print_graph();

            
    } catch (const out_of_range& e) {
        cerr << "Error" << e.what() << "\n";
        return -1;
    }

    return 0;
}