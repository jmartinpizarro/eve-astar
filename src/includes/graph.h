#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <string>
#include <limits>
#include <algorithm>

#include "system.h"
/**
 * @class Graph
 * @brief A Graph instance, made of Systems pointers as nodes.
 */
class Graph
{
private:
    unordered_map<string, System *> systems; // represented as a dict of Systems

public:
    int n_systems; // number of total nodes

    /**
     * @brief get system object given a name
     * @param name the key of the dict
     * @return a System pointer
     */
    System* get_system(const string name)
    {
        return systems[name];
    }

    /**
     * @brief get system object given a name
     * @param name the key of the dict
     * @return a System pointer
     */
    System* get_or_create_system(const string &name, double security = 0.0)
    {
        if (systems.find(name) == systems.end())
        {
            systems[name] = new System(name, security);
            n_systems++;
        }
        return systems[name];
    }

    /**
     * @brief adds an edge to the graph between two systems
     * @param from the key of the dict (origin node)
     * @param to the key of the dict (destination node)
     * @param distance distance (AU)
     * @return void
     */
    void add_connection(const string from, const string to, double distance)
    {
        System *system1 = get_or_create_system(from);
        System *system2 = get_or_create_system(to);

        system1->add_adjacent_system(to, system2);
        system1->add_adjacent_system_distance(system2, distance);
    }

    /**
     * @brief prints the graph data
     * @return void
     */
    void print_graph()
    {
        for (const auto &[name, system] : systems)
        {
            cout << "System " << name << " is connected to:\n";
            for (const auto &[adj_name, adj_system] : system->get_adjacent_systems())
            {
                cout << "\t - " << adj_name << " with distance "
                     << system->get_adjacent_systems_distance()[adj_system] << "\n";
            }
        }
    }

    /**
     * @brief states which is the closest to the origin point (for Dijkstra algorithm)
     * @param visited u_map that states if a system has been visited or not
     * @param distances u_map that states the distances between systems (aka jumps)
     * @return System pointer
     */
    System* closest_to_origin(unordered_map<System *, int> visited, unordered_map<System *, double> distances)
    {
        double min = numeric_limits<int>::max();
        System *sys = nullptr;

        for (const auto &[name, system] : systems)
        {
            if (visited[system] == 0 && distances[system] <= min)
            {
                min = distances[system];
                sys = system;
            }
        }

        return sys;
    }


    /**
     * @brief Dijkstra algorithm
     * @param origin origin system
     * @param destination destination system
     * @return 1 if everything went correct
     */
    int dijkstra(System* origin, System* destination)
    {
        /* Modified Dijkstra Algorithm. Calculates the shortest path between origin and destination */
    
        // if a system has been visited or not
        unordered_map<System *, int> visited;
        for (const auto &[name, system] : systems)
        {
            visited[system] = 0;
        }
        // the previous node in order to conform the path
        unordered_map<System *, System *> previous;
        for (const auto &[name, system] : systems)
        {
            previous[system] = NULL;
        }
    
        // the accumulated distance from the origin to that point
        unordered_map<System *, double> distances;
        for (const auto &[name, system] : systems)
        {
            distances[system] = numeric_limits<double>::max(); // all nodes are unreachable
        }
    
        distances[origin] = 0;
    
        // Early exit check - if origin and destination are the same
        if (origin == destination) {
            cout << "\tPath: " << origin->get_name() << " with a total jumps of: 0" << endl;
            return 0;
        }
    
        for (int n = 0; n < n_systems; n++)
        { // Dijkstra is going to take 1 iteration per node
    
            System *u = closest_to_origin(visited, distances); // take the best option (min cost)
            if (u == nullptr)
            {
                break; // no more nodes to study
            }
            
            visited[u] = 1;
            
            // Early termination if we've processed the destination
            if (u == destination) {
                break;
            }
    
            for (const auto &[name, system] : u->get_adjacent_systems())
            { // for all adjacent systems (name, System*)
                double w = u->get_adjacent_system_distance(system);
                if (visited[system] == 0 && (distances[system] > (distances[u] + w)))
                { // this path is shorter
                    distances[system] = distances[u] + w;
                    previous[system] = u;
                }
            }
        }
    
        // Check if destination is reachable
        if (distances[destination] == numeric_limits<double>::max()) {
            cout << "No possible path from " << origin->get_name() << " to " << destination->get_name() << endl;
            return -1;
        }
    
        // Reconstruct the path from origin to destination
        
        System *prev = destination;
        /*d_printSolution(prev, previous);*/

        vector<System*> minimum_path;
        while (prev != nullptr) {
            minimum_path.push_back(prev);
            prev = previous[prev];
        }
    
        return minimum_path.size();
    }

    /**
     * @brief prints the dijkstra solution
     * @param prev init as the destination, it will do backtracking
     * @param previous u_map that states the backtracking
     * @return void
     */
    void d_printSolution(System* prev,
                        unordered_map<System *, System *> previous)
    {
        vector<System*> minimum_path;
        while (prev != nullptr) {
            minimum_path.push_back(prev);
            prev = previous[prev];
        }
        
        // Reverse the path to get it from origin to destination
        reverse(minimum_path.begin(), minimum_path.end());
    
        cout << "\tPath: ";
        for (size_t i = 0; i < minimum_path.size(); ++i) {
            cout << minimum_path[i]->get_name();
            if (i < minimum_path.size() - 1)
                cout << " -> ";
        }
        cout << " with a total jumps of: " << minimum_path.size() << endl;
        return;
    }
};

#endif