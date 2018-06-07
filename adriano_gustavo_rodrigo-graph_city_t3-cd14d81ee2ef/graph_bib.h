#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>

#define NUM_THREADS 1
#define VEL_MAX_RUA 666		//metros por minuto
#define VEL_MAX_AVE 1000 	//metros por minuto
#define VEL_MAX_EST 1666	//metros por minuto
#define TRUE 1
#define FALSE 0

typedef struct grafo {
	float comprimento;//em metros
	int tipo;
	float tempo;	//em minutos
	int trafego;	//porcentagem
} grafo_t;

FILE *arq, *arq2;
int infinity;
int no_verts;
int q_size;
float *queue;
float *dist;
int *predecessor;
int linhas, colunas;
float trafego;
float velocidade_rua;
float velocidade_avenida;
float velocidade_estrada;
grafo_t **adjacent;
pthread_mutex_t mutex;


void dijkstra_caminho(int s);
void dijkstra_time(int s);

void dijkstra_saida();
void zera_vetores();
void alocadora();
void inicializa_matriz();
int rand_num(int min_num, int max_num);
int requires_attention(int x, int i, float peso);
int delete_min();
int q_not_empty();
int le(int *x);
void relax_edge(int x, int i, float peso);
void print_shortest_path(int s, int k);
void init_Q();
void *gera_trafego(void *threadid);
void gera_entrada();
void sleep_ms(unsigned int mseconds);
