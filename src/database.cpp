#include "../include/database.h"
#include <algorithm>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <locale>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

Database::Database(string path) {
  DIR *directory = opendir(path.c_str());

  if (directory == nullptr) {
    cerr << "Erro ao abrir o diretório: " << path << endl;
    return;
  }

  struct dirent *entry;

  while ((entry = readdir(directory)) != nullptr) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    string nomeArquivo = entry->d_name;
    ProcessTextFile(path, nomeArquivo);
  }

  closedir(directory);
}

void Database::ProcessTextFile(const string path, const string &nomeArquivo) {

  string caminhoArquivo = path + "/" + nomeArquivo;
  ifstream file(caminhoArquivo);
  if (file.is_open()) {
    string line;
    int documentoID = 1;
    while (getline(file, line)) {
      string a = line;
       std::regex regex("[^a-zA-Z]");
        a = std::regex_replace(line, regex, "");
      string textoNormalizado = Normaliza(line);

      vector<string> palavras;
      istringstream iss(textoNormalizado);
      string palavra;

      while (iss >> palavra) {
        _indice[palavra]
               [nomeArquivo]++; // Incrementa a contagem da palavra no arquivo
      }

      documentoID++;
    }

    file.close();
  } else {
    cerr << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
  }
}

string RemoveAcentos(const string &texto) {
  string a = texto;

  for (char& c : a) {
        c = std::tolower(c);
    }
    
 std::regex regex("[^a-zA-Z]");
  a = std::regex_replace(texto, regex, "");
  return a;
}

string Database::Normaliza(string texto) {
  string normalizada;
  string noAcentos;
  noAcentos = RemoveAcentos(texto);

  for (char c : texto) {
    if ((c >= 97 && c <= 122) || c == 32) {
      normalizada += c;
    } else if (c >= 65 && c <= 90) {
      normalizada += tolower(c);
    } else if (c == 10) {
      c = 32;
      normalizada += c;
    }
  }

  return normalizada;
}

void Database::Pesquisa(const vector<string> &palavras) {
  for (const auto &palavra : palavras) {

    cout << palavra << ":" << endl;
    int _a = 0;
    if (_indice[palavra].size()) {
      for (const auto &entry : _indice[palavra]) {
        _a++;
        int contador = pegaIndicePalRep(palavra, entry.first);
        cout << "(" << entry.first << ", " << contador << ")";
        if (_a >= _indice[palavra].size())
          cout << endl;
        else
          cout << ", ";
      }
    } else {
      cout << "Palavra não encontrada";
    }
    _a = 0;
    cout << endl;
  }
}

int Database::pegaIndicePalRep(const string &palavra, const string &arquivo) {
  if (_indice.find(palavra) != _indice.end() &&
      _indice[palavra].find(arquivo) != _indice[palavra].end()) {
    return _indice[palavra][arquivo];
  }
  return 0;
}

Database::~Database() {}
