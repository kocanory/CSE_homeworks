#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

vector<string> password_set;
vector<string> character_set = {"0123456789", 
                                "!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ",
                                "0123456789!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                "0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ",
                                "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                "0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~"
                                };

int hashval = 0;
bool check = false;

int Password_character(int size)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> digit(0, size - 1);
    int character = digit(gen);
    return character;   
}

void Make_password()
{    
    string password = "";
    for (int count = 0; count < 10; count++)
    {
        for (int length = 4; length <= 8; length++)
        {
            for (int charset = 0; charset < character_set.size(); charset++)
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
    //random_device rd;
    //mt19937 gen(rd());
    //shuffle(password_set.begin(), password_set.end(), gen);
}

void print_processingCharacters(int characters)
{
    switch (characters)
    {
    case 4:
        cout << "Processing 4 word" << endl;
        break;
    case 5:
        cout << "Processing 5 word" << endl;
        break;
    case 6:
        cout << "Processing 6 word" << endl;
        break;
    case 7:
        cout << "Processing 7 word" << endl;
        break;
    case 8:
        cout << "Processing 8 word" << endl;
        break;
    default:
        cout << "Error mode" << endl;
        break;
    }

}
void print_mode(int mode)
{
    switch (mode)
    {
    case 0:
        cout << "incremental mode : Num" << endl;
        break;
    case 1:
        cout << "incremental mode : Special" << endl;
        break;
    case 2:
        cout << "incremental mode : Alpha" << endl;
        break;
    case 3:
        cout << "incremental mode : Num + Special" << endl;
        break;
    case 4:
        cout << "incremental mode : Num + Alpha" << endl;
        break;
    case 5:
        cout << "incremental mode : Alpha + Special" << endl;
        break;
    case 6:
        cout << "incremental mode : ASCII" << endl;
        break;
    default:
        cout << "Error mode" << endl;
        break;
    }
}
void find(int count, int index, string password, string origin, int charset, int characters)
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
            cout << "Hit! : " << password << endl;
            check = true;
        }
    }
    else
    {
        for (int j = 0; j < character_set[charset].size(); j++)
        {
            if (check == true) return;
            password[index] = character_set[charset][j];
            find(count - 1, index + 1, password, origin, charset, characters);
        }
    }
}

void BruteForceAttack()
{
    int count = 0;
    for (auto pw : password_set)
    {
        auto start = chrono::high_resolution_clock::now();
        check = false;
        cout << ++count << "번째 Cracking 할 Password : " << pw << endl;
        cout << count << "번째 패스워드 진행 시작" << endl;
        hashval = 0;
        string password = "";
        for (auto c : pw) hashval += (int)c;

        for (int characters = 4; characters <= 8; characters++)
        {
            print_processingCharacters(characters);
            for (int charset = 0; charset < character_set.size(); charset++)
            {
                for (int i = 0; i < characters; ++i) password += character_set[charset][0];
                print_mode(charset);
                find(characters, 0, password, pw, charset, characters);
                password.clear();
                if (check == true) break;
            }
            if (check == true) break;
            cout << endl;
        }

        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
        cout << "Duration of time : " << duration.count() << " seconds" << endl;
        cout << "#############################################" << endl << endl;
    }
    
}

int main()
{
    Make_password();
    BruteForceAttack();
}