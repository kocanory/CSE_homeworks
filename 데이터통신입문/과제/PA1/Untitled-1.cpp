#include <iostream>
#include <unistd.h>

using namespace std;

int t0, t1, t2, t3;
int code_t0[8], code_t1[8], code_t2[8], code_t3[8];
int information[8], t0_s[8], t1_s[8], t2_s[8], t3_s[8];
int re_t0, re_t1, re_t2, re_t3;

void input()
{
	cout << "Enter Data t0 : ";
	cin >> t0;
	if (t0 == 0) t0 = -1;

	cout << "Enter Data t1 : ";
	cin >> t1;
	if (t1 == 0) t1 = -1;

	cout << "Enter Data t2 : ";
	cin >> t2;
	if (t2 == 0) t2 = -1;

	cout << "Enter Data t3 : ";
	cin >> t3;
	if (t3 == 0) t3 = -1;

	cout << "code_t0 : ";
	for (int i = 0; i < 8; i++) scanf("%1d", &code_t0[i]);

	cout << "code_t1 : ";
	for (int i = 0; i < 8; i++) scanf("%1d", &code_t1[i]);

	cout << "code_t2 : ";
	for (int i = 0; i < 8; i++) scanf("%1d", &code_t2[i]);

	cout << "code_t3 : ";
	for (int i = 0; i < 8; i++) scanf("%1d", &code_t3[i]);
	cout << endl;
}

void info()
{
	for (int i = 0; i < 8; i++)
	{
		t0_s[i] = (t0 * code_t0[i]);
		t1_s[i] = (t1 * code_t1[i]);
		t2_s[i] = (t2 * code_t2[i]);
		t3_s[i] = (t3 * code_t3[i]);
		information[i] = t0_s[i] + t1_s[i] + t2_s[i] + t3_s[i];
	}
	cout << endl;
}

void recover()
{
	for (int i = 0; i < 8; i++)
	{
		re_t0 += (information[i] * code_t0[i]);
		re_t1 += (information[i] * code_t1[i]);
		re_t2 += (information[i] * code_t2[i]);
		re_t3 += (information[i] * code_t3[i]);
	}

	if (re_t0 / (double)8 > 0) re_t0 = 1;
	else re_t0 = 0;

	if (re_t1 / (double)8 > 0) re_t1 = 1;
	else re_t1 = 0;

	if (re_t2 / (double)8 > 0) re_t2 = 1;
	else re_t2 = 0;

	if (re_t3 / (double)8 > 0) re_t3 = 1;
	else re_t3 = 0;

	cout << "Recover t0 : " << re_t0 << endl;
	cout << "Recover t1 : " << re_t1 << endl;
	cout << "Recover t2 : " << re_t2 << endl;
	cout << "Recover t3 : " << re_t3 << endl;
}
int main()
{
	int pipes_parent[2];
	int pipes_child[2];
	
	pid_t pid;
	input();
	info();
	recover();
	return 0;
}