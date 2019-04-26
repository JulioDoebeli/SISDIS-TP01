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
### Log 1: "./VCube 1"
```
O nodo 0 falhou no tempo   0.0
Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1; 
=============== +-----+-----+
        Rodada  |  1  |  1  |
 Numero do Nodo |  0  |  1  |
   Status real  |  0  |  1  |
Numero de testes|  0  |  1  |
                | 01  | 01  | 
Vetor de Status | XX  | 01  | 
=============== +-----+-----+
Rodadas de testes: 1
   Nodo 0 = 0 testes (0 por rodada)
   Nodo 1 = 1 testes (1 por rodada)
```

### Log 2: "./VCube 2"
```
O nodo 0 falhou no tempo   0.0

Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1;  3 = Sem-Falha,  Obtem Status de:  2; 

Nodo   2 testou:  3 = Sem-Falha,  ;  0 = Falha       ;  1 = Sem-Falha,  ; 

Nodo   3 testou:  2 = Sem-Falha,  ;  1 = Sem-Falha,  Obtem Status de:  0; 
=============== +-------+-------+-------+-------+
        Rodada  |  1    |  1    |  1    |  1    |
 Numero do Nodo |  0    |  1    |  2    |  3    |
   Status real  |  0    |  1    |  1    |  1    |
Numero de testes|  0    |  2    |  3    |  2    |
                | 0123  | 0123  | 0123  | 0123  | 
Vetor de Status | XXXX  | 01X1  | 0111  | 0111  | 
=============== +-------+-------+-------+-------+

Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1;  3 = Sem-Falha,  Obtem Status de:  2; 

Nodo   2 testou:  3 = Sem-Falha,  ;  0 = Falha       ;  1 = Sem-Falha,  ; 

Nodo   3 testou:  2 = Sem-Falha,  ;  1 = Sem-Falha,  Obtem Status de:  0; 
=============== +-------+-------+-------+-------+
        Rodada  |  2    |  2    |  2    |  2    |
 Numero do Nodo |  0    |  1    |  2    |  3    |
   Status real  |  0    |  1    |  1    |  1    |
Numero de testes|  0    |  4    |  6    |  4    |
                | 0123  | 0123  | 0123  | 0123  | 
Vetor de Status | XXXX  | 0111  | 0111  | 0111  | 
=============== +-------+-------+-------+-------+
Rodadas de testes: 2
   Nodo 0 = 0 testes (0 por rodada)
   Nodo 1 = 4 testes (2 por rodada)
   Nodo 2 = 6 testes (3 por rodada)
   Nodo 3 = 4 testes (2 por rodada)
```


