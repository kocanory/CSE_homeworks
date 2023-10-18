#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

void print(char *array, int length)
{
    for (int i = 0; i < length; i++)
        cout << array[i];   //문자열의 원소를 출력
    cout << endl;    
}

int main(int argc, char *argv[])
{
    int bitNo;  //비트를 바꿀 인덱스를 저장할 변수 선언
    string line;

    for (int i = 0; i < argc; i++) bitNo = atoi(argv[i]); //입력받은 인수를 정수로 바꿔 저장    
    getline(cin, line);             //frame을 입력 받음
    int input_len = line.length();  //frame의 길이 저장
    char input_msg[input_len + 1];  //frame을 저장할 배열 선언
    strcpy(input_msg, line.c_str());//frame을 배열에 복사
    
    getline(cin, line);             //generator를 입력받음
    int generator_len = line.length(); //generator의 길이 저장
    if(bitNo < generator_len + input_len){  //만약 입력받은 인덱스가 전송할 frame 내에 있는 경우
        if (input_msg[bitNo - 1] == '1')
            input_msg[bitNo - 1] = '0';     //1을 0으로 변경
        else
            input_msg[bitNo - 1] = '1';     //0을 1로 변경
    }
    print(input_msg, input_len);            //변경된 frame을 출력
    cout << line;                           //generator를 출력
    return 0;
}