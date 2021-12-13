#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int INF = 1000000000;

int main(){
    int n = 0, m = 0;
    scanf("%i %i", &n, &m);

    int** adjacencyMatrix = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        adjacencyMatrix[i] = calloc(n, sizeof(int));

    for (int i = 0; i < m; i++){
        int u = 0, v = 0, w = 0;
        scanf("%i %i %i", &u, &v, &w);
        adjacencyMatrix[u][v] = w;
    }

    int start = 0, finish = 0;
    scanf("%i %i", &start, &finish);
    int* distance = calloc(n, sizeof(int));
    int* previousVertex = calloc(n, sizeof(int));
    bool* used = calloc(n, sizeof(bool));

    for (int i = 0; i < n; i++){
        distance[i] = INF;
        previousVertex[i] = -1;
        used[i] = false;
    }
    distance[start] = 0;

    while (true){
        int v = -1;
        for (int i = 0; i < n; i++)
            if (!used[i] && (v == -1 || distance[v] > distance[i]))
                v = i;

        if (v == -1 || distance[v] == INF)
            break;

        used[v] = true;
        for (int i = 0; i < n; i++)
            if (adjacencyMatrix[v][i] != 0)
                    if (distance[i] > distance[v] + adjacencyMatrix[v][i]){
                        previousVertex[i] = v;
                        distance[i] = distance[v] + adjacencyMatrix[v][i];
                    }
    }
    int currentVertex = finish;
    int length = 1, idx = 1;
    int* path = calloc(n, sizeof(int));
    path[0] = finish;

    while(previousVertex[currentVertex] != -1){
        currentVertex = previousVertex[currentVertex];
        path[idx++] = currentVertex;
        length++;
    }
    printf("%i %i\n", length, distance[finish]);
    for (int i = length-1; i >= 0; i--){
        printf("%i ", path[i]);
    }

    free(path);
    free(distance);
    free(previousVertex);
    free(used);
    for (int i = 0; i < n; i++)
        free(adjacencyMatrix[i]);
    free(adjacencyMatrix);

    return 0;
}
