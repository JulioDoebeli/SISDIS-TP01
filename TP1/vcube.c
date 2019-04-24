#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    int *ESTADO;
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
               j;           // Variavel auxiliar 2
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
    for (i=0; i<N; i++) {
        memset(fa_name, '\0', 5);
        sprintf(fa_name, "%d", i);
        nodo[i].id = facility(fa_name,1);
        nodo[i].variavel = -1;
        nodo[i].ESTADO = (int *) malloc (sizeof(int)*N);
        for (j=0; j<N; j++)
            nodo[i].ESTADO[j] = -1;
        /*printf("fa_name = %s, nodo[i].id = %d\n", fa_name, nodo[i].id);*/
    }

    // Escalonamento de eventos iniciais
    for (i=0; i<N; i++)
        schedule(test, 30.0, i);
    schedule(fault, 31.0, 2);
    schedule(repair, 61.0, 2);

    // Loop principal da simulacao
    while (time() < 100.0) {
        cause (&event, &token);
        switch(event) {
        case test:
            if (status(nodo[token].id) != 0) break;
            Prox = (token+1) % N;
            printf("O nodo %d vai testar o nodo ", token);
            printf("%d no tempo %5.1f ---> ", Prox, time());
                if ( (status(nodo[Prox].id)) == 0)
                {
                    printf("   Nodo %d estah sem-falha.\n",Prox);

                    if (nodo[Prox].variavel != -1)
                        nodo[token].variavel = nodo[Prox].variavel;
                    /*printf("   nodo[%d].variavel = %d\n", token, nodo[token].variavel);*/

                    // Pega vetor do nodo testado (vetor de Prox)
                    for (j=0; j<N; j++)
                    {
                        if (nodo[Prox].ESTADO[j] != -1)
                            nodo[token].ESTADO[j] = nodo[Prox].ESTADO[j];
                    }
                    nodo[token].ESTADO[Prox] = 0;

                    /*for (j=0; j<N; j++)
                        printf("%d ",nodo[token].ESTADO[j]);
                    printf("\n");*/
                }
                else
                {
                    printf("   Nodo %d estah falho.\n",Prox);
                    nodo[token].variavel = Prox;
                    /*printf("   nodo[%d].variavel = %d\n", token, nodo[token].variavel);*/

                    nodo[token].ESTADO[Prox] = 1;

                    /*for (j=0; j<N; j++)
                        printf("%d ",nodo[token].ESTADO[j]);
                    printf("\n");*/
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
}
