// tempo.c
#include <stdio.h>
#include <stdlib.h>
#include "smpl.h"

// Cada nodo vai contar o seu tempo
// Eventos
#define test 1
#define fault 2
#define repair 3

// Descritor do nodo
typedef struct {
    int id;
    int variavel;
    int *TESTED;
    int *ESTADO;
    int num_testes;
} tnodo;
tnodo *nodo;

///// PROGRAMA PRINCIPAL /////
int main (int argc, char *argv[]) {
    static int N,           // Numero de nodos simulados
               token,       // Nodo atual no evento
               event,
               r,
               Prox,        // Proximo elemento (circular)
               i,           // Variavel auxiliar 1
               j,           // Variavel auxiliar 2
               k;           // Variavel auxiliar 3
    static int achou_nodo = 0; // Verifica se um nodo nao-falho foi encontrado
    static int terminou = 0;// Confere se ja chegou na condicao de parada
    static int *executou;   // Vetor que diz qual nodo ja executou
    static int rodadas = 0; // Guarda o numero da rodada de testes
    static int mesma_rodada = 0;
    static char fa_name[5];

    if (argc != 2) {
        puts("Uso correto: tempo <num_nodos>");
        exit(1);
    }
    N = atoi(argv[1]);
    smpl(0,"Um exemplo de simulacao");
    reset();
    stream(1);

    // Inicializacao
    nodo = (tnodo *) malloc (sizeof(tnodo)*N);
    executou = (int *) malloc (sizeof(int)*N);
    for (i=0; i<N; i++) {
        memset(fa_name, '\0', 5);
        sprintf(fa_name, "%d", i);
        nodo[i].id = facility(fa_name,1);
        nodo[i].variavel = -1;
        nodo[i].TESTED = (int *) malloc (sizeof(int)*N);
        for (j=0; j<N; j++)
            nodo[i].TESTED[j] = -1;
        nodo[i].ESTADO = (int *) malloc (sizeof(int)*N);
        for (j=0; j<N; j++)
            nodo[i].ESTADO[j] = -1;
        nodo[i].num_testes = 0;
        executou[i] = 0;
        /*printf("fa_name = %s, nodo[i].id = %d\n", fa_name, nodo[i].id);*/
    }

    // Escalonamento de eventos iniciais
    for (i=0; i<N-1; i++)
        schedule(test, 30.0, i);
    schedule(fault, 31.0, 2);
    schedule(repair, 61.0, 2);

    // Loop principal da simulacao
    //while (time() < 100.0) {
    while (! terminou) {
        cause (&event, &token);
        switch(event) {
        case test:
            if (status(nodo[token].id) != 0) break;

            Prox = (token+1) % N;
            achou_nodo = 0;
            while ( ! achou_nodo ) {
                printf("O nodo %d vai testar o nodo ", token);
                printf("%d no tempo %5.1f ---> ", Prox, time());

                nodo[token].num_testes = nodo[token].num_testes + 1;
                executou[token] = 1;

                if ( (status(nodo[Prox].id)) == 0){
                    printf("   Nodo %d estah sem-falha.\n",Prox);

                    if (nodo[Prox].variavel != -1)
                        nodo[token].variavel = nodo[Prox].variavel;
                    printf("   nodo[%d].variavel = %d\n", token, nodo[token].variavel);

                    // Pega vetor do nodo testado (vetor de Prox)
                    for (j=0; j<N; j++){
                        if (nodo[Prox].ESTADO[j] != -1)
                            nodo[token].ESTADO[j] = nodo[Prox].ESTADO[j];
                    }
                    nodo[token].ESTADO[Prox] = 0;

                    achou_nodo = 1;
                    // Algoritmo do TESTED_UP
                    nodo[token].TESTED[token] = Prox;
                    for (j=0; j<N; j++)
                        if (token != j)
                            nodo[token].TESTED[j] = nodo[Prox].TESTED[j];

                    terminou = 1;
                    for(i=0; i<N; i++)
                        for(j=0; j<N-1; j++)
                            for(k=j+1; k<N; k++)
                                if ( (status(nodo[j].id) == 0) &&
                                     (status(nodo[k].id) == 0) &&
                                     (nodo[j].ESTADO[i] != nodo[k].ESTADO[i]) )
                                    terminou = 0;

                    mesma_rodada = 1;
                    for(i=0; i<N; i++)
                        if ( (status(nodo[i].id) == 0) && (executou[i] != 1) )
                            mesma_rodada = 0;

                    if (mesma_rodada){
                        rodadas = rodadas + 1;
                        mesma_rodada = 0;
                        for (i=0; i<N; i++)
                            executou[i] = 0;
                    }

                    printf("   ESTADO: ");
                    for (j=0; j<N; j++)
                        printf("%d ",nodo[token].ESTADO[j]);
                    printf("\n");

                    printf("   TESTED: ");
                    for (j=0; j<N; j++)
                        printf("%d ",nodo[token].TESTED[j]);
                    printf("\n");

                } else {
                    printf("   Nodo %d falho.\n",Prox);
                    /*nodo[token].variavel = Prox;
                    printf("   nodo[%d].variavel = %d\n", token, nodo[token].variavel);*/
                    nodo[token].ESTADO[Prox] = 1;

                    printf("   ESTADO: ");
                    
                    for (j=0; j<N; j++)
                        printf("%d ",nodo[token].ESTADO[j]);
                    printf("\n");

                    printf("   TESTED: ");
                    for (j=0; j<N; j++)
                        printf("%d ",nodo[token].TESTED[j]);
                    printf("\n");

                    // Testa outro valor de nodo
                    Prox = (Prox + 1) % N;
                }
            }
            schedule(test,30.0,token);
            break;
        case fault:
            r = request(nodo[token].id, token, 0);
            if (r != 0) {
                puts("Nao foi possivel falhar");
                exit(1);
            }
            printf("O nodo %d falhou no tempo %5.1f\n", token, time());
            break;
        case repair:
            printf("O nodo %d recuperou no tempo %5.1f\n", token, time());
            release(nodo[token].id, token);
            schedule(test,30.0,token);
            break;
        }
    }

    printf("\n\n");
    for (i=0; i<N; i++)
        printf("Para nodo %d: num_testes = %d \n", i, nodo[i].num_testes);

    printf("Rodadas de teste = %d\n",rodadas);
}
