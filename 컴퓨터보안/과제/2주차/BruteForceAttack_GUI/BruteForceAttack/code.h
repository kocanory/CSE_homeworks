#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <thread>

using namespace std;
using namespace System;

class BruteForce
{
public:
    vector<string> character_set = { "0123456789",
                                    "!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                    "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ",
                                    "0123456789!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                    "0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ",
                                    "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                    "0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~"
    }; //각 패스워드 유형별 문자셋 저장
    vector<string> mode_name = { "Number", "Special", "Alpha", "Number + Special", "Number + Alpha", "Alpha + Special", "Number + Alpha + Special" }; 
    //패스워드 유형별 모드 출력하기 위한 스트링 벡터
    
    int hashval = 0; //target password의 해시 값을 저장하기 위한 변수
    bool check = false; //password를 알아낸 경우 함수를 도중에 중지하기 위한 플래그 변수

public:

       BruteForce()
       {

       }
       int Password_character(int size)
       {
           random_device rd;                                    
           mt19937 gen(rd());
           uniform_int_distribution<int> digit(0, size - 1);    //문자셋에서 가져올 문자의 인덱스를 균일한 확률로 무작위로 선택
           int character = digit(gen);                          //인덱스를 저장
           return character;                                    //인덱스 반환
       }

       int mode(bool Number, bool Alpha, bool Special)
       {
           if (Number && Alpha && Special) return 6;            //패스워드 생성에서 숫자, 알파벳, 특수문자 모두 선택했을 경우
           else if (Alpha && Special) return 5;                 //패스워드 생성에서 알파벳, 특수문자 선택했을 경우
           else if (Number && Alpha) return 4;                  //패스워드 생성에서 숫자, 알파벳 선택했을 경우
           else if (Number && Special) return 3;                //패스워드 생성에서 숫자, 특수문자 선택했을 경우
           else if (Alpha) return 2;                            //패스워드 생성에서 알파벳 선택했을 경우
           else if (Special) return 1;                          //패스워드 생성에서 특수문자 선택했을 경우
           else if (Number) return 0;                           //패스워드 생성에서 숫자 선택했을 경우
           else return -1;                                      //패스워드 생성에서 아무것도 선택하지 않은 경우, 모든 유형의 패스워드 전부 생성하도록 처리
       }

       vector<string> Make_password(bool Number, bool Alpha, bool Special, System::Windows::Forms::TextBox^ box)
       {
           vector<string> password_set;
           string password = "";
           if (mode(Number, Alpha, Special) != -1)
           { 
               for (int length = 4; length <= 8; length++) //4 ~ 8자리의 패스워드 생성
               {
                   for (int count = 0; count < 10; count++) //총 10개의 패스워드 생성
                   {
                       for (int index = 0; index < length; index++)
                       {
                           password += character_set[mode(Number, Alpha, Special)][Password_character(character_set[mode(Number, Alpha, Special)].length())];
                           //선택한 유형의 문자 셋에서 무작위로 문자를 선택해 추가
                       }
                       password_set.push_back(password);    //벡터에 만들어진 패스워드 저장
                       password.clear();    //새로운 패스워드를 생성하기 위해 초기화
                   }
               }
               box->Text = "Generating (" + ToGcString(mode_name[mode(Number, Alpha, Special)]) + ") Passwords";
               //GUI에 선택한 유형의 패스워드 생성이 끝났음을 출력
           }
           else
           {
               for (int length = 4; length <= 8; length++) //4 ~ 8자리의 패스워드 생성
               {
                   for (int charset = 0; charset < character_set.size(); charset++) //모든 유형의 패스워드 생성
                   {
                        for (int count = 0; count < 10; count++) //총 10개의 패스워드 생성
                        {                      
                           for (int index = 0; index < length; index++)
                           {
                               password += character_set[charset][Password_character(character_set[charset].length())]; //유형별로 순회하면서 문자 셋에서 무작위로 문자를 선택해 추가
                           }
                           password_set.push_back(password); //벡터에 만들어진 패스워드 저장
                           password.clear(); //새로운 패스워드를 생성하기 위해 초기화
                        }
                   }
               }
               random_shuffle(password_set.begin(), password_set.end()); //무작위로 패스워드 섞음
               box->Text = "Generating All Category Passwords";
               //GUI에 모든 유형의 패스워드 생성이 끝났음을 출력
           }
           return password_set; //생성한 패스워드들이 저장된 벡터 반환
       }

