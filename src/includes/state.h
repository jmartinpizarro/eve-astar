#ifndef STATE_H
#define STATE_H

#include "system.h"

using namespace std;

class State{
    public:
        System* currentSystem;

        // constructor by default is a nullptr
        State(System* system = nullptr) : currentSystem(system) {}

        bool operator==(const State& other) const {
            if (!currentSystem || !other.currentSystem) {
                return currentSystem == other.currentSystem; // both are nullptr
            }
            return currentSystem->get_name() == other.currentSystem->get_name();
        }

        vector<State*>max_sec_heuristic(System* node, System* destination){
            // HEURISTIC g(x) where it is selected the system with the maximum security
            vector<State*> priority_states_queue = {};
            if (node->get_name() ==  destination->get_name()){
                return {}; // we are at the destination, h(x) = 0
            }
            vector<System*>adjacents;
            for (const auto& [name, system] : node->get_adjacent_systems()){
                adjacents.push_back(system);
            }
            double max = numeric_limits<double>::min();
            System* curr = nullptr;
            for (int i = 0; i < adjacents.size(); i++){
                if (adjacents[i]->get_security() > max) {
                    max = adjacents[i]->get_security();
                    curr = adjacents[i];
                    State* new_s = new State();
                    new_s->currentSystem = curr;
                    priority_states_queue.insert(priority_states_queue.begin(), new_s);
                }
            }
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