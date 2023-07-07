#ifndef PROJETOFINAL_H
#define PROJETOFINAL_H

#define MAX_QUEUE 3      //máximo de filas
#define MAX_ELEMENTS 10  //máximo de elementos em cada fila

//estrutura de processo
typedef struct Processo {
    int tempo_chegada;  //data de criação
    int duracao;        //tempo de execução
    int prioridade;     //proridade
} Processo;

//estrutura de fila de processos
typedef struct Queue {
    Processo processes[MAX_ELEMENTS];
    int start;
    int end;
} Queue;

void queue_init(Queue *queue);
void queue_insert(Queue *queue, Processo process);

// O número de processos presentes no arquivo de entrada deverá ter
// no mínimo o dobro do tamanho do buffer circular.
Queue input[10];              // processos vindos do input.txt
Queue mult_input[10];              // processos vindos do input.txt
Queue fila_prioridade[MAX_ELEMENTS];    // vetor que sofre escalonamento
int clock_tick; // controle do quantum
int mult_clock_tick; // controle do quantum

void ler_arquivo(Queue *q, Queue *mult);

void schedule_priority(void *queue);
void schedule_multiple_queues(Processo *p);
void print_process(Queue *q);
void add_process(Queue *p_fila, Queue *p_buffer);



//multifilas 
Queue mult_queue[MAX_QUEUE];
void mult_queue_init(Queue *mult);
void mult_add_process(Queue *input, Queue *mult);
void mult_execute_process(Queue *mult);


#endif