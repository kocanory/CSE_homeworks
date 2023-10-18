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

void XOR(char *a, char *b, char *c)
{
    if ((*b == '0' && *c == '0') || (*b == '1' && *c == '1'))
        *a = '0';   //만약 비교하는 원소가 같은 경우 1
    else
        *a = '1';   //만약 배교하는 원소가 다른 경우 0
}

void division(char *frame, char *generator, char *remainder, int m_len, int g_len, int r_len, int startptr)
{
    bool only_once = true;  //불필요한 계산을 줄이기 위해 xor한 후 첫자리가 1이 나오도록 shift
    int start = startptr;   //시작 인덱스 저장
    for (int i = start; i < (start + g_len); i++)
    {
        XOR(&frame[i], &generator[(i - start )], &frame[i]); //frame과 generator 원소에 대하여 xor 연산
        if ((frame[i] == '0') && only_once == true) startptr++; //첫 자리가 1이 나올때 까지 shift 
        else only_once = false; //첫 자리가 1이 된 경우 shift 중지
    }
    if (m_len - startptr > r_len) division(frame, generator, remainder, m_len, g_len, r_len, startptr); 
    //다음번 연산의 시작 지점에서 끝 지점까지의 원소 개수가 나머지 차수보다 큰 경우, 즉 연산이 더 가능한 경우 연산을 재귀적으로 호출
    else{
        strncpy(remainder, &frame[m_len - r_len], r_len);   //나머지 저장
        remainder[r_len] = '\0';    //끝 부분임을 알리기 위한 null 저장
    }
}

int main(int argc, char *argv[])
{

    string line;
    ifstream in_file(argv[1]);  //input 파일을 불러옴
    if (in_file.is_open())      //파일이 열려있는 경우
    {
        getline(in_file, line);         //첫 번째 줄을 불러옴, 즉 frame을 불러옴
        int input_len = line.length();  //frame의 길이 저장
        char input[input_len + 1];      //frame을 저장할 배열 선언
        strcpy(input, line.c_str());    //frame을 배열에 복사

        getline(in_file, line);             //두 번째 줄을 불러옴, 즉 generator를 불러옴
        int generator_len = line.length();  //generator의 길이 저장
        char polynomial[generator_len + 1]; //generator를 저장할 배열 선언
        strcpy(polynomial, line.c_str());   //generator를 배열에 복사

        int message_len = generator_len + input_len - 1;    //전송할 frame의 길이를 저장
        char temp[message_len] = "";                        //xor 연산을 한 후 결과를 일시적으로 저장할 배열 선언
        char output[message_len + 1] = "";                  //전송할 frame을 출력하기 위한 배열 선언
        strncpy(temp, input, input_len);                    //frame을 temp 배열에 복사
        for (int i = input_len; i < message_len; i++) temp[i] = '0';    //frame 끝에 0을 padding
        strncpy(output, temp, message_len);                 //frame을 output 배열에 복사

        int remainder_len = generator_len - 1;              //remainder의 길이를 저장
        char remainder[remainder_len + 1];                  //remainder를 저장할 배열 선언
        int startptr = 0;                                   //연산을 시작할 인덱스 선언
        while (temp[startptr] == '0') startptr++;           //만약 앞 부분이 0으로 이루어져 있다면 건너뜀

        division(temp, polynomial, remainder, message_len, generator_len, remainder_len, startptr); 
        // frame과 generator에 대하여 연산을 수행함
        for (int i = input_len; i < message_len; i++) output[i] = remainder[i - input_len];
        // frame 뒤에 remainder를 추가함

        print(output, message_len);         //최종으로 전송할 frame을 출력
        print(polynomial, generator_len);   //generator를 출력
        in_file.close();                    //파일 입력 종료
        ofstream out_file("Output.txt");    //파일 출력 시작
        if (out_file.is_open())             
        {
            out_file << output << endl;     //최종으로 전송할 frame을 파일에 기록
            out_file << polynomial << endl; //generator를 파일에 기록
        }
        out_file.close();                   //파일 출력 종료
    }
    return 0;
}