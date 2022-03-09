#include<stdio.h>
#include<stdlib.h>
#include "prim.h"
#include "prim.c"

#define MAX 100


int main()
{
    int weight = 0;
    int n = 0;
    int i;
    struct Edges mst[MAX];
    int graph[MAX][MAX];
    

    n = toGraph(graph);

    prim(0, mst, n, graph);

    printf("\nMST: \n");

    for(i=1; i<=n-1; i++){
		
        printf("(%d, ", mst[i].u);
        printf("%d, ", mst[i].v);
        printf("%d)\n", graph[mst[i].u][mst[i].v]);
        weight += graph[mst[i].u][mst[i].v];
    }
    printf("\nWeight: %d\n", weight);

    return 0;    

}