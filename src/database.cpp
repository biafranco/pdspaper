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

    DIR *pasta;
        struct dirent *entrada;

        //Abre o diretório
       if ((pasta = opendir(path.c_str())) != nullptr) {
        // Lê cada arquivo presente no diretório
        while ((entrada = readdir(pasta)) != nullptr) {
            string arquivo = path + "/" + entrada->d_name;
            processTextFile(arquivo);
        }
        // Fecha o diretório
        closedir(pasta);
       
       } else {
        cerr << "Erro ao abrir o diretório: " << path << endl;
       }
}

void Database::processTextFile(const string& arquivo) {
     
     ifstream file(arquivo);
     if (file.is_open()) {

        ofstream arquivoTemp("temp.txt");

        string line;

        while (getline(file, line)) {
           
            string textoNormalizado = normalize(line);
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


string Database::normalize(string texto) {

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
