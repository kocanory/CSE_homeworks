#include <iostream>
#include <fstream>
#include <string>
using namespace std;
 
struct Players{
	string name, position1, position2;
    int ascore, pscore;
};
 
 int main(){
	string filename, pname, p1, p2;
    int ps;
    struct Players record[100];

	cout << "파일 이름 입력 (.txt를 포함하세요) : " << endl;
	cin >> filename;
    ifstream  ifs(filename);

    if(ifs.fail()) {
        cout << "파일 입력 오류입니다. 파일 이름 확인하세요." << endl;
		exit(1);
     }

    int i = 0; 
	while(!ifs.eof()){
     	ifs >> pname >> p1 >> p2 >> ps;
		record[i].name = pname;
		record[i].position1 = p1;
		record[i].position2 = p2;
		record[i].pscore = ps;
		i++;
	}

	cout << "-------------------------------------------" << endl;
	cout << "데이터에서 " << i << "명이 있다." << endl;
	cout << "-------------------------------------------" << endl;
	cout << "이름 | 주 포지션 | 부 포지션 | 포지션 점수" << endl;
	cout << "-------------------------------------------" << endl;
	for(int j = 0; j < i; j++){
		cout << record[j].name << "   " << record[j].position1 << "    " << record[j].position2 << "        " << record[j].pscore << endl;
	}
	cout << "-------------------------------------------" << endl;
}