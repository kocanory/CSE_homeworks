#define _CRT_SECURE_NO_WARNINGS
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int t0, t1, t2, t3; //송신 프로세스의 송신 값 저장
int r0, r1, r2, r3; //수신 프로세스의 수신 값 저장
int code_t0[8], code_t1[8], code_t2[8], code_t3[8]; //각 칩 시퀀스 저장
int information[8], t0_s[8], t1_s[8], t2_s[8], t3_s[8]; 
//칩 시퀀스와 송신 값의 곱과 그 값들의 합을 저장할 변수

void input()
{
	printf("Enter Data t0 : ");
	scanf("%d", &t0);               //전송 프로세스 t0의 전송 값 입력

	printf("Enter Data t1 : ");
	scanf("%d", &t1);               //전송 프로세스 t1의 전송 값 입력

	printf("Enter Data t2 : ");
	scanf("%d", &t2);               //전송 프로세스 t2의 전송 값 입력

	printf("Enter Data t3 : ");
	scanf("%d", &t3);               //전송 프로세스 t3의 전송 값 입력

	printf("code_t0 : ");
	for (int i = 0; i < 8; i++)
	{
		scanf("%1d", &code_t0[i]);              //t0의 칩 시퀀스 입력
		if (code_t0[i] == 0) code_t0[i] = -1;   //입력된 값이 0인 경우 -1로 변환
	}

	printf("code_t1 : ");
	for (int i = 0; i < 8; i++) 
	{ 
		scanf("%1d", &code_t1[i]);              //t1의 칩 시퀀스 입력
		if (code_t1[i] == 0) code_t1[i] = -1;   //입력된 값이 0인 경우 -1로 변환
	}

	printf("code_t2 : ");
	for (int i = 0; i < 8; i++)
	{
		scanf("%1d", &code_t2[i]);              //t2의 칩 시퀀스 입력
		if (code_t2[i] == 0) code_t2[i] = -1;   //입력된 값이 0인 경우 -1로 변환
	}

	printf("code_t3 : ");
	for (int i = 0; i < 8; i++)
	{
		scanf("%1d", &code_t3[i]);              //t3의 칩 시퀀스 입력
		if (code_t3[i] == 0) code_t3[i] = -1;   //입력된 값이 0인 경우 -1로 변환
	}
	printf("\n");
}

void info()
{
	for (int i = 0; i < 8; i++)
	{
		t0_s[i] = (t0 * code_t0[i]);            //t0의 칩 시퀀스와 전송 값을 곱함
		t1_s[i] = (t1 * code_t1[i]);            //t1의 칩 시퀀스와 전송 값을 곱함
		t2_s[i] = (t2 * code_t2[i]);            //t2의 칩 시퀀스와 전송 값을 곱함
		t3_s[i] = (t3 * code_t3[i]);            //t3의 칩 시퀀스와 전송 값을 곱함
		information[i] = t0_s[i] + t1_s[i] + t2_s[i] + t3_s[i];
        //각 프로세스 별로 구한 값을 다 더함
	}
}

void recover()
{
	for (int i = 0; i < 8; i++)
	{
		r0 += (information[i] * code_t0[i]); //r0에서 전송 받은 값과 칩 시퀀스의 내적 값을 구함
		r1 += (information[i] * code_t1[i]); //r1에서 전송 받은 값과 칩 시퀀스의 내적 값을 구함
		r2 += (information[i] * code_t2[i]); //r2에서 전송 받은 값과 칩 시퀀스의 내적 값을 구함
		r3 += (information[i] * code_t3[i]); //r3에서 전송 받은 값과 칩 시퀀스의 내적 값을 구함
	}
	r0 /= 8;                                 //r0에서 구한 내적 값에서 칩 시퀀스의 길이를 나눔 -> normalized inner product
	r1 /= 8;                                 //r1에서 구한 내적 값에서 칩 시퀀스의 길이를 나눔 -> normalized inner product
	r2 /= 8;                                 //r2에서 구한 내적 값에서 칩 시퀀스의 길이를 나눔 -> normalized inner product
	r3 /= 8;                                 //r3에서 구한 내적 값에서 칩 시퀀스의 길이를 나눔 -> normalized inner product

	printf("r0 : %d\n", r0);                 //r0에서 수신된 값을 출력
	printf("r1 : %d\n", r1);                 //r1에서 수신된 값을 출력
	printf("r2 : %d\n", r2);                 //r2에서 수신된 값을 출력
	printf("r3 : %d\n", r3);                 //r3에서 수신된 값을 출력
}
int main()
{
	int fd[2];  //file descriptor 저장할 배열
	pid_t pid;  //pid 저장할 변수

	if(pipe(fd) == -1){ //pipe 함수가 제대로 호출되지 않을경우 처리
		printf("pipe error");   //에러 메시지 출력
		exit(1);                //프로그램 종료
	}	

	input();                    //송신 프로세스의 송신 값과 칩 시퀀스 입력
	pid = fork();               //프로세스 복제

	if(pid == -1){              //fork 함수가 제대로 호출되지 않을 경우 
		printf("fork error");   //에러 메시지 출력
		exit(1);                //프로그램 종료
	}
	else if(pid == 0){
		printf("Joiner : ");
		info();                 //각 칩 시퀀스와 송신 값을 곱하고 더함
		for(int i = 0;i<8;i++) printf("%d ", information[i]);   //join된 값을 출력
		printf("\n");
		write(fd[1], information, 32);  //join된 값을 다른 프로세스에 전송
		printf("Send process\n\n");
	}
	else{
		sleep(2);
		printf("Received process\n");
		read(fd[0], information, 32);   //join된 값을 수신
		recover();                      //join된 값을 칩 시퀀스와 normalized inner product를 이용하여 전송된 값을 복구
	}
	return 0;
}