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
/**
 * @brief A* algorithm
 * @param g: Graph. Necessary for calculating the heuristic
 * @param origin, destination: states nodes
 * @return State*. The final node, solution has been found
 */
State* a_star(Graph g, State* origin, State* destination){
    // A* Implementation
    deque<State*> open_list;
    unordered_set<System*> closed_systems; // tracks the systems already visited (not the states)
    
    open_list.push_back(origin);
    
    while (open_list.size() > 0){
        State* s_system = open_list.front();
        open_list.pop_front();

        if (s_system->currentSystem == destination->currentSystem){ // we found a solution
            return s_system;
        }
        
        if (closed_systems.find(s_system->currentSystem) != closed_systems.end()) { // already in closed list, useless
            continue;
        }
        closed_systems.insert(s_system->currentSystem);

        vector<State*> heuristics_results = s_system->max_sec_heuristic(g, s_system, destination->currentSystem);
        for (int i = heuristics_results.size() - 1; i >= 0; i--){
            // if not processed, add it to the open_list
            if (closed_systems.find(heuristics_results[i]->currentSystem) == closed_systems.end()){
                open_list.push_front(heuristics_results[i]);
            }
        }
    }
    return {};
}
#endif