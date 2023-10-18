#include <iostream>
#include <stdio.h>
#include <cstring>
#include <random>
#include <vector>
#include <string>
#include <chrono>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#define PW_LENGTH 8 // 암호 길이
#define NUM_CHARS 94 // 사용 가능한 문자 개수

using namespace std;

vector<string> password_set;
vector<string> character_set = { "0123456789",
                                "!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ",
                                "0123456789!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                "0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ",
                                "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~",
                                "0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ!\"#$%&'()*+,-./:;<=.?@[\\]^_`{|}~"
};

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
    random_shuffle(password_set.begin(), password_set.end());
}

__device__ int strncmp(const char* s1, const char* s2, size_t n) {
    unsigned char uc1, uc2;
    if (n == 0)
        return 0;
    while (n-- > 0 && *s1 == *s2) {
        if (n == 0 || *s1 == '\0')
            return 0;
        s1++;
        s2++;
    }
    uc1 = (*(unsigned char*)s1);
    uc2 = (*(unsigned char*)s2);
    return ((uc1 < uc2) ? -1 : (uc1 > uc2));
}
__device__ void my_strcpy(char* s1, char* s2)
{
    int i = 0;
    for (i = 0; s2[i] != '\0'; i++)
        s1[i] = s2[i];
    s1[i] = '\0';
}

__global__ void bruteForceAttackKernel(char* target, char* result, int *length) {
    // 스레드 인덱스 계산
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    // 가능한 모든 암호를 생성하여 확인
    char pw[PW_LENGTH + 1];
    pw[PW_LENGTH] = '\0';
    for (int i = 0; i < NUM_CHARS; ++i) {
        for (int j = 0; j < NUM_CHARS; ++j) {
            for (int k = 0; k < NUM_CHARS; ++k) {
                for (int l = 0; l < NUM_CHARS; ++l) {
                    pw[0] = i + 33;
                    pw[1] = j + 33;
                    pw[2] = k + 33;
                    pw[3] = l + 33;
                    if (*length == 4 && strncmp(pw, target, 4) == 0) {
                        my_strcpy(result, pw);
                        return;
                    }
                    if (*length > 4)
                    {
                        for (int m = 0; m < NUM_CHARS; ++m)
                        {
                            pw[4] = m + 33;
                            if (*length == 5 && strncmp(pw, target, 5) == 0) {
                                my_strcpy(result, pw);
                                printf("%s\n", pw);
                                return;
                            }
                            if (*length > 5)
                            {
                                for (int n = 0; n < NUM_CHARS; ++n)
                                {
                                    pw[5] = n + 33;
                                    if (*length == 6 && strncmp(pw, target, 6) == 0) {
                                        my_strcpy(result, pw);
                                        return;
                                    }
                                    if (*length > 6)
                                    {
                                        for (int o = 0; o < NUM_CHARS; ++o)
                                        {
                                            pw[6] = o + 33;
                                            if (*length == 7 && strncmp(pw, target, 7) == 0) {
                                                my_strcpy(result, pw);
                                                return;
                                            }
                                            if (*length > 7)
                                            {
                                                for (int p = 0; p < NUM_CHARS; ++p)
                                                {
                                                    pw[7] = p + 33;
                                                    if (*length == 8 && strncmp(pw, target, 8) == 0) {
                                                        my_strcpy(result, pw);
                                                        return;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }                    
                    }
                }
            }
        }
    }
}

int main() {

    Make_password();
    int count = 0;
    for (auto a : password_set)
    {
        auto start = chrono::high_resolution_clock::now(); //공격 시작 시간 저장
        cout << "Cracking Password " << ++count << ": " << a << endl;   //현재 크래킹할 패스워드 출력
        const char* password = a.c_str();   //패스워드를 const char*에 저장
        int strlen = a.length();  //패스워드 길이  저장
        char target[PW_LENGTH + 1]; // 찾을 암호
        strcpy(target, password);   //패스워드 복사
        char result[PW_LENGTH + 1] = ""; // 찾은 암호
        char* d_target, * d_result; //GPU 메모리에 패스워드 데이터를 옮기기 위한 변수
        int* length;    //GPU 메모리에 패스워드 길이 값을 옮기기 위한 변수
        cudaMalloc((void**)&d_target, sizeof(char) * (PW_LENGTH + 1));  //GPU 메모리에 target password를 저장할 메모리 할당
        cudaMalloc((void**)&d_result, sizeof(char) * (PW_LENGTH + 1));  //GPU 메모리에 크래킹 후 결과 값을 저장할 메모리 할당
        cudaMalloc((void**)&length, sizeof(int));   //GPU 메모리에 패스워드 길이를 저장하기 위한 메모리 할당
        cudaMemcpy(d_target, target, sizeof(char) * (PW_LENGTH + 1), cudaMemcpyHostToDevice);   //target password를 GPU 메모리에 복사
        cudaMemcpy(length, &strlen, sizeof(int), cudaMemcpyHostToDevice);   //패스워드 길이를 GPU 메모리에 복사

        int block_size = 256;   //block 사이즈 설정
        int grid_size = (NUM_CHARS * NUM_CHARS * NUM_CHARS * NUM_CHARS + block_size - 1) / block_size; //grid 사이즈 설정
        bruteForceAttackKernel <<<grid_size, block_size >> > (d_target, d_result, length);  //GPU에서 Brute Force Attack 실행
        cudaMemcpy(result, d_result, sizeof(char) * (PW_LENGTH + 1), cudaMemcpyDeviceToHost); //결과 값을 다시 CPU 메모리에 복사
        cudaFree(d_target); //GPU 메모리 반환
        cudaFree(d_result); //GPU 메모리 반환
        std::cout << "Found password: " << result << endl; //결과 값 출력
        auto stop = chrono::high_resolution_clock::now(); //공격 마친 시간 저장
        auto duration = chrono::duration_cast<chrono::seconds>(stop - start); //소요 시간 계산
        cout << "Duration of time : " << duration.count() << " seconds" << endl; //소요시간 출력
        cout << "#############################################" << endl << endl;
    }
    return 0;
}