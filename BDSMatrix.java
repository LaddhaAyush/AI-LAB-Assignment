import java.util.LinkedList;
import java.util.Queue;

public class BFSMatrix {
    private int vertices;
    private int[][] adjMatrix;

    // Constructor
    public BFSMatrix(int v) {
        vertices = v;
        adjMatrix = new int[v][v];
    }

    // Add edge to the graph (0-indexed)
    void addEdge(int src, int dest) {
        adjMatrix[src][dest] = 1;
        adjMatrix[dest][src] = 1; // For undirected graph
    }

    // BFS algorithm
    void BFS(int startVertex) {
        boolean[] visited = new boolean[vertices];
        Queue<Integer> queue = new LinkedList<>();

        visited[startVertex] = true;
        queue.add(startVertex);

        while (!queue.isEmpty()) {
            int current = queue.poll();
            System.out.println("Visited " + current);

            for (int i = 0; i < vertices; i++) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    queue.add(i);
                }
            }
        }
    }

    // Main method
    public static void main(String[] args) {
        BFSMatrix graph = new BFSMatrix(6);

        graph.addEdge(0, 1);
        graph.addEdge(0, 2);
        graph.addEdge(1, 3);
        graph.addEdge(1, 4);
        graph.addEdge(2, 5);

        System.out.println("Breadth First Search starting from vertex 0:");
        graph.BFS(0);
    }
}
