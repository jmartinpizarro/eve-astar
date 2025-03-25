#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

using namespace std;
/**
 * @class System
 * @brief Represents a System entity
 */
class System {
    private:
        string system_name; // system name
        float system_security; // system security status
        unordered_map<string, System*> adjacent_systems; // adjacent systems 
        unordered_map<System*, double> distance_to_adj_system; // distance to travel (AU) to adjacent systems
    
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

        /**
         * @brief sets the name of the system
         * @param name the future name of the system
         */
        int set_name(string name){
            system_name = name;
            return 0;
        }
        
        /**
         * @brief gets the system name (private attribute)
         * @return system_name 
         */
        string get_name() const {
            return system_name;
        }

        /**
         * @brief sets the system security status (private attribute)
         * @param sec security value for that system
         * @return void 
         */
        void set_security(double sec){
            if (sec > 1.0 || sec < -1.0){
                throw out_of_range("Security status must be an float -1.0 < sec < 1.0");
            } else {
                system_security = sec;
            }
        }

        /**
         * @brief gets the system security status (private attribute)
         * @return system_security 
         */
        double get_security() const {
            return system_security;
        }

        /**
         * @brief gets the adjacent systems atribute (private attribute)
         * @return adjacent_system (u_map) 
         */
        unordered_map<string, System*> get_adjacent_systems() const {
            return adjacent_systems;
        }

        /**
         * @brief gets the distance of the adjacent systems atribute (private attribute)
         * @return distance_to_adj_system (u_map)
         */
        unordered_map<System*, double> get_adjacent_systems_distance() const {
            return distance_to_adj_system;
        }

        /**
         * @brief gets the adjacent distance to an adjacent System (private attribute)
         * @param sys the adjacent system to research for
         * @return distance (double)
         */
        double get_adjacent_system_distance(System* sys) {
            return distance_to_adj_system[sys];
        }

        /**
         * @brief add an adjacent system to a System (private attribute)
         * @param systemName the adjacent system name
         * @param system a pointer to system 
         * @return 0
         */
        int add_adjacent_system(string systemName, System* system) {
            adjacent_systems[systemName] = system;
            return 0;
        }

        /**
         * @brief add an adjacent system distance to a System (private attribute)
         * @param system a pointer to system 
         * @param distance distance to add to that system
         * @return 0
         */
        int add_adjacent_system_distance(System* system, double distance) {
            distance_to_adj_system[system] = distance;
            return 0;
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
