#ifndef GRAPH_H
#define GRAPH_H

#include "system.h"

/*
* TODO: migrate to a class, create methods for inserting nodes
*/

class Graph{
    public:
        int n_elements = 0;
        System* nodes[];

        int add_system(System* system){
            nodes[n_elements] = system;
            n_elements++;
            return 0;
        }
};

#endif