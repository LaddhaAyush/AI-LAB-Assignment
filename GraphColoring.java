import java.util.Arrays;

class GraphColoring {
    static final int V = 4;

    static boolean isSafe(int v, int[][] graph, int[] color, int c) {
        for (int i = 0; i < V; i++) {
            if (graph[v][i] == 1 && color[i] == c) 
                return false;
        }
        return true;
    }

    static boolean graphColoringUtil(int[][] graph, int m, int[] color, int v) {
        if (v == V) 
            return true;

        for (int c = 1; c <= m; c++) {
            if (isSafe(v, graph, color, c)) {
                color[v] = c;

                if (graphColoringUtil(graph, m, color, v + 1)) 
                    return true;

                color[v] = 0;
            }
        }
        return false;
    }

    static boolean graphColoring(int[][] graph, int m) {
        int[] color = new int[V];
        Arrays.fill(color, 0);

        if (!graphColoringUtil(graph, m, color, 0)) {
            System.out.println("Solution does not exist");
            return false;
        }

        System.out.println("Solution exists:");
        for (int i = 0; i < V; i++)
            System.out.println("Vertex " + i + " ---> Color " + color[i]);

        return true;
    }

    public static void main(String[] args) {
        int[][] graph = {
            {0, 1, 1, 1},
            {1, 0, 1, 0},
            {1, 1, 0, 1},
            {1, 0, 1, 0}
        };

        int m = 3;
        graphColoring(graph, m);
    }
}
