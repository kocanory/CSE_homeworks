#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>

using namespace std;

void XOR(char* a, char* b, char* c)
{
    if ((*b == '0' && *c == '0') || (*b == '1' && *c == '1'))
        *a = '0';
    else
        *a = '1';
}

void division(char* message, char* generator, char* remainder, int m_len, int g_len, int r_len, int startptr)
{
    bool only_once = true;
    int start = startptr;
    for (int i = start; i < start + g_len; i++)
    {
        XOR(&message[i], &generator[(i - start)], &message[i]);
        if ((message[i] == '0') && only_once == true) startptr++;
        else only_once = false;
    }

    if (m_len - startptr > r_len) division(message, generator, remainder, m_len, g_len, r_len, startptr);
    strncpy(remainder, &message[m_len - r_len], r_len);
}
int main()
{
    string line;
    ifstream in_file("input.txt");
    if (in_file.is_open())
    {
        getline(in_file, line);
        int i_len = line.length();
        char input_msg[i_len];
        strcpy(input_msg, line.c_str());
        getline(in_file, line);
        int k_len = line.length();
        char polynomial[k_len + 1];
        strcpy(polynomial, line.c_str());
        int msg_length = k_len + i_len - 1;
        char new_msg[msg_length];
        char output_msg[msg_length + 1] = "";
        strncpy(new_msg, input_msg, i_len);
        for (int i = i_len; i < msg_length; i++) new_msg[i] = '0';
        int r_len = k_len - 1;
        char remainder[r_len];
        int tempptr = 0;
        while (new_msg[tempptr] == '0') tempptr++;
        division(new_msg, polynomial, remainder, msg_length, k_len, r_len, tempptr);
        for (int i = i_len; i < msg_length; i++) output_msg[i] = remainder[i - i_len];
        in_file.close();
        ofstream out_file("output.txt");
        if (out_file.is_open())
        {
            out_file << output_msg << endl;
            out_file << polynomial << endl;
        }
    }
    return 0;
}