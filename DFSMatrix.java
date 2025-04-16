public class DFSMatrix {
    private int vertices;
    private int[][] adjMatrix;

    // Constructor
    public DFSMatrix(int v) {
        vertices = v;
        adjMatrix = new int[v][v];
    }

    // Add edge to the graph (0-indexed)
    void addEdge(int src, int dest) {
        adjMatrix[src][dest] = 1;
        adjMatrix[dest][src] = 1; // For undirected graph
    }

    // DFS algorithm (recursive)
    void DFS(int startVertex) {
        boolean[] visited = new boolean[vertices];
        dfsUtil(startVertex, visited);
    }

    // Helper method for DFS
    void dfsUtil(int current, boolean[] visited) {
        visited[current] = true;
        System.out.println("Visited " + current);

        for (int i = 0; i < vertices; i++) {
            if (adjMatrix[current][i] == 1 && !visited[i]) {
                dfsUtil(i, visited);
            }
        }
    }

    // Main method
    public static void main(String[] args) {
        DFSMatrix graph = new DFSMatrix(6);

        graph.addEdge(0, 1);
        graph.addEdge(0, 2);
        graph.addEdge(1, 3);
        graph.addEdge(1, 4);
        graph.addEdge(2, 5);

        System.out.println("Depth First Search starting from vertex 0:");
        graph.DFS(0);
    }
}
