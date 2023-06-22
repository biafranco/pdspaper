#include <iostream>
#include <vector>
#include <sstream>
#include "../include/database.h"

using namespace std;

int main() {
    Database data = Database("documentos");
    string input;                   // Entrada usuario
    
    vector<string> searchArray;
    cout << "Digite as palavras para pesquisar: ";
    getline(cin, input);

    string word;
    istringstream iss(input);

    while (iss >> word) {
        searchArray.push_back(word);
    }

    data.Search(searchArray);
    return 0;
}
