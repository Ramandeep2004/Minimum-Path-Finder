#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <climits>
using namespace std;

void PrintDistances(int startNode, const vector<int>& distance) {
    cout << "Shortest distances from node " << startNode << ":\n";
    for (size_t i = 0; i < distance.size(); i++) {
        cout << "To node " << i << ": ";
        if (distance[i] == INT_MAX) {
        cout << "Non Reachable Node\n";
        } 
        else {
        cout << distance[i] << "\n";
        }        
    }
}

void dijkstra(int startnode, const vector<vector<pair<int, int>>>& graph) {
    int no_node = graph.size(); 
    vector<int> distance(no_node, INT_MAX); 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue; 

    distance[startnode] = 0; 
    queue.push(make_pair(0, startnode)); 

    while (!queue.empty()) {
        
        int currDist = queue.top().first; 
        int currNode = queue.top().second; 
        queue.pop(); 
        
        if (currDist > distance[currNode]) {
            continue;
        }

        for (const auto& neighbor : graph[currNode]) {
            int nextNode = neighbor.first; 
            int weight = neighbor.second; 

            if (distance[nextNode] > currDist + weight) {
                distance[nextNode] = currDist + weight; 
                queue.push(make_pair(distance[nextNode], nextNode)); 
            }
        }
    }

    PrintDistances(startnode, distance);
}

bool readGraphFromFile(const string& filename, vector<vector<pair<int, int>>>& graph) {
    ifstream file(filename);
    if (!file) {
        cout << "Graph File Not Found!" << filename << "\n";
        return false; 
    }

    int nodes, edges;
    file >> nodes >> edges; 

    graph.resize(nodes);

    for (int i = 0; i < edges; i++) {
        int a, b, c;
        file >> a >> b >> c; 
        graph[a].push_back(make_pair(b, c)); 
        graph[b].push_back(make_pair(a, c)); 
    }
    file.close(); 
    return true; 
}

int main() {
    vector<vector<pair<int, int>>> graph; 

    if (!readGraphFromFile("graph3.txt", graph)) {
        return 1;  
    }
    int startNode = 4; 
    dijkstra(startNode, graph);

    return 0; 
}