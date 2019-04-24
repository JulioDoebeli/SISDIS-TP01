/*
 * libvcube.c
 * 
 * Copyright 2019 julio doebeli <julio@julio-N501JW>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define and	&
#define or	|
#define xor	^


// Retorna nodo de cluster adjacente de dimensão
int node_from_adjacent_cluster(int network_dimention, int cluster_dimention, int curent_node, int position){
	int erro_count 			= 0;
	
	int net_dimen_valid = 0;
	int network_size 	= 0;
	
	int clu_dimen_valid = 0;
	int cluster_size 	= 0;
	
	// 1 =< network_dimention =< 31
	if ( network_dimention < 1){
		fprintf(stderr, "ERRO 01: A Dimenção da Network é muito pequena(%d). Ela deveria ser maior ou igual a 1.\n", network_dimention); 
		erro_count--;
	}else if (network_dimention > 31){
		fprintf(stderr, "Erro 02: A Dimenção da Network é muito grande(%d). Ela deveria ser menor ou igual a 32.\n", network_dimention); 
		erro_count--;
	}else {
		net_dimen_valid = 1;
		network_size = 1<< network_dimention;
	}
	
	// 1 =< cluster_dimention < network_dimention
	if ( cluster_dimention < 1){
		fprintf(stderr, "Erro 03: A Dimenção do Cluster é muito pequena(%d). Ela deveria ser maior ou igual a 1.\n", cluster_dimention); 
		erro_count--;
	}else if (cluster_dimention > 31){
		fprintf(stderr, "Erro 04: A Dimenção do Cluster é muito grande(%d). Ela deveria ser menor ou igual a 32.\n", cluster_dimention); 
		erro_count--;
	}else {
		clu_dimen_valid = 1;
		cluster_size = 1<<cluster_dimention;
	}
	
	if (net_dimen_valid==1 && clu_dimen_valid==1) {
		if (network_dimention < cluster_dimention) {
			fprintf(stderr, "Erro 05: A Dimenção do Cluster é maior ou igual a Dimenção da Network (%d >= %d).O Cluster deveria ser menor que a Network.\n", cluster_dimention, network_dimention); 
			erro_count--;
		}
	}
	
	// 0 < current_node < network_size
	if (curent_node < 0) {
		fprintf(stderr, "Erro 06: Nodo atual tem posição menor que Zero(%d < 0). Ela deveria estar entre Zero(0) e o Tamanho da rede(%d).\n", curent_node, network_size); 
		erro_count--;
	}else if ( curent_node>network_size ) {
		fprintf(stderr, "Erro 07: Nodo atual tem posição maior ou igual ao tamanho da network (%d > %d). Ela deveria estar entre Zero(0) e o Tamanho da rede(%d).\n", curent_node, network_size, network_size); 
		erro_count--;
	}
	
	// 0 =< position < cluster_size
	if (position < 0) {
		fprintf(stderr, "Erro 08: Posição atual é menor que Zero(%d < 0). Ela deveria estar entre Zero(0) e o Tamanho do Cluster(%d).\n", position, cluster_size); 
		erro_count--;
		
	}else if ( (position>=cluster_size) && (clu_dimen_valid==1) ){
		fprintf(stderr, "Erro 09: Posição atual é maior ou igual ao tamanho do Cluster (%d >= %d). Ela deveria estar entre Zero(0) e o Tamanho do Cluster(%d).\n", position, cluster_size, cluster_size);
		erro_count--;	
	}
	
	
	if (erro_count != 0)
		return erro_count;
	
	int c = curent_node;//  xor (1 << (cluster_dimention-1));
	
	for (int i = 0; i <= position; i++)
		if (i < cluster_dimention)
			c = c xor ( 1 << ( (2*cluster_dimention-1-i)%(cluster_dimention) ) );
		else
			c = c xor ( 1 << ( (2*cluster_dimention+1+i)%(cluster_dimention) ) );
	return c;
}

/*int main (void)
{
	int tested_node;
	int network_size;
	int cluster_size;
	for (int network_dimention = 3; network_dimention <= 4; network_dimention++) {
		network_size = 1 << network_dimention;
		printf("network_dimention = %d, network_size = %d\n", network_dimention, network_size);
		
		for (int cluster_dimention = 1; cluster_dimention <= network_dimention; cluster_dimention++) {
			cluster_size = 1<< cluster_dimention;
			printf("cluster_dimention = %d, cluster_size = %d\n", cluster_dimention, cluster_size);
			
			for (int curent_node = 0; curent_node < network_size; curent_node++) {
				printf("curent_node = %d, tested nodes are:  ", curent_node);
				
				for (int position = 0; position < cluster_size/2 ; position++) {
					tested_node = node_from_adjacent_cluster( network_dimention,  cluster_dimention,  curent_node,  position);
					printf("%d,  ", tested_node);
					
				}
				printf("\n");
			}
			printf("\n\n");
		}
		printf("\n\n\n");
	}
	scanf("\n");
}*/

int main(int argc, char *argv[]){
	if (argc != 2) {
        puts("Uso correto: tempo <num_nodos>");
        exit(1);
    }
    
    int network_dimention = atoi(argv[1]);
    int network_size = 1 << network_dimention;
    
    smpl(0,"Um exemplo de simulacao");
    reset();
    stream(1);

// Inicializacao
    nodo = (tnodo *) malloc (sizeof(tnodo)*network_size);
    for (i=0; i<network_size; i++) {
        memset(fa_name, '\0', 5);
        sprintf(fa_name, "%d", i);
        nodo[i].id = facility(fa_name,1);
        nodo[i].variavel = -1;
        nodo[i].ESTADO = (int *) malloc (sizeof(int)*N);
        for (j=0; j<network_size; j++)
            nodo[i].ESTADO[j] = -1;
        printf("fa_name = %s, nodo[i].id = %d\n", fa_name, nodo[i].id);
    }

    // Escalonamento de eventos iniciais
    for (i=0; i<network_size; i++)
        schedule(test, 30.0, i);
	
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
