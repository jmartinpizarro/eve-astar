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

int process_line(Graph* g, string* content, int* counter){
    string word1, word2, word3;
    System sys = {"", 0.0};
    stringstream s(*content);
    string prev;
    while (getline(s, word1, ',')) {
        if (*counter == 0){
            sys.set_name(word1);
        }
        else if (*counter == 1){
            double concord_security = stod(word1);
            sys.set_security(concord_security);
        }
        else {
            stringstream ss(word1);
            while (getline(ss, word2, '(')){ // obtain the system distance, there is still ')' as last character
                stringstream ss3(word2);
                while (getline(ss3, word3, ')')){
                    if (prev == ""){
                        prev = word3;
                    } else {
                        string distance = word3;
                        cout << prev << "---" << distance << endl;
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