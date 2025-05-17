// Namata, Julius Christian I.  | 2022-02219
// Pascual, Jamaika T. | 2021-02167

#include<stdio.h>
#include<malloc.h>
#include <stdbool.h>
#include<time.h>
#define MAX_V 100

typedef struct node{
	int x;
	struct node *next;
}graph;

graph **createAdjList(int *, int *);
void viewList(graph **, int);
void deleteGraph(graph **, int);
int  bruteLongestPath(graph **g, int v);
void dfsLongest(graph **g, int u, bool visited[], int depth, int *maxLen);
void viewLongestPath(int len);
int bestPath[MAX_V];
int currentPath[MAX_V];

int main(){
	graph **g;
	int v, e;
	clock_t time_before, time_after;
	
	g = createAdjList(&v, &e);
	viewList(g, v);

	time_before = clock();
	int longest = bruteLongestPath(g, v);
	time_after = clock();

    printf("\nLongest path length: %d\n", longest);
	viewLongestPath(longest);
	
	double time_elapsed = (double) (time_after - time_before) / CLOCKS_PER_SEC; 
	printf("time elapsed: %f\n", time_elapsed);

	deleteGraph(g, v);

	return 0;
}

graph **createAdjList(int *v, int *e){
	/*insert code here for creating an adjacency list*/
	FILE *fptr;
	int source, dest;
	graph *temp = malloc(sizeof(graph));
	// Open a file in read mode
	fptr = fopen("tests/sparse/24.in", "r"); 
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

//brute-force
int bruteLongestPath(graph **g, int v){ 
    bool *visited = calloc(v, sizeof(bool)); //track visited vertices
    int maxLen  = 0; //stores the length of the longest path found

	//for each possible starting vertex i
    for(int i = 0; i < v; i++){
        //reset visited[] for each starting vertex
        for(int j = 0; j < v; j++){
            visited[j] = false;
        }
        visited[i] = true; //mark i as visited and start DFS from i
		currentPath[0] = i; // initialize currentPath with the starting vertex
        dfsLongest(g, i, visited, 0, &maxLen); // perform DFS from vertex i
    }

    free(visited);
    return maxLen;
}

void dfsLongest(graph **g, int u, bool visited[], int depth, int *maxLen){
	//update the max path length and store the current path if this one is longer
    if(depth > *maxLen) {
        *maxLen = depth;
		for (int i = 0; i <= depth; i++) {
				bestPath[i] = currentPath[i];
			}
		}

	 //explore all unvisited neighbors of vertex u
    for(graph *p = g[u]; p; p = p->next){
		int w = p->x; //neighbor vertex index
        if(!visited[w]){
            visited[w] = true; //mark neighbor as visited
			currentPath[depth + 1] = w; // add neighbor to current path
            dfsLongest(g, w, visited, depth + 1, maxLen); //recurse with increased path length
            visited[w] = false; //backtrack: unmark neighbor
        }
    }
}

void viewLongestPath(int len) {
    printf("Longest path: ");
    for (int i = 0; i <= len; i++) {
        printf("%d", bestPath[i]);
        if (i < len) printf(" -> ");
    }
    printf("\n");
}
