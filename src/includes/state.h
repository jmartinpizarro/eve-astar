#ifndef STATE_H
#define STATE_H

#include "system.h"

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

        System* max_sec_heuristic(System* node, System* destination){
            // HEURISTIC g(x) where it is selected the system with the maximum security
            if (node->get_name() ==  destination->get_name()){
                return 0;
            }
            vector<System*>adjacents;
            for (const auto& [name, system] : node->get_adjacent_systems()){
                adjacents.push_back(system);
            }
            double max = numeric_limits<double>::min();
            System* curr;
            for (int i = 0; i < adjacents.size(); i++){
                if (adjacents[i]->get_security() > max) {
                    max = adjacents[i]->get_security();
                    curr = adjacents[i];
                }
            }
            return curr;
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