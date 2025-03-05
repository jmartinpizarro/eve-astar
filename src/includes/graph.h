#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <string>

#include "system.h"

class Graph {
    private:
        unordered_map<string, System*> systems;
    
    public:
        System* get_or_create_system(const string& name, double security = 0.0) {
            if (systems.find(name) == systems.end()) {
                systems[name] = new System(name, security);
            }
            return systems[name];
        }
    
        void add_connection(const string& from, const string& to, double distance) {
            System* system1 = get_or_create_system(from);
            System* system2 = get_or_create_system(to);
            
            system1->add_adjacent_system(to, system2);
            system1->add_adjacent_system_distance(system2, distance);
        }

        void print_graph(){
            for (const auto& [name, system] : systems){
                cout << "System " << name << " is connected to:\n";
                for (const auto& [adj_name, adj_system] : system->get_adjacent_systems()) {
                    cout << "\t - " << adj_name << " with distance " 
                        << system->get_adjacent_systems_distance()[adj_system] << "\n";
                }
            }
        }
    };
    

#endif