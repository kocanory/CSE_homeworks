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
    //random_device rd;
    //mt19937 gen(rd());
    //shuffle(password_set.begin(), password_set.end(), gen);
}

__device__ int strncmp(const char* s1, const char* s2, size_t n) {
    unsigned char uc1, uc2;
    /* Nothing to compare?  Return zero.  */
    if (n == 0)
        return 0;
    /* Loop, comparing bytes.  */
    while (n-- > 0 && *s1 == *s2) {
        /* If we've run out of bytes or hit a null, return zero
        since we already know *s1 == *s2.  */
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

__global__ void recur(char * target, char* result, int *length, int *count)
{
    if (*length > *count - 1)
    {
        for (int m = 0; m < NUM_CHARS; ++m)
        {
            pw[&count - 1] = m + 33;
            if (*length == *count && strncmp(pw, target, *count) == 0) {
                my_strcpy(result, pw);
                printf("%s\n", pw);
                return;
            }
            *count += 1;
            if(*length > count) recur(target, result, length, count);
            *count -= 1;
        }
    }
}
// CUDA 커널 함수
__global__ void bruteForceAttackKernel(char* target, char* result, int *length, int *count) {
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
                    recur(target, result, length, count);
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
        auto start = chrono::high_resolution_clock::now();
        cout << "Cracking Password " << ++count << ": " << a << endl;
        const char* password = a.c_str();
        int strlen = a.length(), cnt = 5;
        char target[PW_LENGTH + 1]; // 찾을 암호
        strcpy(target, password);
        char result[PW_LENGTH + 1] = ""; // 찾은 암호
        char* d_target, * d_result;
        int* length, *count;
        cudaMalloc((void**)&d_target, sizeof(char) * (PW_LENGTH + 1));
        cudaMalloc((void**)&d_result, sizeof(char) * (PW_LENGTH + 1));
        cudaMalloc((void**)&length, sizeof(int));
        cudaMalloc((void**)&count, sizeof(int));
        cudaMemcpy(d_target, target, sizeof(char) * (PW_LENGTH + 1), cudaMemcpyHostToDevice);
        cudaMemcpy(length, &strlen, sizeof(int), cudaMemcpyHostToDevice);
        cudaMemcpy(count, &cnt, sizeof(int), cudaMemcpyHostToDevice);

        int block_size = 256;
        int grid_size = (NUM_CHARS * NUM_CHARS * NUM_CHARS * NUM_CHARS + block_size - 1) / block_size;
        bruteForceAttackKernel <<<grid_size, block_size >> > (d_target, d_result, length, count);
        cudaMemcpy(result, d_result, sizeof(char) * (PW_LENGTH + 1), cudaMemcpyDeviceToHost);
        cudaFree(d_target);
        cudaFree(d_result);
        std::cout << "Found password: " << result << endl;
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
        cout << "Duration of time : " << duration.count() << " seconds" << endl;
        cout << "#############################################" << endl << endl;
    }
    return 0;
}