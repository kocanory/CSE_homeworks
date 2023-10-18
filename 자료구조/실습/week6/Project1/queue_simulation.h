#pragma once
#define MAX_SIMUL_TIME 20 // 시뮬레이션 진행 시간
#define MAX_PRINTING_TIME 5 // 각 Job의 가능한 최대 프린트 시간
#define JOB_ARRIVAL_PROB 0.5 // 매 시각 새로운 Job의 도착 확률
#define boolean unsigned char
#define true 1
#define false 0
// 시뮬레이션을 위한 global variables
int current_time = 0; // 현재 시각
int new_job_id = 0; // 새로운 Job의 ID
int current_job_id; // 현재 프린트하고 있는 Job의 ID
int remaining_time; // 현재 프린트하고 있는 Job의 남은 프린트 시간. 매 시각 1씩 감소
int total_wait_time; // 프린트를 시작한 모든 Job의 대기시간(start time - arrival time)의 합
int num_printed_jobs; // 시뮬레이션이 끝날 때까지 프린트가 시작된 Job의 총 수
typedef struct {
	int id; // Job ID
	int arrival_time; // Job이 요청된(도착한) 시간
	int duration; // Job의 프린트 시간
} Job;
typedef Job Element;
// Global queue
typedef struct queue *queue_pointer;
typedef struct queue {
	Element item;
	queue_pointer link;
} queue;
queue_pointer front, rear;

// ID가 id, 요청시간이 arrival_time, 프린트 시간이 duration인 Job을 큐에 삽입
void insert_job_into_queue(int id, int arrival_time, int duration);
// 다음 job을 큐에서 꺼내 수행(현재 job id, remaining time 등 설정)
void process_next_job();
// 랜덤하게 true 혹은 false를 return. True일 확률은JOB_ARRIVAL_PROB
boolean is_job_arrived();
// 프린터가 놀고 있으면(현재 job의 remaining time <= 0) true
boolean is_printer_idle();
double random(); // 0.0 - 1.0 사이의 랜덤 값을 반환
int get_random_duration(); // 1 - MAX_PRINTING_TIME+1 사이의 랜덤 값을 반환
void addq(Job e);
Element deleteq();
boolean is_queue_empty();
void queue_show(); // 현재 큐에 있는 job의 id 들을 프린트