// Online Java Compiler
// Use this editor to write, compile and run your Java code online

import java.util.*;



public class AStarPathfinding {
    static int[] rowNum = {-1, 1, 0, 0};
    static int[] colNum = {0, 0, -1, 1};
    static final int ROW = 5, COL = 5;

    static boolean isValid(int x, int y) {
        return (x >= 0 && x < ROW && y >= 0 && y < COL);
    }

    static int heuristic(Point a, Point b) {
        return Math.abs(a.x - b.x) + Math.abs(a.y - b.y);
    }

    static List<Point> reconstructPath(Node current) {
        List<Point> path = new ArrayList<>();
        while (current != null) {
            path.add(0, current.pt);
            current = current.parent;
        }
        return path;
    }

    static List<Point> aStar(int[][] grid, Point start, Point goal) {
        PriorityQueue<Node> openList = new PriorityQueue<>(Comparator.comparingInt(n -> n.f));
        boolean[][] closedList = new boolean[ROW][COL];
        Map<Point, Node> nodes = new HashMap<>();

        Node startNode = new Node(start, 0, heuristic(start, goal), null);
        openList.add(startNode);
        nodes.put(start, startNode);

        while (!openList.isEmpty()) {
            Node current = openList.poll();

            if (current.pt.equals(goal)) {
                return reconstructPath(current);
            }

            closedList[current.pt.x][current.pt.y] = true;

            for (int i = 0; i < 4; i++) {
                int newX = current.pt.x + rowNum[i];
                int newY = current.pt.y + colNum[i];

                if (isValid(newX, newY) && grid[newX][newY] == 0 && !closedList[newX][newY]) {
                    Point neighborPt = new Point(newX, newY);
                    int tentativeG = current.g + 1;

                    Node neighbor = nodes.getOrDefault(neighborPt, null);

                    if (neighbor == null || tentativeG < neighbor.g) {
                        Node newNode = new Node(neighborPt, tentativeG, heuristic(neighborPt, goal), current);
                        openList.add(newNode);
                        nodes.put(neighborPt, newNode);
                    }
                }
            }
        }
        return Collections.emptyList(); // No path found
    }

    public static void main(String[] args) {
        int[][] grid = {
            {0, 0, 1, 0, 0},
            {0, 1, 1, 0, 1},
            {0, 0, 0, 0, 0},
            {1, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        };

        Point start = new Point(0, 0);
        Point goal = new Point(4, 4);

        List<Point> path = aStar(grid, start, goal);
        if (!path.isEmpty()) {
            System.out.print("Path found: ");
            for (Point p : path) {
                System.out.print("(" + p.x + ", " + p.y + ") ");
            }
            System.out.println();
        } else {
            System.out.println("No path found.");
        }
    }
}
class Point {
    int x, y;

    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    // Needed for comparisons and map keys
    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Point)) return false;
        Point p = (Point) obj;
        return this.x == p.x && this.y == p.y;
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }
}

class Node {
    Point pt;
    int g, h, f;
    Node parent;

    Node(Point pt, int g, int h, Node parent) {
        this.pt = pt;
        this.g = g;
        this.h = h;
        this.f = g + h;
        this.parent = parent;
    }
}
