#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) // Check if a filename argument is provided
        return 1;

    cout << "Do the edges belong to the graph? ";
    ifstream file;
    file.open(argv[1]);
    int n; // Number of vertices
    int m; // Number of edges

    file >> n >> m;

    vector<vector<int>> adj(n);

    for (int i = 0; i < n; ++i)
        adj[i] = vector<int>();

    for (int i = 0; i < m; ++i) {
        int v1, v2, weight;
        file >> v1 >> v2 >> weight;
        adj[v1 - 1].push_back(v2 - 1);
        adj[v2 - 1].push_back(v1 - 1);
    }

    int cost = 0;
    for (int i = 0; i < m; ++i) {
        int v1, v2;
        cin >> v1 >> v2;
        bool is_edge = false;
        for (auto j : adj[v1 - 1]) {
            if (j == (v2 - 1)) {
                is_edge = true;
                break;
            }
        }

        if (!is_edge) {
            cout << "\nNot an edge: " << v1 << " " << v2 << "\n";
            return 1;
        }
    }

    return 0;
}
