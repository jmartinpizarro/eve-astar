#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <string>

#include "system.h"

class Graph{
    public:
        int n_elements = 0;
        unordered_map<string, System*> nodes;


        int add_system(System* system){
            nodes[system->get_name()] = system;
            n_elements++;
            return 0;
        }
};

#endif