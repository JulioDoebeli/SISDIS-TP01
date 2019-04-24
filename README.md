## TRABALHO PRÁTICO 0
### Algoritmo de diagnóstico Adaptive-DSD, Primeiro trabalho de Sistemas Distribuídos - CI088 
Trabalho Prático 1, Simulação do Algoritmo Adaptive-DSD em ambiente SMPL,Disciplina de Sistemas Distribuídos, UFPR, 1 Semestre de 2019

### Especificação
  Implemente o algoritmo VCube no ambiente de simulação SMPL, e mostre resultados para diversos valores de N e diversos eventos - um evento de cada vez, um evento só ocorre depois do evento anterior ser diagnosticado. Para cada evento mostre claramente o número de testes executados e a latência para completar o diagnóstico do evento. Cada nodo mantém o vetor STATE[0..N-1] de contadores de eventos, inicializado em -1 (estado unknown). Assume-se que os nodos são inicializados sem-falha, a entrada correspondente ao nodo no vetor STATE[] do testador é setada para zero. Ao descobrir um novo evento em um nodo testado, o testador incrementa a entrada correspondente no vetor STATE[].

Para a transferência de informações de diagnóstico lembre-se da estratégia do VCube: quando um nodo sem-falha testa outro nodo sem-falha obtém informações sobre "novidades". Basta comparar os vetores STATE para saber se o testado tem alguma novidade.

Importante: em cada intervalo de testes todos os testadores executam todos os testes assinalados.

Atenção: Data para disponibilizar o trabalho: 24 de abril de 2019 (quarta-feira) O prazo para fazer o trabalho é de mais de 3 semanas -- este prazo não será prorrogado! 
Os alunos devem informar por e-mail a URL do trabalho, usando o subject "TP1 SISDIS 2019-1"

O trabalho deve ser feito individualmente! 
Deve ser feita uma página Web, que contém:

Relatório HTML explicando como o trabalho foi feito (use desenhos, palavras, o que você quiser): o objetivo é detalhar as suas decisões para implementar seu trabalho.
Código fonte dos programas, comentados. ATENÇÃO: acrescente a todo programa a terminação ".txt" para que possa ser diretamente aberto em um browser. Exemplos: cliente.py.txt ou servidor.c.txt
Log dos testes executados: mostre explicitamente diversos casos testados, lembre-se é a partir desta listagem de testes que o professor vai medir até que ponto o trabalho está funcionando. 
Veja este programa exemplo para ilustrar a criação de um bom log.

### Tarefa 0
Editar, Compilar, Executar o programa tempo.c

### Tarefa 1
Cada Nodo Sem Falha Testa o Seguinte no Anel
### Tarefa 2
Cada Nodo Sem Falha Testa os Seguintes no Anel Sequencialmente até encontrar outro nodo sem falha
### Tarefa 3
Cada Nodo Sem Falha Mantem Localmente um vetor com os estados dos nodos e atualiza o estado com resultado de cada teste próprio. 
### Tarefa 4
Cada Nodo Sem Falha Mantem vetor de estados e o atualiza com informação de outro nodo sem falha após testa-lo.


## TRABALHO PRÁTICO 1
### Especificação
Implemente o algoritmo VCube no ambiente de simulação SMPL, e mostre resultados para diversos valores de N e diversos eventos - um evento de cada vez, um evento só ocorre depois do evento anterior ser diagnosticado. Para cada evento mostre claramente o número de testes executados e a latência para completar o diagnóstico do evento. Cada nodo mantém o vetor STATE[0..N-1] de contadores de eventos, inicializado em -1 (estado unknown). Assume-se que os nodos são inicializados sem-falha, a entrada correspondente ao nodo no vetor STATE[] do testador é setada para zero. Ao descobrir um novo evento em um nodo testado, o testador incrementa a entrada correspondente no vetor STATE[].

Para a transferência de informações de diagnóstico lembre-se da estratégia do VCube: quando um nodo sem-falha testa outro nodo sem-falha obtém informações sobre "novidades". Basta comparar os vetores STATE para saber se o testado tem alguma novidade.

Importante: em cada intervalo de testes todos os testadores executam todos os testes assinalados.
```
Algoritmo Hi-ADSD executado no nodo i
repita
  para s ← 1 ate´ log2 N fac¸a
  repita
    node to test := pr´oximo nodo em ci,s
    teste(node to test)
    se node to test esta´ sem-falha entao˜
      atualiza informac¸ ˜ao de diagn´ostico do cluster
      ate´ node to test esta´ sem-falha ou todos os nodos em ci,s estao falhos ˜
    se todos os nodos em ci,s estao falhos ˜ entao˜
      apaga informac¸ ˜oes de diagn´ostico do cluster
    durma ate´ o proximo intervalo de testes ´
para sempre
```
