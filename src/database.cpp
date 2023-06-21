#include "../include/database.h"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <dirent.h>
#include <sstream>
#include <algorithm>

using namespace std;

Database::Database(string path) {
   // DIR é uma estrutura que representa um diretório em um sistema de 
   // arquivos. Ele contém informações sobre o diretório, como o descritor 
   // de arquivo e a posição atual.

   // dirent é uma estrutura que representa uma entrada de diretório, 
   // ou seja, um arquivo ou diretório individual dentro do diretório 
   // principal. Ela contém informações sobre o nome do arquivo, tipo de 
   // arquivo, tamanho, entre outras propriedades.
    DIR* pasta = opendir(path.c_str());
        
    if (pasta == nullptr) {
        return;
    }

    struct dirent *entrada;
        
    while ((entrada = readdir(pasta)) != nullptr) {
        // Ignora os diretórios pai e atual
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
            continue;
        }

        string arquivo = path + "/" + entrada->d_name;
        ProcessTextFile(arquivo);
    }
    
    // Fecha o diretório
    closedir(pasta);
}

void Database::ProcessTextFile(const string& arquivo) {
    ifstream file(arquivo);
    if (file.is_open()) {
        string line;
        int documentoID = 1;

        while (getline(file, line)) {
            string textoNormalizado = Normaliza(line);

            vector<string> palavras;
            istringstream iss(textoNormalizado);
            string palavra;

            while (iss >> palavra) {
                _indice[palavra][arquivo]++;  // Incrementa a contagem da palavra no arquivo
            }

            documentoID++;
        }
        // Remover o arquivo original
        remove(arquivo.c_str());

        // Renomear o arquivo temporário para o nome original
        rename("temp.txt", arquivo.c_str());

        file.close();   
    } else {
        cerr << "Erro ao abrir o arquivo: " << arquivo << endl;
    }
}


string Database::Normaliza(string texto) {
    //ASCII 65-90 Maiusculas
    //ASCII 97-122 Minusculas
    //ASCII 32 SPACE
    string normalizada;
    
    for (char c: texto) {
        //registra alfabeto minusculo e espaco simples
        if ((c >= 97 && c <=122) || c == 32) {
            normalizada += c;
        }
        else if (c >= 65 && c <= 90) {
        //transforma maiuscula em minuscula
            normalizada += tolower(c); 
        }
        //transforma novas linhas em espaco simples
        else if (c == 10) {
            c = 32;
            normalizada += c;
        } //qualquer outro caractere eh ignorado
    }
    
    return normalizada;
}

void Database::Pesquisa(const vector<string>& palavras) {

  for (const auto& palavra : palavras) {
    
        cout << palavra << ":" << endl;
        int _a = 0;
        if(_indice[palavra].size()){
          for (const auto& entry : _indice[palavra]) {
            _a++;
              int contador = pegaIndicePalRep(palavra, entry.first);
              cout << "(" << entry.first << ", " << contador << ")";
            if(_a >= _indice[palavra].size()) cout << endl;
            else cout << ", ";
          }
        }else{
          cout << "Palavra não encontrada";
        }
    _a = 0;
    cout << endl;
    cout << "" << endl;
    }
}

int Database::pegaIndicePalRep(const string& palavra, const string& arquivo) {
    if (_indice.find(palavra) != _indice.end() && _indice[palavra].find(arquivo) != _indice[palavra].end()) {
        return _indice[palavra][arquivo];
    }
    return 0;
}


Database::~Database() {
}
