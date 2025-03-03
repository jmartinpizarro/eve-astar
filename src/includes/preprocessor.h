/**
 * This file contains all the functions used for 
 * processing texts files and generating the corresponding
 * output files
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int read_file(string fileRoute){
    string content;
    ifstream file (fileRoute);
    if (!file.is_open()){
        cerr << "Error: the file could not be opened " << fileRoute;
    }
    while (getline(file, content)){
        cout << content  << "\n";
    }
    file.close();

    return 0;
}