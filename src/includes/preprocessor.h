/**
 * This file contains all the functions used for 
 * processing texts files and generating the corresponding
 * output files
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "system.h"
#include "graph.h"

using namespace std;

int process_line(Graph* g, string* content, int* counter) {
    string word1, word2, word3;
    stringstream s(*content);
    string prev;
    System* sys = nullptr;

    while (getline(s, word1, ',')) {
        if (*counter == 0) {
            sys = g->get_or_create_system(word1);
        }
        else if (*counter == 1) {
            double concord_security = stod(word1);
            sys->set_security(concord_security);
        }
        else {
            stringstream ss(word1);
            while (getline(ss, word2, '(')) { 
                stringstream ss3(word2);
                while (getline(ss3, word3, ')')) {
                    if (prev.empty()) {
                        prev = word3;
                    } else {
                        double distance = stod(word3);
                        g->add_connection(sys->get_name(), prev, distance);
                        prev.clear();
                    }
                }
            }
        }
        (*counter)++;
    }
    return 0;
}


Graph read_file(string fileRoute, string* origin, string* destination){

    Graph g;

    ifstream file (fileRoute);
    if (!file.is_open()){
        throw ios::failure("Error: the file could not be opened " + fileRoute);
    }

    if (!getline(file, *origin) || !getline(file, *destination)) {
        throw ios::failure("Error: the file does not have enough lines.");
    }

    string content;
    string system, security;

    int c = 0;

    while (getline(file, content)){ // obtain the line
        process_line(&g, &content, &c); // process the line
        c = 0;
    }
    file.close();
    return g;
}