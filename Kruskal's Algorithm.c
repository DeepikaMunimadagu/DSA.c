#include <stdio.h>
#include <stdlib.h>

#define MAX_V 10  // Maximum number of vertices in the graph
#define MAX_E 20  // Maximum number of edges in the graph

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int v, int e) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = v;
    graph->E = e;
    graph->edge = (struct Edge*)malloc(e * sizeof(struct Edge));
    return graph;
}

int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void Union(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

int myComp(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    int* parent = (int*)malloc(V * sizeof(int));

    for (int v = 0; v < V; v++)
        parent[v] = -1;

    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edge[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(parent, x, y);
        }
    }

    printf("Edge \tWeight\n");
    for (i = 0; i < e; i++)
        printf("%d - %d \t%d\n", result[i].src, result[i].dest, result[i].weight);
}

int main() {
    int V, E;

    printf("Enter the number of vertices (max %d): ", MAX_V);
    scanf("%d", &V);

    printf("Enter the number of edges (max %d): ", MAX_E);
    scanf("%d", &E);

    struct Graph* graph = createGraph(V, E);

    // Add edges
    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }

    kruskalMST(graph);

    return 0;
}
