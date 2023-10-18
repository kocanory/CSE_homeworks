#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

vector<string> password_set;
vector<string> character_set = {"0123456789", 
                                "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ",
                                "!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                "0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ",
                                "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                "0123456789!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                "0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~"
                                };

int Password_character(int size)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> digit(0, size - 1);
    int character = digit(gen);
    cout << character << endl;
    return character;   
}

void Make_password()
{    
    string password = "";
    for(int i = 0; i < 10; i++)
    {
        for(int j = 4; j <= 8; j++)
        {
            for(int k = 0; k < j; k++)
            {
                int index = Password_character(character_set[0].length());
                password += character_set[0][index];
            }
            password_set.push_back(password);
            password.clear();
        }
    }
}

int main()
{
    Make_password();
}