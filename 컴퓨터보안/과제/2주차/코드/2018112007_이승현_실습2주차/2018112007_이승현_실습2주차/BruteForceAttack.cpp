#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

vector<string> password_set;
vector<string> character_set = { "0123456789",
                                "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ",
                                "!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                "0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ",
                                "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                "0123456789!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                "0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~"
};

vector<string> checked;

int Password_character(int size)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> character(0, size - 1);
    return character(gen);
}

void Make_password()
{
    string password = "";
    for (int i = 0; i < character_set.size(); i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 4; k <= 8; k++)
            {
                for (int l = 0; l < k; l++)
                {
                    password += character_set[i][Password_character(character_set[i].length())];
                }
                password_set.push_back(password);
                password.clear();
            }
        }
    }
    random_shuffle(password_set.begin(), password_set.end());
}

void BruteForceAttack(string password)
{
    for (int i = 0; i < character_set.size(); i++)
    {
        for (int j = 4; j <= 8; j++)
        {
            while (true)
            {
                string brute = "";
                for (int k = 0; k < j; k++)
                {
                    brute += character_set[i][Password_character(character_set[i].length())];
                }
                if (find(checked.begin(), checked.end(), brute) != checked.end() && password == brute)
                {
                    cout << brute << endl;
                    return;
                }
                checked.push_back(brute);
                brute.clear();
            }
        }
    }
}

int main()
{
	Make_password();
    for(auto a : password_set)
        BruteForceAttack(a);
}