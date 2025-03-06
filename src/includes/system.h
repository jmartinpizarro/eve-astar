#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class System {
    private:
        string system_name;
        float system_security;
        unordered_map<string, System*> adjacent_systems;
        unordered_map<System*, double> distance_to_adj_system;
    
    public:
        // constructor
        System(string name, float security)
        : system_name(name) {
            set_security(security);
        }

        // for compairing other systems
        bool operator==(const System& other) const {
            return system_name == other.system_name;
        }

        int set_name(string name){
            system_name = name;
            return 0;
        }
        
        string get_name() const {
            return system_name;
        }

        unordered_map<string, System*> get_adjacent_systems() const {
            return adjacent_systems;
        }

        unordered_map<System*, double> get_adjacent_systems_distance() const {
            return distance_to_adj_system;
        }

        double get_adjacent_system_distance(System* sys) {
            return distance_to_adj_system[sys];
        }

        int add_adjacent_system(string systemName, System* system) {
            adjacent_systems[systemName] = system;
            return 0;
        }

        int add_adjacent_system_distance(System* system, double distance) {
            distance_to_adj_system[system] = distance;
            return 0;
        }

        // for controlling CONCORD Security values
        void set_security(double sec){
            if (sec > 1.0 || sec < -1.0){
                throw out_of_range("Security status must be an float -1.0 < sec < 1.0");
            } else {
                system_security = sec;
            }
        }
};

// define a hashmap for System being a key
namespace std{
    template <>
    struct hash<System> {
        size_t operator()(const System& s) const {
            return hash<string>()(s.get_name());
        }
    };
}

#endif
