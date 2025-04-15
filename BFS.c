#include <stdio.h>
#include <stdlib.h>

int graph[100][100];
int visited[100];
int queue[100];
int front = -1, rear = -1;

void addEdge(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1; 
}

void dfs(int node, int n) {
    visited[node] = 1;
    printf("%d ", node);
    
    for (int i = 0; i < n; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i, n);
        }
    }
}

void enqueue(int node) {
    if (rear == 100 - 1) {
        printf("Queue is full\n");
        return;
    }
    if (front == -1) front = 0;
    queue[++rear] = node;
}

int dequeue() {
    if (front == -1 || front > rear) {
        return -1;
    }
    return queue[front++];
}

void bfs(int start, int n) {
    for (int i = 0; i < n; i++) visited[i] = 0;
    
    enqueue(start);
    visited[start] = 1;
    
    while (front <= rear) {
        int node = dequeue();
        printf("%d ", node);
        
        for (int i = 0; i < n; i++) {
            if (graph[node][i] && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int nodes, edges, u, v;
    
    printf("Enter number of nodes and edges: ");
    scanf("%d %d", &nodes, &edges);
    
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            graph[i][j] = 0;
        }
    }
    
    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    
    printf("\nDFS traversal starting from node 0:\n");
    for (int i = 0; i < nodes; i++) visited[i] = 0;
    dfs(0, nodes);
    
    printf("\n\nBFS traversal starting from node 0:\n");
    bfs(0, nodes);
    
    return 0;
}
