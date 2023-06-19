#ifndef DATABASE_H_ 
#define DATABASE_H_

#include <iostream>
#include <cstring>
#include <map>
#include <dirent.h>
#include <fstream>
#include <vector>
#include <queue>


using namespace std;

class Database {
 public:
  Database(string path);

  string normalize(string input);

  void pesquisa(vector<string> palavras);

  ~Database();

 private:
  map<string, map<string, int>> _indice;
};

#endif