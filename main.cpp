#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unordered_map>

#include "main.h"

int main(int argc, char* argv[]) {
    System s1 = {"Alpha", 1.0, {}, {}};
    System s2 = {"Tango", 2.0, {}, {}};
    System s3 = {"Gamma", 3.0, {}, {}};

    s1.adjacent_systems["Tango"] = &s2;
    s1.adjacent_systems["Gamma"] = &s3;

    s1.distance_to_adj_system[&s2] = 1.5;
    s1.distance_to_adj_system[&s3] = 2.3;

    std::cout << "System " << s1.system_name << " is connected to:\n";
    for (const auto& [name, sys] : s1.adjacent_systems) { // cover all the .keys()
        std::cout << "- " << name << " with distance " << s1.distance_to_adj_system[sys] << "\n";
    }

    return 0;
}