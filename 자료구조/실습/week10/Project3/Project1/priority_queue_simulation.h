#pragma once
#define MAX_SIMUL_TIME 20 // �ùķ��̼� ���� �ð�
#define MAX_PRINTING_TIME 10 // �� Job�� ������ �ִ� ����Ʈ �ð�
#define JOB_ARRIVAL_PROB 0.5 // �� �ð� ���ο� Job�� ���� Ȯ��
#define boolean unsigned char
#define true 1
#define false 0
#define MAX_PQ_SIZE 1000 // Priority queue size
// �ùķ��̼��� ���� global variables
int current_time = 0; // ���� �ð�
int new_job_id = 0; // ���ο� Job�� ID
int current_job_id; // ���� ����Ʈ�ϰ� �ִ� Job�� ID
int remaining_time; // ���� ����Ʈ�ϰ� �ִ� Job�� ���� ����Ʈ �ð�. �� �ð� 1�� ����
int total_wait_time; // ����Ʈ�� ������ ��� Job�� ���ð�(start time - arrival time)�� ��
int num_printed_jobs; // �ùķ��̼��� ���� ������ ����Ʈ�� ���۵� Job�� �� ��
// Job
typedef struct {
	int key; // Priority queue�� Ű �� (duration�� Ű�� ����)
	int id; // Job ID
	int arrival_time; // Job�� ��û��(������) �ð�
	int duration; // Job�� ����Ʈ �ð�
} Job;
typedef Job Element;

// Global PQ (priority queue): min heap - key��(duration)�� ���� ���� �켱������ ����
Element PQ[MAX_PQ_SIZE];
int PQ_size = 0;
void insert_job(int id, int arrival_time, int duration);
// ID�� id, ��û�ð��� arrival_time, ����Ʈ �ð��� duration�� Job�� ť�� ����
void process_next_job(); // ���� job�� ť���� ���� ����(���� job id, remaining time �� ����)
boolean is_job_arrived(); // �����ϰ� true Ȥ�� false�� return. True�� Ȯ���� JOB_ARRIVAL_PROB
boolean is_printer_idle(); // �����Ͱ� ��� ������(���� job�� remaining time <= 0) true
double random(); // 0.0 - 1.0 ������ ���� ���� ��ȯ
int get_random_duration(); // 1 - MAX_PRINTING_TIME+1 ������ ���� ���� ��ȯ
// PQ�� job ����
void insert_PQ(Element item);
// PQ���� min item (��Ʈ) ���� �� ��ȯ
Element delete_PQ();
// PQ�� job���� key�� id�� ���ʷ� ���
void PQ_show();
boolean is_PQ_empty();