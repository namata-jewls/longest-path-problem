// Namata, Julius Christian I.  | 2022-02219
// Pascual, Jamaika T. | 2021-02167

#include<stdio.h>
#include<malloc.h>

typedef struct node{
	int x;
	struct node *next;
}graph;

graph **createAdjList(int *, int *);
void viewList(graph **, int);
void deleteGraph(graph **, int);

int main(){
	graph **g;
	int v, e;
	
	g = createAdjList(&v, &e);
	viewList(g, v);
	
	deleteGraph(g, v);

	return 0;
}

graph **createAdjList(int *v, int *e){
	/*insert code here for creating an adjacency list*/
	FILE *fptr;
	int source, dest;
	graph *temp = malloc(sizeof(graph));
	// Open a file in read mode
	fptr = fopen("tests/graph.in", "r"); 
	fscanf(fptr, "%d", v); 
	fscanf(fptr, "%d", e);
	
	graph **g = (graph**) malloc(sizeof(graph*) * *v);
	// create graph rows using vertices
	for(int i=0; i<*v; i++){
		graph *newNode = (graph*) malloc(sizeof(graph));
		g[i] = NULL;
	}
	// edge cases for creating adjacency list
	if (*v <= 1 || *e < 1){
		return g;
	}

	// create edges
	for(int i=0; i<*e; i++){
		fscanf(fptr, "%d %d", &source, &dest); // get connected vertices of edge
		// create source to dest edge
		graph *newNode = (graph*) malloc(sizeof(graph));
		newNode->x = dest;
		temp = g[source];
		g[source] = newNode;
		newNode->next = temp;
		
		// create dest to source edge
		newNode = (graph*) malloc(sizeof(graph));
		newNode->x = source;
		temp = g[dest];
		g[dest] = newNode;
		newNode->next = temp;

	}

	return g;

}

void viewList(graph **g, int v){
	int i;
	graph *p;
	
	for(i = 0; i < v; i++){
		p = g[i];
		printf("%d: ", i);
		//traverse the list connected to vertex i
		while(p != NULL){
			printf("%3d", p->x);
			p = p->next;
		}
		printf("\n");
	}
}

void deleteGraph(graph **g, int v){
	int i;
	graph *p;
	for(i = 0; i < v; i++){
		while(g[i] != NULL){
			p = g[i];
			g[i] = g[i]->next;
			free(p);
		}
	}
	free(g);
}