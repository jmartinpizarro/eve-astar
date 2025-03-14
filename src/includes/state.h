#ifndef STATE_H
#define STATE_H

#include "system.h"

class State{
    public:
        System* currentSystem;
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