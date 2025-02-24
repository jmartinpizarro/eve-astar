#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <vector>

struct System{
    char* system_name;
    float system_security;
    std::vector<std::string> adjacent_systems;
};

#endif // MAIN_H
