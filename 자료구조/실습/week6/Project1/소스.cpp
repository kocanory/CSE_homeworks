#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue_simulation.h"
int main()
{
	int duration;
	srand(time(NULL));
	while (current_time < MAX_SIMUL_TIME) {
		printf("\n----- time %d ----- \n", current_time);
		// 새 job이 들어오면 큐에 삽입
		if (is_job_arrived()) {
			++new_job_id;
			duration = get_random_duration();
			insert_job_into_queue(new_job_id, current_time, duration);
		}
		// 프린터가 놀고 있으면 다음 job을 수행
		if (is_printer_idle()) {
			if (!is_queue_empty()) process_next_job();
		}
		// 아직 프린트 중
		else {
			printf(" 아직 Jop <%d>을 프린트하고 있습니다 ... \n", current_job_id);
			--remaining_time;
		}
		// 현재 큐의 상태를 보여줌
		printf(" 현재 프린터 큐: ");
		queue_show();
		puts("");
		++current_time;
	}

	printf("\n완료된 프린트 jop = %d 개\n", num_printed_jobs);
	printf("평균 지연 시간	  = %f 단위 시간\n\n", (double)total_wait_time / (double)num_printed_jobs);
	// 통계 자료 출력 - 완료된 프린트 job 수, 평균 지연 시간 (total_wait_time/num_printed_jobs)
}
// ID가 id, 요청시간이 arrival_time, 프린트 시간이 duration인 Job을 큐에 삽입
void insert_job_into_queue(int id, int arrival_time, int duration)
{
	Job p;
	p.id = id;
	p.arrival_time = arrival_time;
	p.duration = duration;
	addq(p);
	// id, arrival_time, duration 설정 후 job p를 큐에 삽입
	// addq() 사용
	printf(" 새 jop <%d>이 들어 왔습니다. 프린트 시간은 = %d 입니다. \n", id, duration);
}
void process_next_job()
{
	Job p;
	p = deleteq();
	current_job_id = p.id;
	remaining_time = p.duration - 1;
	total_wait_time = total_wait_time + (current_time - p.arrival_time);
	// deleteq() 사용
	// 다음 job을 큐에서 꺼내와
	// current_job_id, remaining_time (duration – 1),
	// total_wait_time (total_wait_time + (current_time – arrival_time) 설정
	++num_printed_jobs;
	printf(" 프린트를 시작합니다 - jop <%d>... \n", current_job_id);
}
boolean is_job_arrived()
{
	if (random() < JOB_ARRIVAL_PROB)
		return true;
	else
		return false;
}
// 프린터가 놀고 있는지를 결정. 현재 job의 remaining time <= 0이면 true
boolean is_printer_idle()
{
	if (remaining_time <= 0)
		return true;
	else
		return false;
}
// 0.0 ~ 1.0 사이의 랜덤 값을 반환
double random()
{
	return rand() / (double)RAND_MAX;
}
// 1 ~ MAX_PRINTING_TIME+1 사이의 랜덤 값을 반환
int get_random_duration()
{
	return (int)(MAX_PRINTING_TIME * random()) + 1;
}

void addq(Job e)
{
	queue_pointer node = (queue_pointer)malloc(sizeof(queue));
	node->item = e;
	node->link = NULL;

	if (front == NULL)
		front = rear = node;
	else
	{
		rear->link = node;
		rear = node;
	}
}
Element deleteq()
{
	queue_pointer temp;
	Element item;

	if (front == NULL)
		return item;
	item = front->item;
	temp = front;

	front = front->link;
	free(temp);

	return item;
}
void queue_show()
{
	queue_pointer p = front;
	printf("[");
	while (p)
	{
		printf(" %d", p->item.id);
		p = p->link;
	}
	printf(" ]");
}
boolean is_queue_empty()
{
	if (front == NULL)
		return true;
	else
		return false;
}