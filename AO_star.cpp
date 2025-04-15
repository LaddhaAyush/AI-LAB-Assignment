#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Node {
    string name;
    vector<Node*> children;
    int heuristic;
    Node* parent;
    
    Node(string n, int h) : name(n), heuristic(h), parent(nullptr) {}
};

int calculateCost(Node* node) {
    int cost = 0;
    while (node) {
        cost += node->heuristic;
        if (!node->children.empty()) node = node->children[0];
        else break;
    }
    return cost;
}

Node* aoStar(Node* root, vector<string>& path) {
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> pq;
    unordered_map<Node*, int> costMap;
    
    pq.push({root->heuristic, root});
    costMap[root] = root->heuristic;
    
    while (!pq.empty()) {
        auto [currentCost, currentNode] = pq.top();
        pq.pop();
        
        if (currentNode->heuristic == 0) {
            while (currentNode) {
                path.push_back(currentNode->name);
                currentNode = currentNode->parent;
            }
            reverse(path.begin(), path.end());
            return path.empty() ? nullptr : root;
        }
        
        for (Node* child : currentNode->children) {
            int pathCost = calculateCost(child);
            pq.push({pathCost, child});
            child->parent = currentNode;
        }
    }
    return nullptr;
}

int main() {
    Node* root = new Node("Root", 5);
    Node* child1 = new Node("Child 1", 3);
    Node* child2 = new Node("Child 2", 0);
    Node* child3 = new Node("Child 3", 2);
    
    root->children = {child1, child2};
    child1->children = {child3};
    
    vector<string> path;
    Node* result = aoStar(root, path);
    
    if (result) {
        cout << "Goal Node Found: " << path.back() << "\nPath: ";
        for (const string& nodeName : path) cout << nodeName << " -> ";
        cout << "END\n";
    } else {
        cout << "No Solution Found.\n";
    }
    
    return 0;
}