       void find(int count, int index, string password, string origin, int charset, int characters, string& text)
       {
           if (count == 0)
           {
               int sum = 0;

               for (int i = 0; i < characters; i++)
               {
                   sum += (int)password[i]; //target password의 해시값 구하기
               }

               if (sum == hashval && password == origin)
               {
                   DateTime dt; //시간을 출력하기 위한 클래스 선언
                   text += "[" + ToStdString(dt.Now.ToString("yyyy-MM-dd hh:mm:ss")) + "] " + "Hit! : " + password + ToStdString(Environment::NewLine);
                   //크래킹이 끝난 시점의 시간 출력
                   check = true; //플래그를 true로 지정하여 재귀적으로 호출한 함수들 모두 종료
               }
           }
           else
           {
               for (int j = 0; j < character_set[charset].size(); j++)
               {
                   if (check == true) return; //플래그가 true라면 함수 종료
                   password[index] = character_set[charset][j]; //현재 진행중인 인덱스의 자리에서 문자 값을 변경
                   find(count - 1, index + 1, password, origin, charset, characters, text); //다음 인덱스를 처리하기 위해 함수 재귀적으로 호출
               }
           }
       }

       void Attack(vector<string> password_set, System::Windows::Forms::TextBox^ box)
       {
           int count = 0; //현재 몇번째 패스워드 공격인지 명시하기 위한 벼수
           string text = "";  //GUI에 메세지를 출력하기 위한 변수
           for (auto pw : password_set) //저장된 패스워드 전체 순회
           {
               DateTime dt; //시간을 출력하기 위한 클래스 선언
               auto start = chrono::high_resolution_clock::now(); //공격 시작 시간 저장
               check = false;   //플래그를 초기화
               text += to_string(++count) + "번째 Cracking 할 Password : " + pw + ToStdString(Environment::NewLine);
               //패스워드 비교를 위해 target password 출력
               text += "[" + ToStdString(dt.Now.ToString("yyyy-MM-dd hh:mm:ss"))+ "] " + to_string(count) + "번째 패스워드 진행 시작" + ToStdString(Environment::NewLine);
               //패스워드 공격 시작 시간 출력
               hashval = 0; //해시값 초기화
               string password = ""; //공격이 끝난 후 패스워드를 출력하기 위한 변수
               for (auto c : pw) hashval += (int)c; //target password의 해시값 저장

               for (int characters = 4; characters <= 8; characters++) //4 ~ 8자리의 패스워드 탐색
               {
                   for (int charset = 0; charset < character_set.size(); charset++) //모든 유형의 패스워드 탐색
                   {
                       for (int i = 0; i < characters; ++i) password += character_set[charset][0];
                       //패스워드 초기화
                       find(characters, 0, password, pw, charset, characters, text);
                       //패스워드 공격 시작
                       password.clear();
                       //다음 패스워드 탐색을 위한 초기화
                       if (check == true) break;
                       //패스워드를 찾은 경우 반복문에서 탈출
                   }
                   if (check == true) break; //패스워드를 찾은 경우 반복문에서 탈출
                   cout << endl;
               }

               auto stop = chrono::high_resolution_clock::now();
               auto duration = chrono::duration_cast<chrono::seconds>(stop - start); //패스워드 공격 끝난 시간 저장
               text += "Duration of time : " + to_string(duration.count()) + " seconds" + ToStdString(Environment::NewLine + Environment::NewLine);
               //공격 시작 시간과 끝난 시간의 차로 소요시간 연산
               box->AppendText(ToGcString(text)); //GUI에 패스워드 공격 과정 출력
           }
           box->Text += "End Attack"; //공격이 전부 끝났음을 출력
       }
        private: String^ ToGcString(string std_string) {
              return gcnew String(std_string.data()); //std::string 에서 System::String으로 변환
              }                                       //winform에서 std::string을 출력할 수 없어서 System::String으로 변환 필요


        private: string ToStdString(String^ gc_string) {
            using namespace Runtime::InteropServices;
            const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(gc_string)).ToPointer();
            string std_string = chars;
            Marshal::FreeHGlobal(IntPtr((void*)chars));
            return std_string; //System::String을 std::string으로 변환
        }
};