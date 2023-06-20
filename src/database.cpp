#include "../include/database.h"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <dirent.h>

using namespace std;

Database::Database(string path){
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

        while ((entrada = readdir(pasta)) != nullptr) {
            string arquivo = path + "/" + entrada->d_name;
            ProcessTextFile(arquivo);
        }
        // Fecha o diretório
        closedir(pasta);
       
       }
}

void Database::ProcessTextFile(const string& arquivo) {
     
     ifstream file(arquivo);
     if (file.is_open()) {

        ofstream arquivoTemp("temp.txt");

        string line;

        while (getline(file, line)) {
           
            string textoNormalizado = Normaliza(line);
            arquivoTemp << textoNormalizado << endl; 
        }
        // Fechar os arquivos
        file.close();
        arquivoTemp.close();
    
        // Remover o arquivo original
        remove(arquivo.c_str());

        // Renomear o arquivo temporário para o nome original
        rename("temp.txt", arquivo.c_str());

    } else {
        cerr << "Erro ao abrir o arquivo: " << arquivo << std::endl;
    }

}


string Database::Normaliza(string texto) {

    //ASCII 65-90 Maiusculas
    //ASCII 97-122 Minusculas
    //ASCII 32 SPACE

    string normalizada;
    for (char c: texto){
        //registra alfabeto minusculo e espaco simples
        if ((c >= 97 && c <=122) || c == 32){
        normalizada += c;
        }
        //transforma maiuscula em minuscula
        else if (c >= 65 && c <= 90){
            normalizada += tolower(c); 
        } 
        //transforma novas linhas em espaco simples
        else if (c == 10){
            c = 32;
            normalizada += c;
        } //qualquer outro caractere eh ignorado
    };
    
    return normalizada;
}

void Database::Pesquisa(vector<string> palavras){
    map<string, int> base = this->_indice[palavras[0]];
    vector<string> deleta;
    map<string, int>::iterator it;

    for(int i = 1; i < (int)palavras.size(); i++){
        for (it = base.begin(); it != base.end(); ++it) {
            if (this->_indice[palavras[i]].find(it->first) != this->_indice[palavras[i]].end()) {
                it->second += this->_indice[palavras[i]][it->first];
            } else {
                deleta.insert(deleta.begin(), it->first);
            }
        }

        for(int j = 0; j < (int)deleta.size(); j++){
            base.erase(deleta[j]);
        }

        deleta.clear();
    }
    priority_queue<pair<string, int>, vector<pair<string, int>>, ComparaPar> priority;

    for (it = base.begin(); it != base.end(); ++it) {
        priority.push(make_pair(it->first, it->second));
    }

    while(!priority.empty()){
        cout << priority.top().first << endl;
        priority.pop();
    }
}

Database::~Database(){

}
