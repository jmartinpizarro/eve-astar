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