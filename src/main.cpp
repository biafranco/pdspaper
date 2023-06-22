#include <iostream>
#include <vector>
#include <sstream>
#include "../include/database.h"

using namespace std;

int main() {
    Database data = Database("documentos");
    string input;                   // entrada do usuário
    
    vector<string> searchArray;
    cout << "Digite palavras para pesquisar: ";
    getline(cin, input);

    string word;
    istringstream iss(input);

    while (iss >> word) {
        searchArray.push_back(word);
    }

    data.Pesquisa(searchArray);
    return 0;
}
