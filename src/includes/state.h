#ifndef STATE_H
#define STATE_H

#include "system.h"
#include "graph.h"

using namespace std;
/**
 * @class State
 * @brief Instance of State node, used for the A*
 */
class State{
    public:
        State* prev; // pointer to prev node
        System* currentSystem; // current position of the node
        double heuristic_value; // heuristic value of State

        // constructor by default is a nullptr
        State(State* prev = nullptr, System* system = nullptr) : currentSystem(system) {}

        bool operator==(const State& other) const {
            if (!currentSystem || !other.currentSystem) {
                return currentSystem == other.currentSystem; // both are nullptr
            }
            return currentSystem->get_name() == other.currentSystem->get_name();
        }

        /**
         * @brief Calculates the order of the expanded nodes given the h(x)
         * @param g: Graph. Necessary for calculating the Dijkstra f(x)
         * @param node: State*, current state of the a*
         * @param destination: for calculating the dijkstra path
         * @return vector with the new order of the new expanded nodes
         */
        vector<State*>max_sec_heuristic(Graph g, State* node, System* destination){
            // HEURISTIC g(x) where it is selected the system with the maximum security
            vector<State*> priority_states_queue = {};
            if (node->currentSystem->get_name() ==  destination->get_name()){
                return {}; // we are at the destination, h(x) = 0
            }
            vector<System*>adjacents;
            for (const auto& [name, system] : node->currentSystem->get_adjacent_systems()){
                adjacents.push_back(system);
            }
            for (int i = 0; i < adjacents.size(); i++) {
                double sys_status = adjacents[i]->get_security(); // h1(n) = status
                int r = g.dijkstra(adjacents[i], destination); // h2(n) = dijkstra
            
                // Apply a penalty for systems with low security
                double heuristic_result;
                if (sys_status >= 0.5){
                    heuristic_result = (1 - sys_status);
                } else {
                    double penalty_factor = 10000;  // Strong penalty for low security
                    heuristic_result = fabs(((1 - sys_status) + ((double)r * penalty_factor))); // Dijkstra may return -1 if no path found
                }
                        
                State* new_s = new State();
                new_s->currentSystem = adjacents[i];
                new_s->prev = node;
                new_s->heuristic_value = heuristic_result;
                priority_states_queue.push_back(new_s);
            }
            
            // sort the vector for obtaining the correct order
            std::sort(priority_states_queue.begin(), priority_states_queue.end(),
                      [](State* a, State* b) {
                          return a->heuristic_value < b->heuristic_value;
                      });
                      
            return priority_states_queue;
        }
};

// hash for each state
namespace std{
    template <>
    struct hash<State>{
        size_t operator()(const State& s) const {
            return hash<string>()(s.currentSystem->get_name());
        }
    };
}

#endif