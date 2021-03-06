# dijkstra
menor caminho utilizando dijkstra

POR ADRIANO GARCIA, RODRIGO MASERA e GUSTAVO RODRIGUES.

Para este trabalho foi utilizado um algoritmo de Dijkstra implementado em Java que está disponível no link abaixo:

http://www.cs.cmu.edu/~ab/Desktop/15-211%20Archive/res00117/Dijkstra.java

Para compilar o programa, deve ser utilizado o comando 'make' no respectivo diretório.

O programa possui duas entradas. A primeira consiste de um arquivo contendo uma matriz de adjacência. Nesse arquivo, a primeira linha representa o tamanho da matriz e as seguintes representam a própria matriz, de acordo com o exemplo abaixo:

4 4
x x x x
x x x x
x x x x
x x x x

A segunda entrada consiste de um arquivo contendo uma lista de caminhos a serem computados. Esse arquivo deve possuir um valor inteiro representando um nó inicial e outro representando um nó final, de acordo com o exemplo abaixo:

x y
y z
z x

Para executar o programa, os dois arquivos de entrada devem ser passados como parâmetro, seguindo o formato abaixo:

Exemplo de execução: '$./dijkstra <matriz_adjacencia.txt> <lista_buscas.txt>'.

A saída do programa consiste do caminho mais curto e do caminho mais rápido entre os vértices de entrada.

*************************************************************
OBSERVAÇÃO¹: Caso seja necessário criar uma lista de vértices para busca, o programa possui uma função que busca todos os caminhos baseados em uma matriz de adjacência existente. Essa função pode ser acessada habilitando a macro -DGERA_ARQ no makefile e executando:

'$./dijkstra <matriz_adjacencia.txt> > <lista_buscas.txt>'.

OBSERVAÇÃO²: Caso seja necessário criar uma matriz de adjacencia, basta executar o arquivo gerador de matrizes:
'$.gcc -o gerador gen_matriz_adj.c'.
'$./gerador arq_saida.txt TAMANHO_DA_MATRIZ'.

*************************************************************
