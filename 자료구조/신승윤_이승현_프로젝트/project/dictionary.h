#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#define MAX_DOC_NUM 4
#define MOD 127
using namespace std;

typedef struct location{
  string word;
  int doc;
  int index;
}loc;

vector <vector<loc> > table[MOD];
int indexed_word = 0;
int comparison = 0;

string string_preprocess(string str){
  int i=0;
  while(str.length() > i){
    if((65 <= (int)str[i] && (int)str[i]<= 90) || (97 <= (int)str[i] && (int)str[i]<= 122)) break;
    else str = str.substr(i+1, str.length());
    i++;
  }i = str.length()-1;
  while(i>=0){
    if((65 <= (int)str[i] && (int)str[i]<= 90) || (97 <= (int)str[i] && (int)str[i]<= 122)) break;
    else str = str.substr(0,i);
    i--;
  }
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}

long long hashCode(string s){
	long long r = 0;
	long long a = 19; //prime number
	for(int i = 0; i < s.length(); i++)r +=  r*a + s[i];
	return r;
}

int total_indexed_number(){
  int indexed = 0;
  for(int hash=0; hash<MOD; hash++){
    for(int i=0; i<table[hash].size(); i++){
      indexed++;
    }
  }
  return indexed;
}

void dict_print(){
  //vector <vector<loc> > table[MOD];
  for(int hash=0; hash<MOD; hash++){
    cout << hash << " ";
    for(int i=0; i<table[hash].size(); i++){
      cout << table[hash][i][0].word << ", " << table[hash][i].size() << " ";
    }
    printf("\n");
  }
  printf("\n");
}

void dictionary_make(vector <string> text[]){
  long long mod = MOD;
  int word_count = 0;
  for(int i=0; i<MAX_DOC_NUM; i++){
    for(int j=0; j<text[i].size(); j++){
      comparison++;
      string str = string_preprocess(text[i][j]);
      word_count++;
      long long hash_code = hashCode(str);
      int hash = (int)(hash_code%mod);
      loc temp; temp.word =str; temp.doc = i; temp.index = j;
      //cout << hash <<" "<< str <<endl;
      if(table[hash].size() == 0){
        vector<loc> first; first.push_back(temp);
        table[hash].push_back(first);
      }
      else{
        bool find = false;
        for(int h=0; h<table[hash].size(); h++){
          comparison++;
          if((table[hash][h][0].word).compare(str) == 0){
            //collison
            table[hash][h].push_back(temp);
            find = true;
            break;
          }
        }
        if(!find){
          //chaining
          vector<loc> next; next.push_back(temp);
          table[hash].push_back(next);
        }
      }
    }
  }
  //dict_print();
  printf("dictionary maked successful with %d words\n",word_count);
}
