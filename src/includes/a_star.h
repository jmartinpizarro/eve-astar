#ifndef A_STAR_H
#define A_STAR_H

#include "system.h"
#include "state.h"
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

/**
 * @brief A* algorithm
 * @param g: Graph. Necessary for calculating the heuristic
 * @param origin, destination: states nodes
 * @return State*. The final node, solution has been found
 */
inline State* a_star(Graph& g, State* origin, State* destination) {
    // Vector to store open list, with custom sorting
    std::vector<State*> open_list;
    std::unordered_map<System*, double> g_values;  // stores g(x) for each system
    std::unordered_set<System*> closed_systems;    // tracks the systems already visited

    // Sorting function for open list
    auto compare_states = [](State* a, State* b) {
        return a->heuristic_value < b->heuristic_value;
    };

    origin->heuristic_value = 0; // starting point heuristic (f(x) = g(x) + h(x))
    g_values[origin->currentSystem] = 0;  // g(x) of the origin system is 0
    open_list.push_back(origin);

    while (!open_list.empty()) {
        // Sort open list to get the lowest f(x) state
        std::sort(open_list.begin(), open_list.end(), compare_states);
        
        State* s_system = open_list.front();   // get the node with the lowest f(x)
        open_list.erase(open_list.begin());
        
        // Debug print
        std::cout << "Expanding system: " << s_system->currentSystem->get_name() 
                  << " (f = " << s_system->heuristic_value << ")" << std::endl;
        
        if (s_system->currentSystem == destination->currentSystem) { // we found a solution
            std::cout << "Solution found: " << s_system->currentSystem->get_name() << std::endl;
            return s_system;
        }
        
        if (closed_systems.find(s_system->currentSystem) != closed_systems.end()) { // already in closed list
            continue;
        }
        closed_systems.insert(s_system->currentSystem);
        
        // Generate successors
        std::vector<State*> heuristics_results = s_system->max_sec_heuristic(g, s_system, destination->currentSystem);
        
        for (State* new_state : heuristics_results) {
            double g_cost = g_values[s_system->currentSystem] + 1; // assume each transition has cost 1
            
            // Debug print for successor
            std::cout << "  Checking successor: " << new_state->currentSystem->get_name() << std::endl;
            
            // If the system has not been visited or if we found a better path
            auto existing_g = g_values.find(new_state->currentSystem);
            if (existing_g == g_values.end() || g_cost < existing_g->second) {
                g_values[new_state->currentSystem] = g_cost;
                new_state->heuristic_value = g_cost + new_state->heuristic_value; // update f(x)
                
                new_state->prev = s_system;

                // Check if already in open list to avoid duplicates
                auto it = std::find_if(open_list.begin(), open_list.end(), 
                    [&new_state](State* state) { 
                        return state->currentSystem == new_state->currentSystem; 
                    });
                
                if (it == open_list.end()) {
                    open_list.push_back(new_state);
                    
                    // Debug print for adding to open list
                    std::cout << "    Added to open list" << std::endl;
                }
            }
        }
        
        // Debug print current open list
        std::cout << "Current Open List: ";
        for (auto& state : open_list) {
            std::cout << state->currentSystem->get_name() << "(" 
                      << state->heuristic_value << ") ";
        }
        std::cout << std::endl << std::endl;
    }
    
    std::cout << "No solution found" << std::endl;
    return nullptr; // return nullptr if no solution found
}

#endif