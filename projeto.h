#ifndef PROJETOFINAL_H
#define PROJETOFINAL_H

#define MAX_ELEMENTS 3      //máximo de filas
#define MAX_ELEMENTS 10  //máximo de elementos em cada fila
#define BUFFER_SIZE 5    //tamanho do buffer

//armazena os dados pertinentes de cada processo
typedef struct Processo {
    int tempo_chegada;  //data de criação
    int duracao;        //tempo de execução
    int prioridade;     //proridade
} Processo;

// O número de processos presentes no arquivo de entrada deverá ter
// no mínimo o dobro do tamanho do buffer circular.
Processo fila_proc[BUFFER_SIZE];    // processos vindos do input 
Processo buffer_proc[BUFFER_SIZE];  // vetor que sofre escalonamento
int start = 0, end = 0;
int clock_tick = -1; // controle do quantum

void ler_arquivo(Processo *p);
void imprimir_saida(Processo *p, char *text);
void schedule_priority(Processo *p);
void schedule_multiple_queues(Processo *p);
void print_process(Processo *p, int opc);
void add_process(Processo *p_fila, Processo *p_buffer);
void kernel_loop(void);


#endif