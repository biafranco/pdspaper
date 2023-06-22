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

struct ComparePair {
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

  void ProcessTextFile(const string path, const string &fileName);

  string Normalize(string input);

  void Search(const vector<string> &words);

  int GetWordCount(const string &word, const string &fileName);

  ~Database();

private:
  map<string, map<string, int>> _index;
};

#endif
