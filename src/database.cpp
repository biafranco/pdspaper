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
    cerr << "Erro ao abrir o diretorio: " << path << endl;
    path = "pdspaper/documentos"; // Altera o caminho para "pdspaper/documents"
    directory = opendir(path.c_str()); // Tenta abrir o diretório alternativo
    if (directory == nullptr) {
      cerr << "Error ao abrir o diretorio segunda tentativa: " << path << endl;
      return;
    }
  }

  struct dirent *entry;

  while ((entry = readdir(directory)) != nullptr) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    string fileName = entry->d_name;
    ProcessTextFile(path, fileName);
  }

  closedir(directory);
}

void Database::ProcessTextFile(const string path, const string &fileName) {

  string filePath = path + "/" + fileName;
  ifstream file(filePath);
  if (file.is_open()) {
    string line;
    int documentID = 1;
    while (getline(file, line)) {
      string normalizedText = Normalize(line);

      vector<string> words;
      istringstream iss(normalizedText);
      string word;

      while (iss >> word) {
        _index[word][fileName]++; // Increment word count in the file
      }

      documentID++;
    }

    file.close();
  } else {
    cerr << "Erro ao abrir a pasta: " << fileName << endl;
  }
}

string RemoveAccents(const string &text) {
  string result = text;

  for (char &c : result) {
    c = std::tolower(c);
  }

  std::regex regex("[^a-zA-Z]");
  result = std::regex_replace(text, regex, "");
  return result;
}

string Database::Normalize(string text) {
  string normalized;
  string withoutAccents = RemoveAccents(text);

  for (char c : text) {
    if ((c >= 97 && c <= 122) || c == 32) {
      normalized += c;
    } else if (c >= 65 && c <= 90) {
      normalized += tolower(c);
    }
  }

  return normalized;
}

void Database::Search(const vector<string> &words) {
  for (const auto &word : words) {
     cout << word << ":" << endl;
    vector<pair<string, int>> fileCounts(_index[word].begin(),
                                         _index[word].end());
    sort(fileCounts.begin(), fileCounts.end(),
         [](const pair<string, int> &p1, const pair<string, int> &p2) {
           if (p1.second > p2.second) {
             return true;
           } else if (p1.second < p2.second) {
             return false;
           } else {
             return p1.first < p2.first;
           }
         });

    for (const auto &fileCount : fileCounts) {
      cout << "(" << fileCount.first << ", " << fileCount.second << "), ";
    }

    cout << endl;
    cout << "" << endl;
  }
}

Database::~Database() {}