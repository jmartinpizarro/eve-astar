#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <string>
#include <limits>

#include "system.h"

class Graph
{
private:
    unordered_map<string, System *> systems;
    int n_systems;

public:
    System *get_system(const string &name)
    {
        return systems[name];
    }

    int get_n_systems()
    {
        return n_systems;
    }

    System *get_or_create_system(const string &name, double security = 0.0)
    {
        if (systems.find(name) == systems.end())
        {
            systems[name] = new System(name, security);
            n_systems++;
        }
        return systems[name];
    }

    void add_connection(const string &from, const string &to, double distance)
    {
        System *system1 = get_or_create_system(from);
        System *system2 = get_or_create_system(to);

        system1->add_adjacent_system(to, system2);
        system1->add_adjacent_system_distance(system2, distance);
    }

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

    System *closest_to_origin(unordered_map<System *, int> visited, unordered_map<System *, double> distances)
    {
        /* This function returns the closest node to the origin from all the
        nodes that have not been visited yet*/

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

    int dijkstra(System *origin)
    {
        /* Dijkstra Algorithm. Calculates the shortest path to every possible node*/

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
            distances[system] = numeric_limits<int>::max(); // all nodes are unrecheable
        }

        distances[origin] = 0;

        for (int n = 0; n < n_systems; n++)
        { // Dijkstra is going to take 1 iteration per node

            System *u = closest_to_origin(visited, distances); // take the best option (min cost)
            if (u == nullptr)
            {
                break; // no more nodes to study
            }
            visited[u] = 1;

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

        //d_printSolution(previous, distances, origin);

        vector<System*> minimum_path = get_shortest_solution(previous, distances, origin);
        cout << "\tPath: ";
        for (size_t i = minimum_path.size(); i > 0; --i)
        {
            cout << minimum_path[i - 1]->get_name();
            if (i > 1)
                cout << " -> ";
        }
        cout << " with a total jumps of: " << minimum_path.size() << endl;
        return 1;
    }

    void d_printSolution(unordered_map<System *, System *> previous,
                         unordered_map<System *, double> distances,
                         System *origin)
    {

        cout << "Minimum path from system: " << origin->get_name() << endl;

        for (const auto &[name, system] : systems)
        {
            if (distances[system] == numeric_limits<double>::max())
            {
                cout << "No possible path to system " << system->get_name() << endl;
            }
            else
            {
                vector<System *> minimum_path;
                System *prev = system;

                while (prev != nullptr)
                {
                    minimum_path.push_back(prev);
                    prev = previous[prev];
                }
                reverse(minimum_path.begin(), minimum_path.end());

                cout << "\tPath: ";
                for (size_t i = minimum_path.size(); i > 0; --i)
                {
                    cout << minimum_path[i - 1]->get_name();
                    if (i > 1)
                        cout << " -> ";
                }
                cout << " (Total cost: " << distances[system] << ")" << endl;
            }
        }
    }

    vector<System *> get_shortest_solution(unordered_map<System *, System *> previous, unordered_map<System *, double> distances, System *origin)
    {
        // returns the path with the least possible jumps
        double total_jumps = numeric_limits<double>::max();
        vector<System *> minimum_path;

        for (const auto &[name, system] : systems)
        {
            if (distances[system] == numeric_limits<double>::max())
            {
                throw new logic_error("No possible path to system");
            }
            else if (name == origin->get_name())
            {
                continue;
            }
            else
            {
                vector<System *> minimum_local_path;
                System *prev = system;

                while (prev != nullptr)
                {
                    minimum_local_path.push_back(prev);
                    prev = previous[prev];
                }

                double total_local_jumps = minimum_local_path.size();

                if (total_local_jumps <= total_jumps)
                {
                    reverse(minimum_local_path.begin(), minimum_local_path.end());
                    minimum_path = minimum_local_path;
                    total_jumps = total_local_jumps;
                }
            }
        }
        return minimum_path;
    };
};

#endif