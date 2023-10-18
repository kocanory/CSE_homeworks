#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "btree.h"
#include "file.h"
#include "dictionary.h"
using namespace std;

string doc_path[10] = {"D:\document1.txt",
                      "D:\document2.txt",
                      "D:\document3.txt",
                      "D:\document4.txt",};
vector <string> document[10];

int main(){
  for(int i=0; i<MAX_DOC_NUM; i++) document[i] = file_read(doc_path[i]);
  printf("==file loaded==\n");
  dictionary_make(document);
  printf("\n===============================\n");
  printf("Total Number of document : %d\n", MAX_DOC_NUM);
  printf("Total Number of indexed word : %d\n",total_indexed_number());
  printf("Total Number of comparison : %d\n",comparison);
  printf("===============================\n\n");
  while(true){
    int compare = 0;
    string search_word; printf("word > ");
    cin >> search_word;

    search_word = string_preprocess(search_word);
    long long hash_code = hashCode(search_word);
    int hash = (int)(hash_code%MOD);
    vector <loc> word_in_doc[MAX_DOC_NUM];
    pair<int,int> word_num_in_doc[MAX_DOC_NUM];

    //searching
    for(int w=0; w<table[hash].size(); w++){
      compare++;
      if((table[hash][w][0].word).compare(search_word)==0){
        for(int l = 0; l<table[hash][w].size(); l++){
          word_num_in_doc[table[hash][w][l].doc].first +=1;
          word_num_in_doc[table[hash][w][l].doc].second = table[hash][w][l].doc;
          loc temp;
          temp.word = search_word;
          temp.doc = table[hash][w][l].doc;
          temp.index = table[hash][w][l].index;
          word_in_doc[table[hash][w][l].doc].push_back(temp);
        }
        break;
      }
    }
    sort(word_num_in_doc, word_num_in_doc+MAX_DOC_NUM);

    //print
    bool isWord = false;
    for(int i=MAX_DOC_NUM-1;i>=0; i--){
      if(word_num_in_doc[i].first > 0){
        isWord = true;
        cout << "\n" <<"<document" << word_num_in_doc[i].second + 1 <<".txt> "<< search_word << " : " << word_num_in_doc[i].first<<endl;
        for(auto e : word_in_doc[word_num_in_doc[i].second]){
          int idx = e.index; int docx= e.doc;
          if(idx-4 >=0) cout << ". . . ";
          for(int i=3; i>0; i--){
            if(idx-i >=0) cout << document[docx][idx-i] << " ";
          }
          cout << document[docx][idx] << " ";
          for(int i=1; i<=3; i++){
            if(idx+i < document[docx].size()) cout << document[docx][idx+i] << " ";
          }
          if(idx+4 < document[docx].size()) cout << ". . . ";
          printf("\n");
        }
      }
    }
    if(!isWord) printf("  No such word!  ");
    printf("\n----------------------------------\n");
    printf("total number of comparison : %d\n",compare);
    printf("----------------------------------\n\n");
  }
  return 0;
}
