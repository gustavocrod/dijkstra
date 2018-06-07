#include <graph_bib.h>

void dijkstra_caminho(int s){
	int i;
	zera_vetores();
	for(i=0; i<no_verts; i++){
		dist[i] = infinity;
		predecessor[i] = -1;
	}
	dist[s] = 0;
	init_Q();
	while(q_not_empty()){
		int x = delete_min();
		for(i=0; i<no_verts; i++){
    	if(adjacent[x][i].comprimento!=0){
				if(requires_attention(x, i, adjacent[x][i].comprimento)){
					pthread_mutex_lock(&mutex);
					relax_edge(x, i, adjacent[x][i].comprimento);
					pthread_mutex_unlock(&mutex);
				}
			}
		}
	}
}

void dijkstra_time(int s){
	int i;
	zera_vetores();
	for(i=0; i<no_verts; i++){
		dist[i] = infinity;
		predecessor[i] = -1;
	}
	dist[s] = 0;
	init_Q();
	while(q_not_empty()){
		int x = delete_min();
		for(i=0; i<no_verts; i++){
    			if(adjacent[x][i].comprimento!=0){
				if(requires_attention(x, i, adjacent[x][i].tempo)){
					pthread_mutex_lock(&mutex);
					relax_edge(x, i, adjacent[x][i].tempo);
					pthread_mutex_unlock(&mutex);
				}
			}
		}
	}
}

int requires_attention(int x, int i, float peso){
	if(dist[i]>dist[x]+peso){
		return TRUE;
	} else {
		return FALSE;
	}
}

void relax_edge(int x, int i, float peso){
	dist[i] = dist[x]+peso;
	predecessor[i] = x;
}

void print_shortest_path(int s, int k){
	if(s==k){
		printf("%d", s);
		return;
	}
	if(predecessor[k]==-1){
		printf("CAMINHO INEXISTENTE!");
		return;
	}
	print_shortest_path(s, predecessor[k]);
	printf(" -> %d", k);
}

void init_Q(){
	q_size = no_verts;
	int i;
	for(i=0; i<no_verts; i++){
		queue[i] = dist[i];
	}
}
int delete_min(){
	q_size--;
	int min = 0;
	int i;
	for(i = 0; i<no_verts; i++){
		if(queue[i]<queue[min])
    			min = i;
	}
	int ret = min;
	queue[min] = infinity+1;
	return ret;
}

int q_not_empty(){
	if(q_size>0){
		return TRUE;
	}else{
		return FALSE;
	}
}
