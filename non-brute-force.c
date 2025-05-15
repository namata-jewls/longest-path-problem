// Namata, Julius Christian I.  | 2022-02219
// Pascual, Jamaika T. | 2021-02167

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define NEG_INF -999999

typedef struct node{
	int x;
	struct node *next;
}graph;

graph **createAdjList(int *, int *);
graph *longestPath(graph **, int *, int *, int *, int *);
void viewLongestPath(graph *);
void viewList(graph **, int);
void deleteGraph(graph **, int);

int main(){
	graph **g, *path;
	int v, e, path_length = -1, best_mask, last_v;
	
	g = createAdjList(&v, &e);
	viewList(g, v);
	
	path = longestPath(g, &v, &path_length, &best_mask, &last_v);
	printf("longest_path_length: %d\n", path_length);
	viewLongestPath(path);

	deleteGraph(g, v);

	return 0;
}

// derived from Bellman-Held-Karp Algorithm for Travelling Salesman Problem
graph *longestPath(graph **g, int *v, int *path_length, int *best_mask, int *last_v){
	graph *path = (graph *) malloc(sizeof(graph)), *adj;
	path->next = NULL;
	int subsets = 1 << *v; // equal to 2^v
	int dp[subsets][*v], parent[subsets][*v], adj_mask;
	memset(parent, -1, sizeof(parent));
	// initialize dp elemetnts to -inf
	for(int i=0; i<subsets; i++)
		for(int j=0; j<*v; j++)
			dp[i][j] = NEG_INF;

	// re-initialize paths starting and ending at the same vertex to zero  
	for(int i=0; i<*v; i++) dp[1 << i][i] = 0;

	for(int mask=0; mask<subsets; mask++){
		for(int curr_v=0; curr_v<*v; curr_v++){
			if(!((1 << curr_v) & mask)) continue; // skip if current vertex not in subset

			// otherwise, check current vertex's adjacent vertices 
			adj = g[curr_v];
			while(adj != NULL){
				// skip if adjacent vertex is also not in subset
				if((1 << adj->x) & mask){ 
					adj_mask = mask ^ (1 << curr_v); // get adj mask by removing the current vertex from the subset mask
				
					if(dp[adj_mask][adj->x] >= 0){
						// get max of dp of curr_v and dp of the adjacent vertex with adj_mask
						// store max to dp of curr_v using current mask
						if (dp[adj_mask][adj->x] + 1 > dp[mask][curr_v]){
							dp[mask][curr_v] = dp[adj_mask][adj->x] + 1;
							parent[mask][curr_v] = adj->x;

							// if dp of current v is bigger than path length 
							// most likely it will be the last vertex in path
							if(dp[mask][curr_v] > *path_length){
								*path_length = dp[mask][curr_v];
								*best_mask = mask;
								*last_v = curr_v;
							}
						}
					}
				}
				adj = adj->next;
			}
		}
	}

	// construct longest path
	int temp = *last_v, mask = *best_mask, prev;
	graph *newNode;
    while (temp != -1) {
    	newNode = (graph*) malloc(sizeof(graph));
    	newNode->x = temp;
    	newNode->next = path->next;
    	path->next = newNode;
		prev = parent[mask][temp];
        mask = mask ^ (1 << temp);
        temp = prev;
    }

	return path;
}

void viewLongestPath(graph *path){
	graph *temp = path->next;
	printf("Longest path: ");
	while(temp != NULL){
		printf("%d", temp->x);
		temp = temp->next;
		temp != NULL ? printf(" -> ") : printf("\n");
	}
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