#ifndef DATABASE_H_
#define DATABASE_H_

#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

struct ComparaPar {
  bool operator()(const pair<string, int> &p1,
                  const pair<string, int> &p2) const {
    if (p1.second != p2.second) {
      return p1.second < p2.second;
    }
    return p1.first > p2.first;
  }
};

class Database {
public:
  Database(string path);


  void ProcessTextFile(const string path, const string &nomeArquivo);

  string Normaliza(string input);

  void Pesquisa(const vector<string> &palavras);


  int pegaIndicePalRep(const string &palavra, const string &nomeArquivo);

  ~Database();

private:
  map<string, map<string, int>> _indice;
};

#endif
