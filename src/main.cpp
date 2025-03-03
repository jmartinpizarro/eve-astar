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

int main(int argc, char* argv[]) {
    if (argc != 2){
        cerr << "Error: you have not passed the fileRoute parameter";
    }

    read_file(argv[1]);

    try{

        System s1 = {"Jita", 1.0};
        System s2 = {"Amarr", 1.0};
        System s3 = {"Perimeter", 1.0};
        System s4 = {"Tama", 0.4};
        System s5 = {"Villore", 0.6};
    
        s1.add_adjacent_system(s3.get_name(), &s3);

        s2.add_adjacent_system(s5.get_name(), &s5);

        s3.add_adjacent_system(s1.get_name(), &s1);
        s3.add_adjacent_system(s4.get_name(), &s4);
        s3.add_adjacent_system(s5.get_name(), &s5);

        s4.add_adjacent_system(s3.get_name(), &s3);

        s5.add_adjacent_system(s4.get_name(), &s3);
        s5.add_adjacent_system(s5.get_name(), &s2);

        /*---*/
        s1.add_adjacent_system_distance(&s3, 6.7);

        s2.add_adjacent_system_distance(&s5, 3.4);

        s3.add_adjacent_system_distance(&s1, 6.7);
        s3.add_adjacent_system_distance(&s4, 76.4);
        s3.add_adjacent_system_distance(&s5, 8.7);

        s4.add_adjacent_system_distance(&s3, 76.4);

        s5.add_adjacent_system_distance(&s2, 8.7);
        s5.add_adjacent_system_distance(&s3, 3.4);

        Graph g;
        System* systems[] = {&s1,&s2,&s3,&s4,&s5};
        int size = 5;

        for (int i = 0; i < size; i++){
            g.add_system(systems[i]);
        }

        for (const auto& [name, system] : g.nodes) {
            cout << "System " << name << " is connected to:\n";
            for (const auto& [adj_name, adj_system] : system->get_adjacent_systems()) {
                cout << "\t - " << adj_name << " with distance " 
                     << system->get_adjacent_systems_distance()[adj_system] << "\n";
            }
        }
            
    } catch (const out_of_range& e) {
        cerr << "Error" << e.what() << "\n";
        return -1;
    }

    return 0;
}