### Log 3: "./VCube 3"
```
O nodo 0 falhou no tempo   0.0

Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1;  3 = Sem-Falha,  Obtem Status de:  2;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6; 

Nodo   2 testou:  3 = Sem-Falha,  ;  0 = Falha       ;  1 = Sem-Falha,  ;  6 = Sem-Falha,  Obtem Status de:  7,  4,  5; 

Nodo   3 testou:  2 = Sem-Falha,  ;  1 = Sem-Falha,  Obtem Status de:  0;  7 = Sem-Falha,  Obtem Status de:  6,  5,  4; 

Nodo   4 testou:  5 = Sem-Falha,  ;  6 = Sem-Falha,  Obtem Status de:  7;  0 = Falha       ;  1 = Sem-Falha,  Obtem Status de:  2,  3; 

Nodo   5 testou:  4 = Sem-Falha,  ;  7 = Sem-Falha,  Obtem Status de:  6;  1 = Sem-Falha,  Obtem Status de:  0,  3,  2; 

Nodo   6 testou:  7 = Sem-Falha,  ;  4 = Sem-Falha,  Obtem Status de:  5;  2 = Sem-Falha,  Obtem Status de:  3,  0,  1; 

Nodo   7 testou:  6 = Sem-Falha,  ;  5 = Sem-Falha,  Obtem Status de:  4;  3 = Sem-Falha,  Obtem Status de:  2,  1,  0; 

=============== +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
        Rodada  |  1        |  1        |  1        |  1        |  1        |  1        |  1        |  1        |
 Numero do Nodo |  0        |  1        |  2        |  3        |  4        |  5        |  6        |  7        |
   Status real  |  0        |  1        |  1        |  1        |  1        |  1        |  1        |  1        |
Numero de testes|  0        |  3        |  4        |  3        |  4        |  3        |  3        |  3        |
                | 01234567  | 01234567  | 01234567  | 01234567  | 01234567  | 01234567  | 01234567  | 01234567  | 
Vetor de Status | XXXXXXXX  | 01X1X1XX  | 0111XX1X  | 0111XXX1  | 01X1111X  | 01X111X1  | 01111111  | 01111111  | 
=============== +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+

Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1;  3 = Sem-Falha,  Obtem Status de:  2;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6; 

Nodo   2 testou:  3 = Sem-Falha,  ;  0 = Falha       ;  1 = Sem-Falha,  ;  6 = Sem-Falha,  Obtem Status de:  7,  4,  5; 

Nodo   3 testou:  2 = Sem-Falha,  ;  1 = Sem-Falha,  Obtem Status de:  0;  7 = Sem-Falha,  Obtem Status de:  6,  5,  4; 

Nodo   4 testou:  5 = Sem-Falha,  ;  6 = Sem-Falha,  Obtem Status de:  7;  0 = Falha       ;  1 = Sem-Falha,  Obtem Status de:  2,  3; 

Nodo   5 testou:  4 = Sem-Falha,  ;  7 = Sem-Falha,  Obtem Status de:  6;  1 = Sem-Falha,  Obtem Status de:  0,  3,  2; 

Nodo   6 testou:  7 = Sem-Falha,  ;  4 = Sem-Falha,  Obtem Status de:  5;  2 = Sem-Falha,  Obtem Status de:  3,  0,  1; 

Nodo   7 testou:  6 = Sem-Falha,  ;  5 = Sem-Falha,  Obtem Status de:  4;  3 = Sem-Falha,  Obtem Status de:  2,  1,  0; 

=============== +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
        Rodada  |  2        |  2        |  2        |  2        |  2        |  2        |  2        |  2        |
 Numero do Nodo |  0        |  1        |  2        |  3        |  4        |  5        |  6        |  7        |
   Status real  |  0        |  1        |  1        |  1        |  1        |  1        |  1        |  1        |
Numero de testes|  0        |  6        |  8        |  6        |  8        |  6        |  6        |  6        |
                | 01234567  | 01234567  | 01234567  | 01234567  | 01234567  | 01234567  | 01234567  | 01234567  | 
Vetor de Status | XXXXXXXX  | 011111X1  | 01111111  | 01111111  | 01111111  | 01111111  | 01111111  | 01111111  | 
=============== +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+

Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1;  3 = Sem-Falha,  Obtem Status de:  2;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6; 

Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1;  3 = Sem-Falha,  Obtem Status de:  2;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6; 

Nodo   2 testou:  3 = Sem-Falha,  ;  0 = Falha       ;  1 = Sem-Falha,  ;  6 = Sem-Falha,  Obtem Status de:  7,  4,  5; 

Nodo   3 testou:  2 = Sem-Falha,  ;  1 = Sem-Falha,  Obtem Status de:  0;  7 = Sem-Falha,  Obtem Status de:  6,  5,  4; 

Nodo   4 testou:  5 = Sem-Falha,  ;  6 = Sem-Falha,  Obtem Status de:  7;  0 = Falha       ;  1 = Sem-Falha,  Obtem Status de:  2,  3; 

Nodo   5 testou:  4 = Sem-Falha,  ;  7 = Sem-Falha,  Obtem Status de:  6;  1 = Sem-Falha,  Obtem Status de:  0,  3,  2; 

Nodo   6 testou:  7 = Sem-Falha,  ;  4 = Sem-Falha,  Obtem Status de:  5;  2 = Sem-Falha,  Obtem Status de:  3,  0,  1; 

Nodo   7 testou:  6 = Sem-Falha,  ;  5 = Sem-Falha,  Obtem Status de:  4;  3 = Sem-Falha,  Obtem Status de:  2,  1,  0; 

=============== +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
        Rodada  |  3        |  3        |  3        |  3        |  3        |  3        |  3        |  3        |
 Numero do Nodo |  0        |  1        |  2        |  3        |  4        |  5        |  6        |  7        |
   Status real  |  0        |  1        |  1        |  1        |  1        |  1        |  1        |  1        |
Numero de testes|  0        | 12        | 12        |  9        | 12        |  9        |  9        |  9        |
                | 01234567  | 01234567  | 01234567  | 01234567  | 01234567  | 01234567  | 01234567  | 01234567  | 
Vetor de Status | XXXXXXXX  | 01111111  | 01111111  | 01111111  | 01111111  | 01111111  | 01111111  | 01111111  | 
=============== +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
Rodadas de testes: 3
   Nodo 0 = 0 testes (0 por rodada)
   Nodo 1 = 12 testes (4 por rodada)
   Nodo 2 = 12 testes (4 por rodada)
   Nodo 3 = 9 testes (3 por rodada)
   Nodo 4 = 12 testes (4 por rodada)
   Nodo 5 = 9 testes (3 por rodada)
   Nodo 6 = 9 testes (3 por rodada)
   Nodo 7 = 9 testes (3 por rodada)
```

