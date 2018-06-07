#include <graph_bib.h>

int main(int argc, char **argv){

	int i = 0, j = 0;
	infinity = 999999;
	trafego = 50;
	pthread_t tra_thread;
	pthread_attr_t attr;
	int rc;
	
	arq = fopen(argv[1], "r");
	if (arq == NULL) {
		printf("ERRO na abertura do arquivo %s!\n", argv[1]);
		exit(-1);
	}
	fscanf(arq, "%d %d", &linhas, &colunas);
	
	no_verts = linhas;
	alocadora();
	inicializa_matriz();

	#if defined(GERA_ARQ)
		gera_entrada();
		return 0;
	#endif
	
	arq2 = fopen(argv[2], "r");
	if (arq2 == NULL) {
		printf("ERRO na abertura do arquivo %s!\n", argv[2]);
		exit(-1);
	}
	
	rc = pthread_create(&tra_thread, NULL, gera_trafego, (void *)0);
	if (rc){
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	pthread_mutex_init(&mutex, NULL);
	dijkstra_saida();
	pthread_mutex_destroy;
	return 0;
}
