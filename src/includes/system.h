#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct System{
    string system_name;
    float system_security;
    std::unordered_map<string, System*> adjacent_systems;
    std::unordered_map<System*, double> distance_to_adj_system;

    bool operator==(const System& other) const {
        return system_name == other.system_name && system_security == other.system_security;
    }
};

// define a hashmap for System being a key
namespace std{
    template <>
    struct hash<System> {
        size_t operator()(const System& s) const {
            return hash<string>()(s.system_name);
        }
    };
}

#endif
