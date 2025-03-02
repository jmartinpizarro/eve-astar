#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct System{
    string system_name;
    float system_security;
    std::vector<unordered_map<string, System*>> adjacent_systems;
    std::vector<unordered_map<System, double>> distance_to_adj_system;

    bool operator==(const System& other) const {
        return system_name == other.system_name && system_security == other.system_security;
    }
};

struct State{
    System currentSystem;
};

#endif // MAIN_H
