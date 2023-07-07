#include <stdio.h>
#include <stdlib.h>
#include "projetofinal.h"

void imprimir_saida(FILE *o, Queue *q, char *text);
void kernel_loop(FILE *o,Queue *q, Queue *mult);
void execute_process(FILE *o, Queue *q);
void mult_print_process(FILE *o, Queue *mult);

int main()
{
    ler_arquivo(input, mult_input);
    FILE *o = fopen("output.txt", "a");
    //impressão do vetor input (leitura do input.txt)
    fprintf(o, " -- processos sem escalonamento -- \n");
    for (int i = 0; i < 20; i++)
        fprintf(o, "\tp %d %d %d \n", input->processes[i].tempo_chegada, input->processes[i].duracao, input->processes[i].prioridade);

    printf("processos sem escalonamento\n");
    for (int i = 0; i < 20; i++)
        printf("\tp %d %d %d \n", input->processes[i].tempo_chegada, input->processes[i].duracao, input->processes[i].prioridade);

    kernel_loop( o, fila_prioridade, mult_queue);

    fclose(o);
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
        printf("full queue");
        return;
    }
    queue->processes[++queue->end] = process;
}
//ler os dados do arquivo input.txt
void ler_arquivo(Queue *q, Queue *mult) {
    FILE *f = fopen("input.txt", "r");
    Processo aux;

    if (f == NULL) return;

    for (int i = 0; i < 20; i++) {
        //colocar os processos dentro da fila 
        fscanf(f, "%d %d %d", &aux.tempo_chegada, &aux.duracao, &aux.prioridade);
        q->processes[i] = aux;
        mult->processes[i] = aux;
    }
    fclose(f);
}
//imprime a saída do programa no arquivo output.txt
void imprimir_saida(FILE *o, Queue *q, char *text)
{
    fprintf(o, "%s", text);
    for (int i = 0; i < MAX_ELEMENTS; i++)
        fprintf(o, "\tp %d %d %d \n", q->processes[i].tempo_chegada, q->processes[i].duracao, q->processes[i].prioridade);

    //fechando o arquivo de saída output.txt
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
    for (int i = 0; i < MAX_ELEMENTS; i++)
        printf("\tp %d %d %d \n", q->processes[i].tempo_chegada, q->processes[i].duracao, q->processes[i].prioridade);
}
// adiciona os processos no buffer de acordo com o clock_tick
void add_process(Queue *input, Queue *q) {
    //fila está cheia?
    if((q->end+1)%MAX_ELEMENTS == q->start)
        return;
    
    for(int i = 19; i >= 0; i--) {
        //se o processo já chegou e ainda não foi lido
        if((input->processes[i].tempo_chegada <= clock_tick) && (input->processes[i].tempo_chegada != -1)){
            q->processes[q->end] = input->processes[i];
            q->end = (q->end + 1) % MAX_ELEMENTS;

            //indicar que o processo já foi lido
            input->processes[i].tempo_chegada = -1;
        }
        if((q->end+1)%MAX_ELEMENTS == q->start)
            break; //fila cheia
    }
}
//executa processos
void execute_process(FILE *o, Queue *q) {    
    //executar o primeiro processo da fila e incrementar a variável 'start'
    printf("> processo %d executado\n", q->processes[q->start].prioridade);
    fprintf(o, "> processo %d executado\n", q->processes[q->start].prioridade);
    clock_tick += q->processes[q->start].duracao;

    printf("---------------------------- clock time: %d | start: %d | end: %d\n", clock_tick, q->start, q->end);
    fprintf(o, "---------------------------- clock time: %d | start: %d | end: %d\n", clock_tick, q->start, q->end);

    //q->processes[q->start].prioridade = -1;
    q->start = (q->start+1) % MAX_ELEMENTS;
}
//
// multiplas filas ------------------------------------
//
void mult_queue_init(Queue *mult){
    mult[0].end = 0;
    mult[0].start = 0;
    mult[1].end = 0;
    mult[1].start = 0;
    mult[2].end = 0;
    mult[2].start = 0;
}
//
void  mult_add_process(Queue *inp, Queue *mult){

    //primeira fila está cheia?
    if((mult[0].end+1)%MAX_ELEMENTS == mult[0].start){
        printf("queue full\n");
        return;
    }

    for(int i = 0; i < 20; i++) {
        //se o processo já chegou e ainda não foi lido
        // printf("end [%d]\n", mult[0].end);
        if((inp->processes[i].tempo_chegada <= mult_clock_tick) && (inp->processes[i].tempo_chegada > -1)){
            
            //adiciona os processos na primeira fila
            mult[0].processes[mult[0].end] = inp->processes[i];
            mult[0].end = (mult[0].end + 1) % MAX_ELEMENTS;
            //
            inp->processes[i].tempo_chegada = -1;
        }
        if((mult[0].end+1)%MAX_ELEMENTS == mult[0].start)
            break; //fila cheia
    }
}
//
void mult_print_process(FILE *o, Queue *mult){

    //printa primeira fila
    for (int j =0; j < MAX_ELEMENTS; j++)
    {
        printf("\tfila[0] p %d %d %d \tfila[1] p %d %d %d \tfila[2] p %d %d %d\n", mult[0].processes[j].tempo_chegada, 
                mult[0].processes[j].duracao, mult[0].processes[j].prioridade,  mult[1].processes[j].tempo_chegada, 
                mult[1].processes[j].duracao, mult[1].processes[j].prioridade, mult[2].processes[j].tempo_chegada, 
                mult[2].processes[j].duracao, mult[2].processes[j].prioridade);
        fprintf(o, "\tfila[0] p %d %d %d \tfila[1] p %d %d %d \tfila[2] p %d %d %d\n", mult[0].processes[j].tempo_chegada, 
                mult[0].processes[j].duracao, mult[0].processes[j].prioridade,  mult[1].processes[j].tempo_chegada, 
                mult[1].processes[j].duracao, mult[1].processes[j].prioridade, mult[2].processes[j].tempo_chegada, 
                mult[2].processes[j].duracao, mult[2].processes[j].prioridade);
    }
}
void mult_remove(Queue *mult, int idx, int quantum)
{
    int i = mult[idx].start; // idx 0

    // verifica se tempo de duracao e menor que quantum
    if ((mult[idx].processes[i].duracao - quantum) <= 0)
    {
        //setando valores diferentes para visualização da execução
        mult[idx].processes[i].duracao = 0;
        mult[idx].processes[i].prioridade = 0;
        mult[idx].processes[i].tempo_chegada = 0;

        //incrementação da variável start da fila em eecução e somatório da duração ao clock
        mult[idx].start = (mult[idx].start + 1) % MAX_ELEMENTS;
        mult_clock_tick += quantum;

        printf("--> processo [%d] executado\n", mult[idx].processes[mult[idx].start].tempo_chegada);
        return;
    }
    else
    {
        mult[idx].processes[i].duracao -= quantum; // diminui a fatia de tempo do processo
        mult_clock_tick += quantum;
        mult[idx + 1].processes[mult[idx + 1].end] = mult[idx].processes[i]; // adiciona na segunda fila
        printf("--> processo [%d] movido fila [%d]\n", mult[idx].processes[i].tempo_chegada, idx + 1);
        mult[idx + 1].end = (mult[idx + 1].end + 1) % MAX_ELEMENTS; // move curso do vetor
        mult[idx].processes[mult[idx].start].duracao = 0;
        mult[idx].processes[mult[idx].start].prioridade = 0;
        mult[idx].processes[mult[idx].start].tempo_chegada = 0;
        mult[idx].start = (mult[idx].start + 1) % MAX_ELEMENTS;
    }
}
//
void mult_execute_process(Queue *mult)
{

    // fila mult[0] vazia, executo a fila mult[1]
    if (mult[0].start == mult[0].end)
    {
        int quantum = 1;
        mult_remove(mult, 1, quantum);
        return;
    }
    if ((mult[1].start == mult[1].end)&&(mult[0].start == mult[0].end))
    {
        int quantum = 10;
        mult_remove(mult, 2, quantum);
        return;
    }
    if ((mult[0].start == mult[0].end)&&(mult[0].start == (mult[0].end+1)%MAX_ELEMENTS))
    {
        int quantum = 1;
        mult_remove(mult, 1, quantum);
        return;
    }
    if (mult[1].start == (mult[1].end+1)%MAX_ELEMENTS)
    {
        int quantum = 5;
        mult_remove(mult, 1, quantum);
        return;
    }
    if (mult[2].start == (mult[2].end+1)%MAX_ELEMENTS)
    {
        int quantum = 5;
        mult_remove(mult, 2, quantum);
        return;
    }

    //se chegou aqui a mult[0] não está vazia, logo executamos ela
    int quantum = 3;
    mult_remove(mult, 0, quantum);
}
//looping infinito
void kernel_loop(FILE *o,Queue *q, Queue *mult)
{
    clock_tick = 0;
    queue_init(q);

    for (;;) {
        add_process(input, q);
        printf("processos escalonados prioridade\n");
        print_process(q);
        imprimir_saida(o, q, "processos escalonados prioridade\n");
        //se a lista não está vazia
        if (q->end  != q->start) {
            schedule_priority(q);
            execute_process(o, q);
        }else
            clock_tick++;

        if (clock_tick >= 99)
            break;
    }
    
    printf("-----------processos sem escalonamento multiplas ----------------------\n");
    for (int i = 0; i < 20; i++)
        printf("\tp %d %d %d \n", mult_input->processes[i].tempo_chegada, mult_input->processes[i].duracao, mult_input->processes[i].prioridade);

    fprintf(o, "-----------processos sem escalonamento multiplas ----------------------\n");
    for (int i = 0; i < 20; i++)
        fprintf(o, "\tp %d %d %d \n", mult_input->processes[i].tempo_chegada, mult_input->processes[i].duracao, mult_input->processes[i].prioridade);
    
    mult_clock_tick = 0;
    mult_queue_init(mult);


    for (;;) {
        mult_add_process(mult_input, mult);
        printf("\nprocessos escalonados multiplas -- clock[%d] start0[%d] end0[%d] start1[%d] end1[%d] \n", 
            mult_clock_tick, mult[0].start, mult[0].end, mult[1].start, mult[1].end );
        fprintf(o, "\nprocessos escalonados multiplas -- clock[%d] start0[%d] end0[%d] start1[%d] end1[%d] \n", 
            mult_clock_tick, mult[0].start, mult[0].end, mult[1].start, mult[1].end );
        mult_print_process(o, mult);
        
        if ((mult[0].end != mult[0].start)||(mult[1].end != mult[1].start)||(mult[2].end != mult[2].start))
        {
            mult_execute_process(mult);
        }else{
            mult_clock_tick++;
        }
        


        if (mult_clock_tick >= 200)
            break;
    }
 
}