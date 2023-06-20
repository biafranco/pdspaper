#include <iostream>
#include <vector>
#include <sstream>

#include "../include/database.h"
#include <iostream>
=======
#include "database.h"

using namespace std;

int main(){
   
    Database data = Database("./teste_doc");
    string input;                   //entrada do usuário
    
    vector<string> searchArray;
    cout << "Digite palavras para pesquisar: ";
    getline(cin, input);

    string word;
    istringstream iss(input);

    while (iss >> word) {
        searchArray.push_back(word);
    }
    
    data.pesquisa(searchArray);
    return 0;
}


