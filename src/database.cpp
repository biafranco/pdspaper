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
    map<string, int> indicePalavra = this->_indice[palavras[0]];
    vector<string> deletadas;
    map<string, int>::iterator it;

    priority_queue<pair<string, int>, vector<pair<string, int>>, ComparaPar> filaPrioridade;

    for(int i = 1; i < (int)palavras.size(); i++){

        for (it = indicePalavra.begin(); it != indicePalavra.end(); ++it) {
            filaPrioridade.push(make_pair(it->first, it->second));

            if (this->_indice[palavras[i]].find(it->first) != this->_indice[palavras[i]].end()) {
                it->second += this->_indice[palavras[i]][it->first];
            } 
            else {
                deletadas.insert(deletadas.begin(), it->first);
            }
        }

        for(int j = 0; j < (int)deletadas.size(); j++){
            indicePalavra.erase(deletadas[j]);
        }

        deletadas.clear();
    }

    while(!filaPrioridade.empty()){
        cout << filaPrioridade.top().first << endl;
        filaPrioridade.pop();
    }
}

Database::~Database(){

}
