#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct System{
    string system_name;
    float system_security;
    std::vector<unordered_map<string, System>> adjacent_systems;
    std::vector<unordered_map<System, int>> distance_to_adj_system;
};

struct State{
    System currentSystem;
};

#endif // MAIN_H