### Log 3: "./VCube 4"
```
O nodo 0 falhou no tempo   0.0

Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1;  3 = Sem-Falha,  Obtem Status de:  2;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6;  9 = Sem-Falha,  Obtem Status de:  8, 11, 10, 13, 12, 15, 14; 

Nodo   2 testou:  3 = Sem-Falha,  ;  0 = Falha       ;  1 = Sem-Falha,  ;  6 = Sem-Falha,  Obtem Status de:  7,  4,  5; 10 = Sem-Falha,  Obtem Status de: 11,  8,  9, 14, 15, 12, 13; 

Nodo   3 testou:  2 = Sem-Falha,  ;  1 = Sem-Falha,  Obtem Status de:  0;  7 = Sem-Falha,  Obtem Status de:  6,  5,  4; 11 = Sem-Falha,  Obtem Status de: 10,  9,  8, 15, 14, 13, 12; 

Nodo   4 testou:  5 = Sem-Falha,  ;  6 = Sem-Falha,  Obtem Status de:  7;  0 = Falha       ;  1 = Sem-Falha,  Obtem Status de:  2,  3; 12 = Sem-Falha,  Obtem Status de: 13, 14, 15,  8,  9, 10, 11; 

Nodo   5 testou:  4 = Sem-Falha,  ;  7 = Sem-Falha,  Obtem Status de:  6;  1 = Sem-Falha,  Obtem Status de:  0,  3,  2; 13 = Sem-Falha,  Obtem Status de: 12, 15, 14,  9,  8, 11, 10; 

Nodo   6 testou:  7 = Sem-Falha,  ;  4 = Sem-Falha,  Obtem Status de:  5;  2 = Sem-Falha,  Obtem Status de:  3,  0,  1; 14 = Sem-Falha,  Obtem Status de: 15, 12, 13, 10, 11,  8,  9; 

Nodo   7 testou:  6 = Sem-Falha,  ;  5 = Sem-Falha,  Obtem Status de:  4;  3 = Sem-Falha,  Obtem Status de:  2,  1,  0; 15 = Sem-Falha,  Obtem Status de: 14, 13, 12, 11, 10,  9,  8; 

Nodo   8 testou:  9 = Sem-Falha,  ; 10 = Sem-Falha,  Obtem Status de: 11; 12 = Sem-Falha,  Obtem Status de: 13, 14, 15;  0 = Falha       ;  1 = Sem-Falha,  Obtem Status de:  2,  3,  4,  5,  6,  7; 

Nodo   9 testou:  8 = Sem-Falha,  ; 11 = Sem-Falha,  Obtem Status de: 10; 13 = Sem-Falha,  Obtem Status de: 12, 15, 14;  1 = Sem-Falha,  Obtem Status de:  0,  3,  2,  5,  4,  7,  6; 

Nodo  10 testou: 11 = Sem-Falha,  ;  8 = Sem-Falha,  Obtem Status de:  9; 14 = Sem-Falha,  Obtem Status de: 15, 12, 13;  2 = Sem-Falha,  Obtem Status de:  3,  0,  1,  6,  7,  4,  5; 

Nodo  11 testou: 10 = Sem-Falha,  ;  9 = Sem-Falha,  Obtem Status de:  8; 15 = Sem-Falha,  Obtem Status de: 14, 13, 12;  3 = Sem-Falha,  Obtem Status de:  2,  1,  0,  7,  6,  5,  4; 

Nodo  12 testou: 13 = Sem-Falha,  ; 14 = Sem-Falha,  Obtem Status de: 15;  8 = Sem-Falha,  Obtem Status de:  9, 10, 11;  4 = Sem-Falha,  Obtem Status de:  5,  6,  7,  0,  1,  2,  3; 

Nodo  13 testou: 12 = Sem-Falha,  ; 15 = Sem-Falha,  Obtem Status de: 14;  9 = Sem-Falha,  Obtem Status de:  8, 11, 10;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6,  1,  0,  3,  2; 

Nodo  14 testou: 15 = Sem-Falha,  ; 12 = Sem-Falha,  Obtem Status de: 13; 10 = Sem-Falha,  Obtem Status de: 11,  8,  9;  6 = Sem-Falha,  Obtem Status de:  7,  4,  5,  2,  3,  0,  1; 

Nodo  15 testou: 14 = Sem-Falha,  ; 13 = Sem-Falha,  Obtem Status de: 12; 11 = Sem-Falha,  Obtem Status de: 10,  9,  8;  7 = Sem-Falha,  Obtem Status de:  6,  5,  4,  3,  2,  1,  0; 

=============== +-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
        Rodada  |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |
 Numero do Nodo |  0          |  1          |  2          |  3          |  4          |  5          |  6          |  7          |  8          |  9          | 10          | 11          | 12          | 13          |
   Status real  |  0          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |
Numero de testes|  0          |  4          |  5          |  4          |  5          |  4          |  4          |  4          |  5          |  4          |  4          |  4          |  4          |  4          |
                | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 
Vetor de Status | XXXXXXXXXX  | 01X1X1XXX1  | 0111XX1XXX  | 0111XXX1XX  | 01X1111XXX  | 01X111X1XX  | 01111111XX  | 01111111XX  | 01X1X1XX11  | 01X1X1XX11  | 0111XX1X11  | 0111XXX111  | 01X1111X11  | 01X111X111  | 
=============== +-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+

Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1;  3 = Sem-Falha,  Obtem Status de:  2;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6;  9 = Sem-Falha,  Obtem Status de:  8, 11, 10, 13, 12, 15, 14; 

Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1;  3 = Sem-Falha,  Obtem Status de:  2;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6;  9 = Sem-Falha,  Obtem Status de:  8, 11, 10, 13, 12, 15, 14; 

Nodo   2 testou:  3 = Sem-Falha,  ;  0 = Falha       ;  1 = Sem-Falha,  ;  6 = Sem-Falha,  Obtem Status de:  7,  4,  5; 10 = Sem-Falha,  Obtem Status de: 11,  8,  9, 14, 15, 12, 13; 

Nodo   3 testou:  2 = Sem-Falha,  ;  1 = Sem-Falha,  Obtem Status de:  0;  7 = Sem-Falha,  Obtem Status de:  6,  5,  4; 11 = Sem-Falha,  Obtem Status de: 10,  9,  8, 15, 14, 13, 12; 

Nodo   4 testou:  5 = Sem-Falha,  ;  6 = Sem-Falha,  Obtem Status de:  7;  0 = Falha       ;  1 = Sem-Falha,  Obtem Status de:  2,  3; 12 = Sem-Falha,  Obtem Status de: 13, 14, 15,  8,  9, 10, 11; 

Nodo   5 testou:  4 = Sem-Falha,  ;  7 = Sem-Falha,  Obtem Status de:  6;  1 = Sem-Falha,  Obtem Status de:  0,  3,  2; 13 = Sem-Falha,  Obtem Status de: 12, 15, 14,  9,  8, 11, 10; 

Nodo   6 testou:  7 = Sem-Falha,  ;  4 = Sem-Falha,  Obtem Status de:  5;  2 = Sem-Falha,  Obtem Status de:  3,  0,  1; 14 = Sem-Falha,  Obtem Status de: 15, 12, 13, 10, 11,  8,  9; 

Nodo   7 testou:  6 = Sem-Falha,  ;  5 = Sem-Falha,  Obtem Status de:  4;  3 = Sem-Falha,  Obtem Status de:  2,  1,  0; 15 = Sem-Falha,  Obtem Status de: 14, 13, 12, 11, 10,  9,  8; 

Nodo   8 testou:  9 = Sem-Falha,  ; 10 = Sem-Falha,  Obtem Status de: 11; 12 = Sem-Falha,  Obtem Status de: 13, 14, 15;  0 = Falha       ;  1 = Sem-Falha,  Obtem Status de:  2,  3,  4,  5,  6,  7; 

Nodo   9 testou:  8 = Sem-Falha,  ; 11 = Sem-Falha,  Obtem Status de: 10; 13 = Sem-Falha,  Obtem Status de: 12, 15, 14;  1 = Sem-Falha,  Obtem Status de:  0,  3,  2,  5,  4,  7,  6; 

Nodo  10 testou: 11 = Sem-Falha,  ;  8 = Sem-Falha,  Obtem Status de:  9; 14 = Sem-Falha,  Obtem Status de: 15, 12, 13;  2 = Sem-Falha,  Obtem Status de:  3,  0,  1,  6,  7,  4,  5; 

Nodo  11 testou: 10 = Sem-Falha,  ;  9 = Sem-Falha,  Obtem Status de:  8; 15 = Sem-Falha,  Obtem Status de: 14, 13, 12;  3 = Sem-Falha,  Obtem Status de:  2,  1,  0,  7,  6,  5,  4; 

Nodo  12 testou: 13 = Sem-Falha,  ; 14 = Sem-Falha,  Obtem Status de: 15;  8 = Sem-Falha,  Obtem Status de:  9, 10, 11;  4 = Sem-Falha,  Obtem Status de:  5,  6,  7,  0,  1,  2,  3; 

Nodo  13 testou: 12 = Sem-Falha,  ; 15 = Sem-Falha,  Obtem Status de: 14;  9 = Sem-Falha,  Obtem Status de:  8, 11, 10;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6,  1,  0,  3,  2; 

Nodo  14 testou: 15 = Sem-Falha,  ; 12 = Sem-Falha,  Obtem Status de: 13; 10 = Sem-Falha,  Obtem Status de: 11,  8,  9;  6 = Sem-Falha,  Obtem Status de:  7,  4,  5,  2,  3,  0,  1; 

Nodo  15 testou: 14 = Sem-Falha,  ; 13 = Sem-Falha,  Obtem Status de: 12; 11 = Sem-Falha,  Obtem Status de: 10,  9,  8;  7 = Sem-Falha,  Obtem Status de:  6,  5,  4,  3,  2,  1,  0; 

=============== +-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
        Rodada  |  2          |  2          |  2          |  2          |  2          |  2          |  2          |  2          |  2          |  2          |  2          |  2          |  2          |  2          |
 Numero do Nodo |  0          |  1          |  2          |  3          |  4          |  5          |  6          |  7          |  8          |  9          | 10          | 11          | 12          | 13          |
   Status real  |  0          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |
Numero de testes|  0          | 12          | 10          |  8          | 10          |  8          |  8          |  8          | 10          |  8          |  8          |  8          |  8          |  8          |
                | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 
Vetor de Status | XXXXXXXXXX  | 011111X111  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 011111X111  | 011111X111  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 
=============== +-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+

Nodo   2 testou:  3 = Sem-Falha,  ;  0 = Falha       ;  1 = Sem-Falha,  ;  6 = Sem-Falha,  Obtem Status de:  7,  4,  5; 10 = Sem-Falha,  Obtem Status de: 11,  8,  9, 14, 15, 12, 13; 

Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1;  3 = Sem-Falha,  Obtem Status de:  2;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6;  9 = Sem-Falha,  Obtem Status de:  8, 11, 10, 13, 12, 15, 14; 

Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1;  3 = Sem-Falha,  Obtem Status de:  2;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6;  9 = Sem-Falha,  Obtem Status de:  8, 11, 10, 13, 12, 15, 14; 

Nodo   3 testou:  2 = Sem-Falha,  ;  1 = Sem-Falha,  Obtem Status de:  0;  7 = Sem-Falha,  Obtem Status de:  6,  5,  4; 11 = Sem-Falha,  Obtem Status de: 10,  9,  8, 15, 14, 13, 12; 

Nodo   5 testou:  4 = Sem-Falha,  ;  7 = Sem-Falha,  Obtem Status de:  6;  1 = Sem-Falha,  Obtem Status de:  0,  3,  2; 13 = Sem-Falha,  Obtem Status de: 12, 15, 14,  9,  8, 11, 10; 

Nodo   6 testou:  7 = Sem-Falha,  ;  4 = Sem-Falha,  Obtem Status de:  5;  2 = Sem-Falha,  Obtem Status de:  3,  0,  1; 14 = Sem-Falha,  Obtem Status de: 15, 12, 13, 10, 11,  8,  9; 

Nodo   7 testou:  6 = Sem-Falha,  ;  5 = Sem-Falha,  Obtem Status de:  4;  3 = Sem-Falha,  Obtem Status de:  2,  1,  0; 15 = Sem-Falha,  Obtem Status de: 14, 13, 12, 11, 10,  9,  8; 

Nodo   8 testou:  9 = Sem-Falha,  ; 10 = Sem-Falha,  Obtem Status de: 11; 12 = Sem-Falha,  Obtem Status de: 13, 14, 15;  0 = Falha       ;  1 = Sem-Falha,  Obtem Status de:  2,  3,  4,  5,  6,  7; 

Nodo   9 testou:  8 = Sem-Falha,  ; 11 = Sem-Falha,  Obtem Status de: 10; 13 = Sem-Falha,  Obtem Status de: 12, 15, 14;  1 = Sem-Falha,  Obtem Status de:  0,  3,  2,  5,  4,  7,  6; 

Nodo  10 testou: 11 = Sem-Falha,  ;  8 = Sem-Falha,  Obtem Status de:  9; 14 = Sem-Falha,  Obtem Status de: 15, 12, 13;  2 = Sem-Falha,  Obtem Status de:  3,  0,  1,  6,  7,  4,  5; 

Nodo  11 testou: 10 = Sem-Falha,  ;  9 = Sem-Falha,  Obtem Status de:  8; 15 = Sem-Falha,  Obtem Status de: 14, 13, 12;  3 = Sem-Falha,  Obtem Status de:  2,  1,  0,  7,  6,  5,  4; 

Nodo  12 testou: 13 = Sem-Falha,  ; 14 = Sem-Falha,  Obtem Status de: 15;  8 = Sem-Falha,  Obtem Status de:  9, 10, 11;  4 = Sem-Falha,  Obtem Status de:  5,  6,  7,  0,  1,  2,  3; 

Nodo  13 testou: 12 = Sem-Falha,  ; 15 = Sem-Falha,  Obtem Status de: 14;  9 = Sem-Falha,  Obtem Status de:  8, 11, 10;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6,  1,  0,  3,  2; 

Nodo  14 testou: 15 = Sem-Falha,  ; 12 = Sem-Falha,  Obtem Status de: 13; 10 = Sem-Falha,  Obtem Status de: 11,  8,  9;  6 = Sem-Falha,  Obtem Status de:  7,  4,  5,  2,  3,  0,  1; 

Nodo  15 testou: 14 = Sem-Falha,  ; 13 = Sem-Falha,  Obtem Status de: 12; 11 = Sem-Falha,  Obtem Status de: 10,  9,  8;  7 = Sem-Falha,  Obtem Status de:  6,  5,  4,  3,  2,  1,  0; 

Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1;  3 = Sem-Falha,  Obtem Status de:  2;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6;  9 = Sem-Falha,  Obtem Status de:  8, 11, 10, 13, 12, 15, 14; 

Nodo   1 testou:  0 = Falha       ;  todos falharam no cluster  1;  3 = Sem-Falha,  Obtem Status de:  2;  5 = Sem-Falha,  Obtem Status de:  4,  7,  6;  9 = Sem-Falha,  Obtem Status de:  8, 11, 10, 13, 12, 15, 14; 

Nodo   2 testou:  3 = Sem-Falha,  ;  0 = Falha       ;  1 = Sem-Falha,  ;  6 = Sem-Falha,  Obtem Status de:  7,  4,  5; 10 = Sem-Falha,  Obtem Status de: 11,  8,  9, 14, 15, 12, 13; 

Nodo   3 testou:  2 = Sem-Falha,  ;  1 = Sem-Falha,  Obtem Status de:  0;  7 = Sem-Falha,  Obtem Status de:  6,  5,  4; 11 = Sem-Falha,  Obtem Status de: 10,  9,  8, 15, 14, 13, 12; 

Nodo   4 testou:  5 = Sem-Falha,  ;  6 = Sem-Falha,  Obtem Status de:  7;  0 = Falha       ;  1 = Sem-Falha,  Obtem Status de:  2,  3; 12 = Sem-Falha,  Obtem Status de: 13, 14, 15,  8,  9, 10, 11; 

=============== +-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
        Rodada  |  3          |  3          |  3          |  3          |  3          |  3          |  3          |  3          |  3          |  3          |  3          |  3          |  3          |  3          |
 Numero do Nodo |  0          |  1          |  2          |  3          |  4          |  5          |  6          |  7          |  8          |  9          | 10          | 11          | 12          | 13          |
   Status real  |  0          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |  1          |
Numero de testes|  0          | 28          | 20          | 16          | 15          | 12          | 12          | 12          | 15          | 12          | 12          | 12          | 12          | 12          |
                | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 0123456789  | 
Vetor de Status | XXXXXXXXXX  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 0111111111  | 
=============== +-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
Rodadas de testes: 3
   Nodo 0 = 0 testes (0 por rodada)
   Nodo 1 = 28 testes (9 por rodada)
   Nodo 2 = 20 testes (6 por rodada)
   Nodo 3 = 16 testes (5 por rodada)
   Nodo 4 = 15 testes (5 por rodada)
   Nodo 5 = 12 testes (4 por rodada)
   Nodo 6 = 12 testes (4 por rodada)
   Nodo 7 = 12 testes (4 por rodada)
   Nodo 8 = 15 testes (5 por rodada)
   Nodo 9 = 12 testes (4 por rodada)
   Nodo 10 = 12 testes (4 por rodada)
   Nodo 11 = 12 testes (4 por rodada)
   Nodo 12 = 12 testes (4 por rodada)
   Nodo 13 = 12 testes (4 por rodada)
   Nodo 14 = 12 testes (4 por rodada)
   Nodo 15 = 12 testes (4 por rodada)
```
