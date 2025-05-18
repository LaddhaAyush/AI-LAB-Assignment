private int vertices;
private List<List<Integer>> adj;

public GraphTraversal(int v) {
    vertices = v;
    adj = new ArrayList<>();
    for (int i = 0; i < v; i++)
        adj.add(new ArrayList<>());
}

public void addEdge(int u, int v) {
    adj.get(u).add(v);
    adj.get(v).add(u); // For undirected graph
}

// BFS traversal
public void bfs(int start) {
    boolean[] visited = new boolean[vertices];
    Queue<Integer> queue = new LinkedList<>();

    visited[start] = true;
    queue.offer(start);

    System.out.print("BFS: ");
    while (!queue.isEmpty()) {
        int node = queue.poll();
        System.out.print(node + " ");

        for (int neighbor : adj.get(node)) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.offer(neighbor);
            }
        }
    }
    System.out.println();
}

// DFS traversal
public void dfs(int start) {
    boolean[] visited = new boolean[vertices];
    System.out.print("DFS: ");
    dfsHelper(start, visited);
    System.out.println();
}

private void dfsHelper(int node, boolean[] visited) {
    visited[node] = true;
    System.out.print(node + " ");

    for (int neighbor : adj.get(node)) {
        if (!visited[neighbor])
            dfsHelper(neighbor, visited);
    }
}

public static void main(String[] args) {
    GraphTraversal g = new GraphTraversal(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    g.bfs(0); // Starting BFS from node 0
    g.dfs(0); // Starting DFS from node 0
}
