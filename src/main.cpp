#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> nomesArquivos = {"d1.txt", "d2.txt", "d3.txt"};
    vector<string> arquivosTexto;

    for (const string& nomeArquivo : nomesArquivos) {
        ifstream arquivo(nomeArquivo);

        if (arquivo.is_open()) {
            string conteudo;
            getline(arquivo, conteudo);

            arquivosTexto.push_back(conteudo);

            arquivo.close();
        } 
    }

    for (int i = 0; i < arquivosTexto.size(); i++) {
        cout << arquivosTexto[i] << endl;
    }

    return 0;
}
