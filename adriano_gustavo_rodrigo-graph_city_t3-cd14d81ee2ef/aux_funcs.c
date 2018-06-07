#include <graph_bib.h>


void dijkstra_saida(){
	int inicial, final;
	while (fscanf(arq2, "%d %d", &inicial, &final) != EOF){
		if(inicial > linhas || final > linhas || inicial < 0 || final < 0){
			printf("Vértices %d e %d\n", inicial, final);
			printf("Nó inicial ou nó final inexistentes\n");
		} else {
			dijkstra_caminho(inicial);
			printf("Vértices %d e %d\n", inicial, final);
			printf("Caminho mais curto:\t");
			print_shortest_path(inicial, final);

			dijkstra_time(inicial);
			printf("\nCaminho mais rápido:\t");
			print_shortest_path(inicial, final);
		}
		printf("\n\n");
	}
}

int le(int *x){
	if (scanf(" %d", &*x) == 0) {
	getchar();
		return TRUE;
	} else {
		return FALSE;
	}
}

void alocadora(){
	int i;
	queue = (float *) malloc(linhas * sizeof(float));
	dist = (float *) malloc(linhas * sizeof(float));
	predecessor = (int *) malloc(linhas * sizeof(int));
	adjacent = (grafo_t **) malloc(linhas * sizeof(grafo_t *));
	for (i = 0; i < linhas; i++) {
		adjacent[i] = (grafo_t *) malloc(colunas * sizeof(grafo_t));
	}

}

void zera_vetores(){
	int i;
	for(i = 0; i < no_verts; i++){
		queue[i] = 0.0;
		dist[i] = 0.0;
		predecessor[i] = 0;
	}
}

void inicializa_matriz(){
	int i = 0, j = 0;
	while (i < linhas && j < colunas && (fscanf(arq, "%f", &adjacent[i][j].comprimento) != EOF)) {
		if(adjacent[i][j].comprimento != 0){
			int rand_n = 1+(rand()%3);
			adjacent[i][j].tipo = rand_n;
			adjacent[i][j].trafego = 50;
			switch(rand_n){
				case 1:
					adjacent[i][j].tempo = (float)adjacent[i][j].comprimento/(float)VEL_MAX_RUA;
					break;
				case 2:
					adjacent[i][j].tempo = (float)adjacent[i][j].comprimento/(float)VEL_MAX_AVE;
					break;
				case 3:
					adjacent[i][j].tempo = (float)adjacent[i][j].comprimento/(float)VEL_MAX_EST;
					break;
				default:
					break;
			}
		}
		j++;
		if (i >= linhas)
			i = 0;
		if (j >= colunas){
			j = 0;
			i++;
		}
	}
}

void sleep_ms(unsigned int mseconds){
    clock_t goal = (mseconds*1000) + clock();
    while (goal > clock());
}

void *gera_trafego(void *threadid){
	long tid;
	tid = (long)threadid;
	int i, j, aux;

	while(1){
		//escolhe uma linha aleatoria da matriz e atualiza os valores dessa linha
		i = rand_num (0, linhas-1);
		for (j = 0; j < colunas; j++){
			if(adjacent[i][j].comprimento != 0){
				trafego = adjacent[i][j].trafego;	//recupera o trafego mais recente
				aux = rand_num(0,100);
				if (aux >= 50){				//atualiza o trafego randomicamente e linearmente
					if (trafego < 100)
						trafego += 10;
				}else {
					if (trafego > 0)
						trafego -= 10;
				}
				adjacent[i][j].trafego = trafego;	//salva o trafego atual

				//atualiza as velocidades por tipo de via
				if (VEL_MAX_RUA-((trafego/100.0)*(float)VEL_MAX_RUA) >= (VEL_MAX_RUA/5.0))
					velocidade_rua = VEL_MAX_RUA-((trafego/100.0)*(float)VEL_MAX_RUA);
				if (VEL_MAX_AVE-((trafego/100.0)*(float)VEL_MAX_AVE) >= (VEL_MAX_AVE/5.0))
					velocidade_avenida = VEL_MAX_AVE-((trafego/100.0)*(float)VEL_MAX_AVE);
				if (VEL_MAX_EST-((trafego/100.0)*(float)VEL_MAX_EST) >= (VEL_MAX_EST/5.0))
					velocidade_estrada = VEL_MAX_EST-((trafego/100.0)*(float)VEL_MAX_EST);

				//atualiza o tempo para percorrer cada via de acordo com o respectivo trafego
				int tipo = adjacent[i][j].tipo;
				switch(tipo){
					case 1:
						adjacent[i][j].tempo = adjacent[i][j].comprimento/velocidade_rua;
						break;
					case 2:
						adjacent[i][j].tempo = adjacent[i][j].comprimento/velocidade_avenida;
						break;
					case 3:
						adjacent[i][j].tempo = adjacent[i][j].comprimento/velocidade_estrada;
						break;
					case 0:
						adjacent[i][j].tempo = 0;
						break;
					default:
						break;
				}
				//sleep_ms(100);
			}
		}
	}
	pthread_exit(NULL);
}

int rand_num(int min_num, int max_num){
	int result=0,low_num=0,hi_num=0;
	if(min_num<max_num){
		low_num=min_num;
		hi_num=max_num+1;
	}else{
		low_num=max_num+1;
		hi_num=min_num;
	}
	srand(time(NULL));
	result = (rand()%(hi_num-low_num))+low_num;
	return result;
}

void gera_entrada(){
	int i, j;
	for (i = 0; i < linhas+10; i++){
		for (j = 0; j < colunas+20; j++) {
			if (i != j)
				printf("%d %d\n", i, j);
		}
	}
}
