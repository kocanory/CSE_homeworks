#pragma once
#define MAX_SIMUL_TIME 20 // 시뮬레이션 진행 시간
#define MAX_PRINTING_TIME 10 // 각 Job의 가능한 최대 프린트 시간
#define JOB_ARRIVAL_PROB 0.5 // 매 시각 새로운 Job의 도착 확률
#define boolean unsigned char
#define true 1
#define false 0
#define MAX_PQ_SIZE 1000 // Priority queue size
// 시뮬레이션을 위한 global variables
int current_time = 0; // 현재 시각
int new_job_id = 0; // 새로운 Job의 ID
int current_job_id; // 현재 프린트하고 있는 Job의 ID
int remaining_time; // 현재 프린트하고 있는 Job의 남은 프린트 시간. 매 시각 1씩 감소
int total_wait_time; // 프린트를 시작한 모든 Job의 대기시간(start time - arrival time)의 합
int num_printed_jobs; // 시뮬레이션이 끝날 때까지 프린트가 시작된 Job의 총 수
// Job
typedef struct {
	int key; // Priority queue의 키 값 (duration을 키로 설정)
	int id; // Job ID
	int arrival_time; // Job이 요청된(도착한) 시간
	int duration; // Job의 프린트 시간
} Job;
typedef Job Element;

// Global PQ (priority queue): min heap - key값(duration)이 작을 수록 우선순위가 높음
Element PQ[MAX_PQ_SIZE];
int PQ_size = 0;
void insert_job(int id, int arrival_time, int duration);
// ID가 id, 요청시간이 arrival_time, 프린트 시간이 duration인 Job을 큐에 삽입
void process_next_job(); // 다음 job을 큐에서 꺼내 수행(현재 job id, remaining time 등 설정)
boolean is_job_arrived(); // 랜덤하게 true 혹은 false를 return. True일 확률은 JOB_ARRIVAL_PROB
boolean is_printer_idle(); // 프린터가 놀고 있으면(현재 job의 remaining time <= 0) true
double random(); // 0.0 - 1.0 사이의 랜덤 값을 반환
int get_random_duration(); // 1 - MAX_PRINTING_TIME+1 사이의 랜덤 값을 반환
// PQ에 job 삽입
void insert_PQ(Element item);
// PQ에서 min item (루트) 삭제 및 반환
Element delete_PQ();
// PQ의 job들의 key와 id를 차례로 출력
void PQ_show();
boolean is_PQ_empty();