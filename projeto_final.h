#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUES 10
#define MAX_PROCESSES 10

//estrutura de processos
typedef struct {
    int id;
    int priority;
    int time_left;
    int running;
} Process;
//ponteiro para localizar e manipular os processos criados e adicionados as filas
Process *processes[MAX_PROCESSES];

typedef struct {
    Process *processes[MAX_PROCESSES];
    int head;
    int tail;
} Queue; //fila com um buffer circular

typedef struct {
    Queue queues[MAX_QUEUES];
    int num_queues;
} Scheduler; //escalonador de filas

void scheduler_init(Scheduler *s);
int scheduler_add_queue(Scheduler *s);
int enqueue(Queue *q, void *item);
void *dequeue(Queue *q);
int scheduler_enqueue(Scheduler *s, int queue_idx, void *item);
void *scheduler_dequeue(Scheduler *s);

int schedule_verifier(int index, Scheduler *s);
void scheduler(int index, Scheduler *s, int type);
int timeLeft_scheduler(Queue *q);
int priority_scheduler(Queue *q);
void print_queue(Scheduler *s, int index, int type);

#endif
