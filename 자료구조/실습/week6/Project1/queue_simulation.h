#pragma once
#define MAX_SIMUL_TIME 20 // �ùķ��̼� ���� �ð�
#define MAX_PRINTING_TIME 5 // �� Job�� ������ �ִ� ����Ʈ �ð�
#define JOB_ARRIVAL_PROB 0.5 // �� �ð� ���ο� Job�� ���� Ȯ��
#define boolean unsigned char
#define true 1
#define false 0
// �ùķ��̼��� ���� global variables
int current_time = 0; // ���� �ð�
int new_job_id = 0; // ���ο� Job�� ID
int current_job_id; // ���� ����Ʈ�ϰ� �ִ� Job�� ID
int remaining_time; // ���� ����Ʈ�ϰ� �ִ� Job�� ���� ����Ʈ �ð�. �� �ð� 1�� ����
int total_wait_time; // ����Ʈ�� ������ ��� Job�� ���ð�(start time - arrival time)�� ��
int num_printed_jobs; // �ùķ��̼��� ���� ������ ����Ʈ�� ���۵� Job�� �� ��
typedef struct {
	int id; // Job ID
	int arrival_time; // Job�� ��û��(������) �ð�
	int duration; // Job�� ����Ʈ �ð�
} Job;
typedef Job Element;
// Global queue
typedef struct queue *queue_pointer;
typedef struct queue {
	Element item;
	queue_pointer link;
} queue;
queue_pointer front, rear;

// ID�� id, ��û�ð��� arrival_time, ����Ʈ �ð��� duration�� Job�� ť�� ����
void insert_job_into_queue(int id, int arrival_time, int duration);
// ���� job�� ť���� ���� ����(���� job id, remaining time �� ����)
void process_next_job();
// �����ϰ� true Ȥ�� false�� return. True�� Ȯ����JOB_ARRIVAL_PROB
boolean is_job_arrived();
// �����Ͱ� ��� ������(���� job�� remaining time <= 0) true
boolean is_printer_idle();
double random(); // 0.0 - 1.0 ������ ���� ���� ��ȯ
int get_random_duration(); // 1 - MAX_PRINTING_TIME+1 ������ ���� ���� ��ȯ
void addq(Job e);
Element deleteq();
boolean is_queue_empty();
void queue_show(); // ���� ť�� �ִ� job�� id ���� ����Ʈ