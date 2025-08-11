#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int u, v, weight;
} Edge;

typedef struct {
    int parent;
    int rank;
} Subset;

Subset* createSubsets(int n) {
    Subset* subsets = (Subset*)malloc(n * sizeof(Subset));
    for (int i = 0; i < n; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }
    return subsets;
}

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void unionByRank(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);
    
    if (rootX != rootY) {
        if (subsets[rootX].rank > subsets[rootY].rank) {
            subsets[rootY].parent = rootX;
        } else if (subsets[rootX].rank < subsets[rootY].rank) {
            subsets[rootX].parent = rootY;
        } else {
            subsets[rootY].parent = rootX;
            subsets[rootX].rank++;
        }
    }
}

int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

void kruskal(Edge edges[], int numEdges, int V) {
    qsort(edges, numEdges, sizeof(Edge), compare);
    
    Subset* subsets = createSubsets(V);
    
    int mstWeight = 0;
    int mstEdges = 0;
    
    printf("\nSelected Edges in the MST:\n");
    
    for (int i = 0; i < numEdges && mstEdges < V - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        int rootU = find(subsets, u);
        int rootV = find(subsets, v);

        if (rootU != rootV) {
            printf("%c - %c : %d\n", 'A' + u, 'A' + v, edges[i].weight);
            mstWeight += edges[i].weight;
            mstEdges++;
            unionByRank(subsets, rootU, rootV);
        }
    }
    
    printf("\nTotal Minimum Cost = %d\n", mstWeight);
    free(subsets);
}

int charToIndex(char c) {
    c = toupper(c);
    return c - 'A';
}

int main() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    Edge* edges = (Edge*)malloc(E * sizeof(Edge));

    printf("Enter the edges (format: u v cost):\n");
    for (int i = 0; i < E; i++) {
        char uChar, vChar;
        int cost;
        scanf(" %c %c %d", &uChar, &vChar, &cost);
        edges[i].u = charToIndex(uChar);
        edges[i].v = charToIndex(vChar);
        edges[i].weight = cost;
    }

    kruskal(edges, E, V);
    free(edges);
    return 0;
}
