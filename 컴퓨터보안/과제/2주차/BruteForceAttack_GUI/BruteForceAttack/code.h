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
    }; //�� �н����� ������ ���ڼ� ����
    vector<string> mode_name = { "Number", "Special", "Alpha", "Number + Special", "Number + Alpha", "Alpha + Special", "Number + Alpha + Special" }; 
    //�н����� ������ ��� ����ϱ� ���� ��Ʈ�� ����
    
    int hashval = 0; //target password�� �ؽ� ���� �����ϱ� ���� ����
    bool check = false; //password�� �˾Ƴ� ��� �Լ��� ���߿� �����ϱ� ���� �÷��� ����

public:

       BruteForce()
       {

       }
       int Password_character(int size)
       {
           random_device rd;                                    
           mt19937 gen(rd());
           uniform_int_distribution<int> digit(0, size - 1);    //���ڼ¿��� ������ ������ �ε����� ������ Ȯ���� �������� ����
           int character = digit(gen);                          //�ε����� ����
           return character;                                    //�ε��� ��ȯ
       }

       int mode(bool Number, bool Alpha, bool Special)
       {
           if (Number && Alpha && Special) return 6;            //�н����� �������� ����, ���ĺ�, Ư������ ��� �������� ���
           else if (Alpha && Special) return 5;                 //�н����� �������� ���ĺ�, Ư������ �������� ���
           else if (Number && Alpha) return 4;                  //�н����� �������� ����, ���ĺ� �������� ���
           else if (Number && Special) return 3;                //�н����� �������� ����, Ư������ �������� ���
           else if (Alpha) return 2;                            //�н����� �������� ���ĺ� �������� ���
           else if (Special) return 1;                          //�н����� �������� Ư������ �������� ���
           else if (Number) return 0;                           //�н����� �������� ���� �������� ���
           else return -1;                                      //�н����� �������� �ƹ��͵� �������� ���� ���, ��� ������ �н����� ���� �����ϵ��� ó��
       }

       vector<string> Make_password(bool Number, bool Alpha, bool Special, System::Windows::Forms::TextBox^ box)
       {
           vector<string> password_set;
           string password = "";
           if (mode(Number, Alpha, Special) != -1)
           { 
               for (int length = 4; length <= 8; length++) //4 ~ 8�ڸ��� �н����� ����
               {
                   for (int count = 0; count < 10; count++) //�� 10���� �н����� ����
                   {
                       for (int index = 0; index < length; index++)
                       {
                           password += character_set[mode(Number, Alpha, Special)][Password_character(character_set[mode(Number, Alpha, Special)].length())];
                           //������ ������ ���� �¿��� �������� ���ڸ� ������ �߰�
                       }
                       password_set.push_back(password);    //���Ϳ� ������� �н����� ����
                       password.clear();    //���ο� �н����带 �����ϱ� ���� �ʱ�ȭ
                   }
               }
               box->Text = "Generating (" + ToGcString(mode_name[mode(Number, Alpha, Special)]) + ") Passwords";
               //GUI�� ������ ������ �н����� ������ �������� ���
           }
           else
           {
               for (int length = 4; length <= 8; length++) //4 ~ 8�ڸ��� �н����� ����
               {
                   for (int charset = 0; charset < character_set.size(); charset++) //��� ������ �н����� ����
                   {
                        for (int count = 0; count < 10; count++) //�� 10���� �н����� ����
                        {                      
                           for (int index = 0; index < length; index++)
                           {
                               password += character_set[charset][Password_character(character_set[charset].length())]; //�������� ��ȸ�ϸ鼭 ���� �¿��� �������� ���ڸ� ������ �߰�
                           }
                           password_set.push_back(password); //���Ϳ� ������� �н����� ����
                           password.clear(); //���ο� �н����带 �����ϱ� ���� �ʱ�ȭ
                        }
                   }
               }
               random_shuffle(password_set.begin(), password_set.end()); //�������� �н����� ����
               box->Text = "Generating All Category Passwords";
               //GUI�� ��� ������ �н����� ������ �������� ���
           }
           return password_set; //������ �н�������� ����� ���� ��ȯ
       }

       void find(int count, int index, string password, string origin, int charset, int characters, string& text)
       {
           if (count == 0)
           {
               int sum = 0;

               for (int i = 0; i < characters; i++)
               {
                   sum += (int)password[i]; //target password�� �ؽð� ���ϱ�
               }

               if (sum == hashval && password == origin)
               {
                   DateTime dt; //�ð��� ����ϱ� ���� Ŭ���� ����
                   text += "[" + ToStdString(dt.Now.ToString("yyyy-MM-dd hh:mm:ss")) + "] " + "Hit! : " + password + ToStdString(Environment::NewLine);
                   //ũ��ŷ�� ���� ������ �ð� ���
                   check = true; //�÷��׸� true�� �����Ͽ� ��������� ȣ���� �Լ��� ��� ����
               }
           }
           else
           {
               for (int j = 0; j < character_set[charset].size(); j++)
               {
                   if (check == true) return; //�÷��װ� true��� �Լ� ����
                   password[index] = character_set[charset][j]; //���� �������� �ε����� �ڸ����� ���� ���� ����
                   find(count - 1, index + 1, password, origin, charset, characters, text); //���� �ε����� ó���ϱ� ���� �Լ� ��������� ȣ��
               }
           }
       }

       void Attack(vector<string> password_set, System::Windows::Forms::TextBox^ box)
       {
           int count = 0; //���� ���° �н����� �������� ����ϱ� ���� ����
           string text = "";  //GUI�� �޼����� ����ϱ� ���� ����
           for (auto pw : password_set) //����� �н����� ��ü ��ȸ
           {
               DateTime dt; //�ð��� ����ϱ� ���� Ŭ���� ����
               auto start = chrono::high_resolution_clock::now(); //���� ���� �ð� ����
               check = false;   //�÷��׸� �ʱ�ȭ
               text += to_string(++count) + "��° Cracking �� Password : " + pw + ToStdString(Environment::NewLine);
               //�н����� �񱳸� ���� target password ���
               text += "[" + ToStdString(dt.Now.ToString("yyyy-MM-dd hh:mm:ss"))+ "] " + to_string(count) + "��° �н����� ���� ����" + ToStdString(Environment::NewLine);
               //�н����� ���� ���� �ð� ���
               hashval = 0; //�ؽð� �ʱ�ȭ
               string password = ""; //������ ���� �� �н����带 ����ϱ� ���� ����
               for (auto c : pw) hashval += (int)c; //target password�� �ؽð� ����

               for (int characters = 4; characters <= 8; characters++) //4 ~ 8�ڸ��� �н����� Ž��
               {
                   for (int charset = 0; charset < character_set.size(); charset++) //��� ������ �н����� Ž��
                   {
                       for (int i = 0; i < characters; ++i) password += character_set[charset][0];
                       //�н����� �ʱ�ȭ
                       find(characters, 0, password, pw, charset, characters, text);
                       //�н����� ���� ����
                       password.clear();
                       //���� �н����� Ž���� ���� �ʱ�ȭ
                       if (check == true) break;
                       //�н����带 ã�� ��� �ݺ������� Ż��
                   }
                   if (check == true) break; //�н����带 ã�� ��� �ݺ������� Ż��
                   cout << endl;
               }

               auto stop = chrono::high_resolution_clock::now();
               auto duration = chrono::duration_cast<chrono::seconds>(stop - start); //�н����� ���� ���� �ð� ����
               text += "Duration of time : " + to_string(duration.count()) + " seconds" + ToStdString(Environment::NewLine + Environment::NewLine);
               //���� ���� �ð��� ���� �ð��� ���� �ҿ�ð� ����
               box->AppendText(ToGcString(text)); //GUI�� �н����� ���� ���� ���
           }
           box->Text += "End Attack"; //������ ���� �������� ���
       }
        private: String^ ToGcString(string std_string) {
              return gcnew String(std_string.data()); //std::string ���� System::String���� ��ȯ
              }                                       //winform���� std::string�� ����� �� ��� System::String���� ��ȯ �ʿ�


        private: string ToStdString(String^ gc_string) {
            using namespace Runtime::InteropServices;
            const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(gc_string)).ToPointer();
            string std_string = chars;
            Marshal::FreeHGlobal(IntPtr((void*)chars));
            return std_string; //System::String�� std::string���� ��ȯ
        }
};