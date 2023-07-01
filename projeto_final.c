#include <stdio.h>
#include <stdlib.h>
#include "projetofinal.h"

int main()
{

    ler_arquivo(input);
    printf("processos sem escalonamento\n");
    print_process(input);

    printf("processos escalonados priority\n");
    // add_process(fila_proc, buffer_proc);
    // schedule_priority(buffer_proc);
    // print_process(buffer_proc, 2);

    // printf("\nstart = %d, end = %d\n", start, end);

    // imprimir_saida(buffer_proc, "processos escalonado");

    kernel_loop();

    return 0;
}

//inicialização das filas criadas
void queue_init(Queue *queue) {
    queue->start = 0;
    queue->end = 0;
}
//inserindo processos na fila
void queue_insert(Queue *queue, Processo process) {
    if (queue->end == MAX_ELEMENTS - 1) {
        printf("Full queue");
        return;
    }
    queue->processes[++queue->end] = process;
}

//ler os dados do arquivo input.txt
void ler_arquivo(Queue *q) {
    FILE *f = fopen("input.txt", "r");
    Processo aux;

    if (f == NULL) return;

    if ((q->end + 1) % MAX_ELEMENTS == q->start) {
        printf("full process list\n");
        return;
    }

    for (int i = 0; i < MAX_ELEMENTS; i++) {
        //colocar os processos dentro da fila 
        fscanf(f, "%d %d %d", &aux.tempo_chegada, &aux.duracao, &aux.prioridade);
        q->processes[i] = aux;
    }
    fclose(f);
}
//imprime a saída do programa no arquivo output.txt
void imprimir_saida(Queue *q, char *text)
{
    FILE *o = fopen("output.txt", "w");
    fprintf(o, "%s \n", text);
    for (int i = 0; i < MAX_ELEMENTS; i++)
        fprintf(o, "\tp[%d] %d %d \n", q->processes[i].tempo_chegada, q->processes[i].duracao, q->processes[i].prioridade);

    //fechando o arquivo de saída output.txt
    fclose(o);
}
//escalonador de prioridade
void schedule_priority(void *queue) {    
    Queue *q = (Queue*) queue;
    int i = q->start;
    Processo aux;

    while (i != q-> end) {
        if (q->processes[q->start].prioridade < q->processes[i].prioridade) 
        {
            aux = q->processes[q->start];
            q->processes[q->start] = q->processes[i];
            q->processes[i] = aux;
        }
        i = (i+1) % MAX_ELEMENTS;
    }
}
// printa os procesos da fila
void print_process(Queue *q) {
    for (int i = 0; (i < MAX_ELEMENTS); i++)
        printf("\tp %d %d %d \n", q->processes[i].tempo_chegada, q->processes[i].duracao, q->processes[i].prioridade);
}
// adiciona os processos no buffer de acordo com o clock_tick
void add_process(Queue *input, Queue *q) {

    if((q->end+1)%MAX_ELEMENTS == q->start)
        return; //fila cheia

    for (int i = 0; i < MAX_ELEMENTS; i++)
        if ((input->processes[i].tempo_chegada <= clock_tick) && ((q->end+1) % MAX_ELEMENTS != q->start) && (input->processes[i].tempo_chegada != -1)) {
            q->processes[q->end] = input->processes[i];
            q->end = (q->end + 1) % MAX_ELEMENTS;

            //limpar a posição do input para não interferir na próxima leitura
            input->processes[i].tempo_chegada = -1;
        }
}
void remove_process(Queue *q) {    
    //executar o primeiro processo da fila e incrementar a variável 'start'
    printf("\t processo %d executado\n", q->processes[q->start].prioridade);
    clock_tick += q->processes[q->start].duracao;

    q->processes[q->start].prioridade = -1;
    q->start = (q->start+1) % MAX_ELEMENTS;
}
//looping infinito
void kernel_loop(void)
{
    queue_init(fila_prioridade);

    for (;;) {

        add_process(input, fila_prioridade);

        print_process(fila_prioridade);
        printf("add--------------------------- clock time %d\n", clock_tick);

        //se a lista não está vazia
        if (fila_prioridade->end  != fila_prioridade->start) {
            schedule_priority(fila_prioridade);
            remove_process(fila_prioridade);
        }
        else
            clock_tick++;

        print_process(fila_prioridade);
        printf("rem--------------------------- clock time %d\n", clock_tick);

        if (clock_tick >= 49)
            break;
    }
}