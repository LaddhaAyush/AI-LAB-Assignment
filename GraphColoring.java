import java.util.*;

public class Main {

  // Function to check if it's safe to color vertex with a given color
  public static boolean isSafe(int[][] graph, int[] color, int vertex, int c) {
    for (int i = 0; i < graph.length; i++) {
      if (graph[vertex][i] == 1 && color[i] == c) {
        return false;
      }
    }
    return true;
  }

  // Recursive function to try assigning colors
  public static boolean graphColoring(int[][] graph, int m, int[] color, int vertex) {
    int n = graph.length;
    
    if (vertex == n) {
      // All vertices colored successfully
      for (int i = 0; i < n; i++) {
        System.out.println("Vertex " + i + " -> Color " + color[i]);
      }
      System.out.println();
      return true;
    }

    boolean res = false;

    // Try all colors for this vertex
    for (int c = 1; c <= m; c++) {
      if (isSafe(graph, color, vertex, c)) {
        color[vertex] = c;
        res = graphColoring(graph, m, color, vertex + 1) || res;
        color[vertex] = 0; // Backtrack
      }
    }

    return res;
  }

  public static void main(String[] args) {
    // Sample graph represented as adjacency matrix
    int[][] graph = {
      {0, 1, 1, 1},
      {1, 0, 1, 0},
      {1, 1, 0, 1},
      {1, 0, 1, 0}
    };
    
    int m = 3; // Number of colors
    int[] color = new int[graph.length];

    if (!graphColoring(graph, m, color, 0)) {
      System.out.println("No solution exists");
    }
  }
}
