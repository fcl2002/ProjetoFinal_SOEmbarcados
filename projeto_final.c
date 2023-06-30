#include <stdio.h>
#include <stdlib.h>
#include "projetofinal.h"

int main()
{

    ler_arquivo(input_proc);
    printf("processos sem escalonamento\n");
    print_process(input_proc, 1);

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
    queue->start_queue = 0;
    queue->end_queue = 0;
}
//verificação se a fila está vazia
int isEmpty(Queue *queue) {
    return (queue->end_queue < queue->start_queue);
}
//inserindo processos na fila
void queue_insert(Queue *queue, Processo process) {
    if (queue->end_queue == MAX_ELEMENTS - 1) {
        printf("Full queue");
        return;
    }
    queue->processes[++queue->end_queue] = process;
}

//inicialização do buffer
void buffer_init(Buffer *buf) {
    buf->start = 0;
    buf->end = -1;
}

//ler os dados do arquivo input.txt
void ler_arquivo(Processo *p)
{
    FILE *f = fopen("input.txt", "r");
    Processo aux;

    if (f == NULL)
        return;

    if ((end + 1) % MAX_ELEMENTS == start)
    {
        printf("full process list\n");
        return;
    }

    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
        //colocar os valores do arquivo nas variáveis do Processo
        fscanf(f, "%d %d %d", &aux.tempo_chegada, &aux.duracao, &aux.prioridade);
        p[i] = aux;
    }
    fclose(f);
}
//imprime a saída do programa no arquivo output.txt
void imprimir_saida(Processo *p, char *text)
{
    FILE *o = fopen("output.txt", "w");
    fprintf(o, "%s \n", text);
    for (int i = 0; i < MAX_BUFFER; i++)
        fprintf(o, "\tp[%d] %d %d \n", p[i].tempo_chegada, p[i].duracao, p[i].prioridade);

    //fechando o arquivo de saída output.txt
    fclose(o);
}
//priority-based scheduling
void schedule_priority(Processo *p)
{
    Processo aux;
    for (int i = 0; i < MAX_BUFFER; i++) {
        for (int j = i + 1; j < MAX_BUFFER; j++) {
            if (p[i].prioridade < p[j].prioridade) {
                //swap
                aux = p[i];
                p[i] = p[j];
                p[j] = aux;
            }
        }
    }
}
// Scheduling Multiple queues with feedback
void schedule_multiple_queues(Processo *p)
{
}
// printa os procesos do buffer e da fila
void print_process(Processo *p, int opc)
{
    if (opc == 1)
    {
        for (int i = 0; (i < MAX_ELEMENTS); i++)
        {
            printf("\tp %d %d %d \n", p[i].tempo_chegada, p[i].duracao, p[i].prioridade);
            // printf("======= aqui =======\n");
        }
    }
    else
    {
        for (int i = 0; i < MAX_BUFFER; i++)
        {
            printf("\tp %d %d %d \n", p[i].tempo_chegada, p[i].duracao, p[i].prioridade);
            // printf("======= aqui =======\n");
        }
    }
}
// adiciona os processos no buffer de acordo com o clock_tick
void add_process(Processo *p_fila, Buffer *p_buffer)
{
    buffer_init(p_buffer);

    for (int i = 0; i < MAX_ELEMENTS; i++) {

        if ((p_fila[i].tempo_chegada <= clock_tick) && ((p_buffer->end+1) % MAX_ELEMENTS != p_buffer->start))
        {
            // printf("adicionando buffer[%d] processo[%d] \n", end, p_fila[i].tempo_chegada);
            p_buffer->processes[p_buffer->end] = p_fila[i];
            p_buffer->end = (p_buffer->end + 1) % MAX_BUFFER;
        }
    }
}
// looping infinito
void kernel_loop(void)
{
    for (;;)
    {
        clock_tick++;
        add_process(input_proc, buffer_proc);
        // schedule_priority(buffer_proc);
        print_process(buffer_proc, 2);
        printf("--------------------------- clock time %d\n", clock_tick);
        end = 0;        //serve pra printar todos processos corretamente 
        if (clock_tick >= 10)
        {
            break;
        }
    }
}