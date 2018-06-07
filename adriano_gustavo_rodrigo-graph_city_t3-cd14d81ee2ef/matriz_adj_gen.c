#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define TYPES 3
#define SIZE 100

int **Alocar_matriz(int m, int n){
  int **v;  /* ponteiro para a matriz */
  int i;    /* variavel auxiliar      */
  if (m < 1 || n < 1) { /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (NULL);
     }
  /* aloca as linhas da matriz */
  v = (int **) calloc (m, sizeof(int *));
  if (v == NULL) {
     printf ("** Erro: Memoria Insuficiente **");
     return (NULL);
     }
  /* aloca as colunas da matriz */
  for ( i = 0; i < m; i++ ) {
      v[i] = (int*) calloc (n, sizeof(int));
      if (v[i] == NULL) {
         printf ("** Erro: Memoria Insuficiente **");
         return (NULL);
         }
      }
  return (v); /* retorna o ponteiro para a matriz */
}

int **Liberar_matriz (int m, int n, int **v){
  int  i;  /* variavel auxiliar */
  if (v == NULL) return (NULL);
  if (m < 1 || n < 1) {  /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (v);
     }
  for (i=0; i<m; i++)free (v[i]); /* libera as linhas da matriz */
  free (v);      /* libera a matriz (vetor de ponteiros) */
  return (NULL); /* retorna um ponteiro nulo */
}


int main (int argc, char **argv){
	FILE *saida_adj, *saida_type;
	int **matrix, **matrix_type, contador_arestas = 0;
	int booleana = 0;
  int size_matrix = 0;

  if (argc < 3){
    printf ("\t**ERRO NOS PARAMETORS**\nUSO: <%s> <arq_saida> <size_matrix>\n", argv[0]);
    exit (-1);
  }
  if (argv[2] < 0) {
    printf ("\t**TAMANHO PRECISA SER UM NÚMERO MAIOR QUE 1**\n");
    exit (-1);
  }
  size_matrix = atoi(argv[2]); //recebe do parametro o tamanho da matriz
	matrix = Alocar_matriz(size_matrix, size_matrix);
	saida_adj = fopen(argv[1], "w");
  if (saida_adj == NULL) {
    printf ("\t**ERRO NOS PARAMETORS**\nUSO: <%s> <arq_saida> <size_matrix>\n", argv[0]);
    exit (-1);
  }
  matrix_type = Alocar_matriz(size_matrix, size_matrix);

	int MAX_ARESTAS = 4 * (size_matrix * (size_matrix))/2;

	srand ((unsigned) time(NULL));
	for (int i=0; i < size_matrix; i++){ //linha
			for (int j=0; j < size_matrix ;j++){ //coluna dupla, pra ir o Tipo
					booleana = rand() % 4;
					if (booleana == 0){ //so entra se for 0
						if (contador_arestas < MAX_ARESTAS){ //se o contador passar de 4 entao n conta mais
							matrix[i][j] = (rand()%SIZE)+150;  //um numero de (0 a 99) + 150
							contador_arestas++;
						}
					}
				}

	}
  fprintf (saida_adj, "%d %d\n", size_matrix, size_matrix);

	for (int i=0; i < size_matrix; i++){ //linha
			for (int j=0; j < size_matrix; j++){ //coluna
				fprintf (saida_adj, "%d ", matrix[i][j]);
			}
			fprintf(saida_adj, "\n");
	}
  printf ("SUCCESS\nMATRIZ %dx%d CRIADA!\n", size_matrix, size_matrix);


	matrix = Liberar_matriz(size_matrix, size_matrix, matrix);
  fclose(saida_adj);

	return 0;
}
