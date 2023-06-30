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
Queue input[MAX_ELEMENTS];    // processos vindos do input 
Queue fila_prioridade[MAX_ELEMENTS];  // vetor que sofre escalonamento
int clock_tick = 0; // controle do quantum

void ler_arquivo(Queue *q);
void imprimir_saida(Queue *q, char *text);
void schedule_priority(void *queue);

void schedule_multiple_queues(Processo *p);

void print_process(Queue * q);
void add_process(Queue *p_fila, Queue *p_buffer);
void remove_process(Queue *q);
void kernel_loop(void);

#endif