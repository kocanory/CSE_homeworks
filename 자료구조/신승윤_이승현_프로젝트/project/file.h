#include <string>
#include <iostream>
#include <fstream>
#define MAX_DOC_NUM 4
using namespace std;


vector <string> file_read(string filePath){
	// read File
  vector <string> temp;
  string word;
	ifstream file(filePath);
	while(file >> word) temp.push_back(word);
	file.close();
  return temp;
}
