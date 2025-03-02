#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unordered_map>
#include <stdexcept>

#include "includes/system.h"
#include "includes/state.h"

int main(int argc, char* argv[]) {
    try{

        System s1 = {"Alpha", 1.4};
        System s2 = {"Tango", 0.9};
        System s3 = {"Gamma", 0.8};
    
        s1.add_adjacent_system(s2.get_name(), &s2);
        s1.add_adjacent_system(s3.get_name(), &s3);
    
        s1.add_adjacent_system_distance(&s2, 10.1);
        s1.add_adjacent_system_distance(&s3, 1.1456);

        std::cout << "System " << s1.get_name() << " is connected to:\n";
        for (const auto& [name, sys] : s1.get_adjacent_systems()) { // cover all the .keys()
            std::cout << "- " << name << " with distance " << s1.get_adjacent_systems_distance()[sys] << "\n";
        }

        State st1 = {&s1};
        std::cout << "State " << st1.currentSystem->get_name() << "\n";

    } catch (const out_of_range& e) {
        cerr << "Error" << e.what() << "\n";
        return -1;
    }

    return 0;
}