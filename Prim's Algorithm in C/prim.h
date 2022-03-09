struct Edges{
    int u;
    int v;
};

int toGraph();
int convertToNum(char s);
void printMST(struct Edges mst[MAX], int numOfNodes, int weight);
void prim(int r, struct Edges mst[MAX], int numOfNodes, int graph[MAX][MAX]);
int findMin();