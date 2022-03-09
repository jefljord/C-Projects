#include<stdio.h>
#include<stdlib.h>
#include "prim.h"

#define MAX 100
#define infinity 2147483647

int convertToNum(char s){
	    
	int num = 0;
	for (char a = 'a'; a <= 'z'; a++) {
        if (a == s) {
        			
		    num = (a-'a');
        			
        }
	        
	}
	    
	return num;
	
}

void prim(int r, struct Edges mst[MAX], int numOfNodes, int graph[MAX][MAX]){
	
    int first[MAX];
    int check[MAX];
    int length[MAX];
    int curr,i;
    int count = 0;
        
    for(i=0; i<numOfNodes; i++){
		
        first[i] = -1;
        length[i] = infinity;
        check[i] = 0;
    }

    length[r] = 0;

    while(1){
		
        curr = findMin(numOfNodes, check, length);

        if(curr == -1){
			
            if(count == numOfNodes-1) 
                return;
				
            else{				
                printf("\nNo path for mst\n");
                exit(1);
            }
			
        }
               
        check[curr] = 1;
                
        if(curr != r){
			
            count++;
            mst[count].u = first[curr];
            mst[count].v = curr;
        }

        for(i=0; i<numOfNodes; i++){
            if(graph[curr][i] > 0 && check[i] == 0){
				if(graph[curr][i] < length[i]){					
                    first[i] = curr;
                    length[i] = graph[curr][i];
                }
			}
        }
	}
}

int findMin(int numOfNodes, int check[MAX], int length[MAX]){
	
    int i;
    int min = infinity;
    int k = -1;

    for(i=0; i<numOfNodes; i++){
		
        if(check[i] == 0 && length[i] < min){			
            min = length[i];
            k = i;
        }
		
    }

    return k;
	
}

int toGraph(int graph[MAX][MAX]){
	
    int i,start,end,cost;
    char a, b;
    int nodes = 0;
    
    printf("Graph:\n");
        
    FILE *fptr = fopen("input.txt","r");
       
    char buf[512];
    while (fgets(buf, sizeof buf, fptr) != 0) {
        sscanf(buf, "%c %c %d", &a, &b, &cost);
        printf("(%c, %c, %d)\n", a, b, cost);        
        start = convertToNum(a);
        end = convertToNum(b);
            
        graph[start][end] = cost;
        graph[end][start] = cost;
        nodes += 1;
            
    }
    
    fclose(fptr);
    return nodes;
        
}