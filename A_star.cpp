#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
using namespace std;

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct Node {
    Point pt;
    int g, h, f;
    Node* parent;

    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

int rowNum[] = {-1, 1, 0, 0};
int colNum[] = {0, 0, -1, 1};

bool isValid(int x, int y, int ROW, int COL) {
    return (x >= 0 && x < ROW && y >= 0 && y < COL);
}

int heuristic(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

vector<Point> reconstruct_path(Node* current) {
    vector<Point> path;
    while (current != nullptr) {
        path.insert(path.begin(), current->pt);
        current = current->parent;
    }
    return path;
}

vector<Point> A_Star(int grid[5][5], Point start, Point goal) {
    int ROW = 5, COL = 5;
    priority_queue<Node, vector<Node>, greater<Node>> openList;
    vector<vector<bool>> closedList(ROW, vector<bool>(COL, false));
    unordered_map<int, unordered_map<int, Node>> nodes;
    
    Node startNode = {start, 0, heuristic(start, goal), heuristic(start, goal), nullptr};
    openList.push(startNode);
    nodes[start.x][start.y] = startNode;
    
    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();
        
        if (current.pt == goal) {
            return reconstruct_path(&nodes[current.pt.x][current.pt.y]);
        }
        
        closedList[current.pt.x][current.pt.y] = true;
        
        for (int i = 0; i < 4; i++) {
            int newX = current.pt.x + rowNum[i];
            int newY = current.pt.y + colNum[i];
            
            if (isValid(newX, newY, ROW, COL) && grid[newX][newY] == 0 && !closedList[newX][newY]) {
                int tentative_g = current.g + 1;
                
                if (nodes.find(newX) == nodes.end() || nodes[newX].find(newY) == nodes[newX].end() || tentative_g < nodes[newX][newY].g) {
                    Node neighbor = {{newX, newY}, tentative_g, heuristic({newX, newY}, goal), tentative_g + heuristic({newX, newY}, goal), &nodes[current.pt.x][current.pt.y]};
                    nodes[newX][newY] = neighbor;
                    openList.push(neighbor);
                }
            }
        }
    }
    return {}; // No path found
}

int main() {
    int grid[5][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    
    Point start = {0, 0};
    Point goal = {4, 4};
    
    vector<Point> path = A_Star(grid, start, goal);
    if (!path.empty()) {
        cout << "Path found: ";
        for (const auto& p : path) {
            cout << "(" << p.x << ", " << p.y << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }
    
    return 0;
}
