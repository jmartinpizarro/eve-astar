/* A* Search Algorithm
1.  Initialize the open list
2.  Initialize the closed list
    put the starting node on the open 
    list (you can leave its f at zero)
3.  while the open list is not empty
    a) find the node with the least f on 
       the open list, call it "q"
    b) pop q off the open list
  
    c) generate q's 8 successors and set their 
       parents to q
   
    d) for each successor
        i) if successor is the goal, stop search
        
        ii) else, compute both g and h for successor
          successor.g = q.g + distance between 
                              successor and q
          successor.h = distance from goal to 
          successor (This can be done using many 
          ways, we will discuss three heuristics- 
          Manhattan, Diagonal and Euclidean 
          Heuristics)
          
          successor.f = successor.g + successor.h
        iii) if a node with the same position as 
            successor is in the OPEN list which has a 
           lower f than successor, skip this successor
        iV) if a node with the same position as 
            successor  is in the CLOSED list which has
            a lower f than successor, skip this successor
            otherwise, add  the node to the open list
     end (for loop)
  
    e) push q on the closed list
    end (while loop)
*/

#ifndef A_STAR_H
#define A_STAR_H

#include "system.h"
#include "state.h"
#include <unordered_set>

#include <queue>  // for priority_queue
#include <unordered_map>  // for tracking g(x) values

/**
 * @brief A* algorithm
 * @param g: Graph. Necessary for calculating the heuristic
 * @param origin, destination: states nodes
 * @return State*. The final node, solution has been found
 */
State* a_star(Graph g, State* origin, State* destination) {
    // A* Implementation
    auto compare = [](State* a, State* b) {
        return a->heuristic_value > b->heuristic_value; // Priority queue based on heuristic value
    };
    
    std::priority_queue<State*, std::vector<State*>, decltype(compare)> open_list(compare);
    std::unordered_map<System*, double> g_values;  // stores g(x) for each system
    std::unordered_set<System*> closed_systems;    // tracks the systems already visited (not the states)
    
    origin->heuristic_value = 0; // starting point heuristic (f(x) = g(x) + h(x))
    g_values[origin->currentSystem] = 0;  // g(x) of the origin system is 0
    open_list.push(origin);
    
    while (!open_list.empty()) {
        State* s_system = open_list.top();   // get the node with the lowest f(x)
        open_list.pop();
        
        if (s_system->currentSystem == destination->currentSystem) { // we found a solution
            return s_system;
        }
        
        if (closed_systems.find(s_system->currentSystem) != closed_systems.end()) { // already in closed list, useless
            continue;
        }
        closed_systems.insert(s_system->currentSystem);
        
        vector<State*> heuristics_results = s_system->max_sec_heuristic(g, s_system, destination->currentSystem);
        for (int i = 0; i < heuristics_results.size(); i++) {
            State* new_state = heuristics_results[i];
            double g_cost = g_values[s_system->currentSystem] + 1; // assume each transition has cost 1 (could be adjusted)
            
            // If the system has not been visited or if we found a greater path
            if (g_values.find(new_state->currentSystem) == g_values.end() || g_cost > g_values[new_state->currentSystem]) {
                g_values[new_state->currentSystem] = g_cost;
                new_state->heuristic_value = g_cost + new_state->heuristic_value; // update f(x) = g(x) + h(x)
                open_list.push(new_state);
            }
        }
    }
    
    return nullptr; // return nullptr if no solution found
}

#endif