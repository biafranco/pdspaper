#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <sstream>
#include "database.h"

using namespace std;

int main() {

    Database test = Database("./teste_documentos");
    string frase;
    vector<string> pesquisa;
    cout << "pesquisa: ";
    getline(cin, frase);

    string palavra;
    istringstream iss(frase);

    while (iss >> palavra) {
        pesquisa.push_back(palavra);
    }
    
    test.pesquisa(pesquisa);
}
}
