## TRABALHO PRÁTICO 0
### Algoritmo de diagnóstico Adaptive-DSD, Primeiro trabalho de Sistemas Distribuídos - CI088 
Trabalho Prático 0, Simulação do Algoritmo Adaptive-DSD em ambiente SMPL,Disciplina de Sistemas Distribuídos, UFPR, 1 Semestre de 2019

### Especificação 0
  Implemente o algoritmo VCube no ambiente de simulação SMPL, e mostre resultados para diversos valores de N e diversos eventos - um evento de cada vez, um evento só ocorre depois do evento anterior ser diagnosticado. Para cada evento mostre claramente o número de testes executados e a latência para completar o diagnóstico do evento. Cada nodo mantém o vetor STATE[0..N-1] de contadores de eventos, inicializado em -1 (estado unknown). Assume-se que os nodos são inicializados sem-falha, a entrada correspondente ao nodo no vetor STATE[] do testador é setada para zero. Ao descobrir um novo evento em um nodo testado, o testador incrementa a entrada correspondente no vetor STATE[].

Para a transferência de informações de diagnóstico lembre-se da estratégia do VCube: quando um nodo sem-falha testa outro nodo sem-falha obtém informações sobre "novidades". Basta comparar os vetores STATE para saber se o testado tem alguma novidade.

Importante: em cada intervalo de testes todos os testadores executam todos os testes assinalados.

#### Algoritmo Hi-ADSD
```
Algoritmo Hi-ADSD executado no nodo i

while(true){
    for ( s=1 ; s<log2(N) ; s++) {
        do {
            node_to_test = próximo_nodo_em_c(i,s);
            if ( teste(node_to_test) == sem_falha ) 
                atualiza_informação_de_diagnóstico_do_cluster();
        } while ( teste(node_to_test) == sem_falha  &&  todos_os_nodos_estão_falhos_em_c(i,s) )
            if ( todos_os_nodos_estao_falhos_em_c(i,s) )
                apaga_informações_de_diagnóstico_do_cluster_c(i,s);
        durma_até_o_proximo_intervalo_de_testes();
    }
}
```
### Tarefas
#### Tarefa 0
Editar, Compilar, Executar o programa tempo.c

#### Tarefa 1
Cada Nodo Sem Falha Testa o Seguinte no Anel
#### Tarefa 2
Cada Nodo Sem Falha Testa os Seguintes no Anel Sequencialmente até encontrar outro nodo sem falha
#### Tarefa 3
Cada Nodo Sem Falha Mantem Localmente um vetor com os estados dos nodos e atualiza o estado com resultado de cada teste próprio. 
#### Tarefa 4
Cada Nodo Sem Falha Mantem vetor de estados e o atualiza com informação de outro nodo sem falha após testa-lo.


## TRABALHO PRÁTICO 1
Trabalho Prático 1, Algoritmo VCube no ambiente de simulação SMPL, Disciplina de Sistemas Distribuídos, UFPR, 1 Semestre de 2019

### Especificação 1
Implemente o algoritmo VCube no ambiente de simulação SMPL, e mostre resultados para diversos valores de N e diversos eventos - um evento de cada vez, um evento só ocorre depois do evento anterior ser diagnosticado. Para cada evento mostre claramente o número de testes executados e a latência para completar o diagnóstico do evento. Cada nodo mantém o vetor STATE[0..N-1] de contadores de eventos, inicializado em -1 (estado unknown). Assume-se que os nodos são inicializados sem-falha, a entrada correspondente ao nodo no vetor STATE[] do testador é setada para zero. Ao descobrir um novo evento em um nodo testado, o testador incrementa a entrada correspondente no vetor STATE[].

Para a transferência de informações de diagnóstico lembre-se da estratégia do VCube: quando um nodo sem-falha testa outro nodo sem-falha obtém informações sobre "novidades". Basta comparar os vetores STATE para saber se o testado tem alguma novidade.

Importante: em cada intervalo de testes todos os testadores executam todos os testes assinalados.

#### Algoritmo VCube
```
Algoritmo VCube executado no nodo i

while(true){
    for ( s=1 ; s<log2(N) ; s++ ) {
        for ( todo j ∈ ci,s | i é o primeiro nodo sem falha ∈ cj,s) {
            if( teste(j) == sem-falha ){
                if ( ti[j] mod 2 = 1 ){
                    ti[j] = ti 7 [j] + 1;
                    obtém_informações_de_diagnóstico();
                }
            } 
            else {
                if ( ti[j] mod 2 = 0 )
                    ti[j] = ti 10 [j] + 1;
            }
        }
        durma_até_o_proximo_intervalo_de_testes();
    }
}

```
