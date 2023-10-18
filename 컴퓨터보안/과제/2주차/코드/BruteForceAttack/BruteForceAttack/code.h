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
    };
    int hashval = 0;
    bool check = false;

public:

       BruteForce()
       {

       }
       int Password_character(int size)
       {
           random_device rd;
           mt19937 gen(rd());
           uniform_int_distribution<int> digit(0, size - 1);
           int character = digit(gen);
           return character;
       }

       vector<string> Make_password()
       {
           vector<string> password_set;
           string password = "";
           for (int length = 4; length <= 8; length++)
           {
               for (int charset = 0; charset < character_set.size(); charset++)
               {
                   for (int count = 0; count < 10; count++)
                   {
                        for (int index = 0; index < length; index++)
                       {
                           password += character_set[charset][Password_character(character_set[charset].length())];
                       }
                       password_set.push_back(password);
                       password.clear();
                   }
               }
           }
           return password_set;
       }

       void find(int count, int index, string password, string origin, int charset, int characters, string& text)
       {
           if (count == 0)
           {
               int sum = 0;

               for (int i = 0; i < characters; i++)
               {
                   sum += (int)password[i];
               }

               if (sum == hashval && password == origin)
               {
                   DateTime dt;
                   text += "[" + ToStdString(dt.Now.ToString("yyyy-MM-dd hh:mm:ss")) + "] " + "Hit! : " + password + ToStdString(Environment::NewLine);
                   check = true;
               }
           }
           else
           {
               for (int j = 0; j < character_set[charset].size(); j++)
               {
                   if (check == true) return;
                   password[index] = character_set[charset][j];
                   find(count - 1, index + 1, password, origin, charset, characters, text);
               }
           }
       }

       void Attack(vector<string> password_set, System::Windows::Forms::TextBox^ box)
       {
           int count = 0;
           string text = "";
           for (auto pw : password_set)
           {
               DateTime dt;
               auto start = chrono::high_resolution_clock::now();
               check = false;
               text += to_string(++count) + "번째 Cracking 할 Password : " + pw + ToStdString(Environment::NewLine);
               text += "[" + ToStdString(dt.Now.ToString("yyyy-MM-dd hh:mm:ss"))+ "] " + to_string(count) + "번째 패스워드 진행 시작" + ToStdString(Environment::NewLine);
               hashval = 0;
               string password = "";
               for (auto c : pw) hashval += (int)c;

               for (int characters = 4; characters <= 8; characters++)
               {
                   for (int charset = 0; charset < character_set.size(); charset++)
                   {
                       for (int i = 0; i < characters; ++i) password += character_set[charset][0];
                       find(characters, 0, password, pw, charset, characters, text);
                       password.clear();
                       if (check == true) break;
                   }
                   if (check == true) break;
                   cout << endl;
               }

               auto stop = chrono::high_resolution_clock::now();
               auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
               text += "Duration of time : " + to_string(duration.count()) + " seconds" + ToStdString(Environment::NewLine + Environment::NewLine);
               box->AppendText(ToGcString(text));
           }
       }
        private: String^ ToGcString(string std_string) {
              return gcnew String(std_string.data());
              }


        private: string ToStdString(String^ gc_string) {
            using namespace Runtime::InteropServices;
            const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(gc_string)).ToPointer();
            string std_string = chars;
            Marshal::FreeHGlobal(IntPtr((void*)chars));
            return std_string;
        }
};

