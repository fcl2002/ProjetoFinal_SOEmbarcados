#ifndef PROJETOFINAL_H
#define PROJETOFINAL_H

#define MAX_QUEUE 3      //máximo de filas
#define MAX_ELEMENTS 10  //máximo de elementos em cada fila
#define MAX_BUFFER 5    //tamanho do buffer

//estrutura de processo
typedef struct Processo {
    int tempo_chegada;  //data de criação
    int duracao;        //tempo de execução
    int prioridade;     //proridade
} Processo;

//estrutura de fila de processos
typedef struct Queue {
    Processo processes[MAX_ELEMENTS];
    int start_queue;
    int end_queue;
} Queue;

typedef struct Buffer {
    Processo processes[MAX_BUFFER];
    int start;
    int end;
} Buffer;

void queue_init(Queue *queue);
void queue_insert(Queue *queue, Processo process);
int isEmpty(Queue *queue);

void buffer_init(Buffer *buf);

// O número de processos presentes no arquivo de entrada deverá ter
// no mínimo o dobro do tamanho do buffer circular.
Processo input_proc[MAX_BUFFER];    // processos vindos do input 
Buffer buffer_proc[MAX_BUFFER];  // vetor que sofre escalonamento
int start = 0, end = 0;
int clock_tick = -1; // controle do quantum

void ler_arquivo(Processo *p);
void imprimir_saida(Processo *p, char *text);
void schedule_priority(Processo *p);
void schedule_multiple_queues(Processo *p);
void print_process(Processo *p, int opc);
void add_process(Processo *p_fila, Buffer *p_buffer);
void kernel_loop(void);

#endif