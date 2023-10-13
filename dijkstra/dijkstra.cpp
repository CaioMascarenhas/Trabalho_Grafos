#include <bits/stdc++.h>
using namespace std;

// Vector 'dist' stores the distance from vertex 0 to each index.
// Vector 'pre' keeps track of the parent vertices.
// We compare the weights of adjacent vertices to determine which one to put in the distance.

void dijkstra(vector<vector<int>> &graph, vector<int> &dist, vector<int> &pre, vector<vector<int>> &weights) 
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue; // Priority queue with specification GREATER = smaller to larger.
    queue.push({0, 1}); // Change 1 to the initial vertex instead of always 1.
    
    while (!queue.empty()) 
    {
        int u = queue.top().second; // The second part of the pair / y (x, y) is the top element of the queue.
        int distance_to_u = queue.top().first;
        queue.pop();
        
        if (distance_to_u > dist[u]) 
        {
            continue; // Already passed through u; otherwise, it would be smaller.
        } 
        else 
        {
            for (auto adjacent : graph[u]) 
            {
                int v = adjacent;
                int weight_uv = weights[u][v];
                
                if (dist[u] + weight_uv < dist[v]) 
                {
                    dist[v] = dist[u] + weight_uv;
                    pre[v] = u;
                    queue.push({dist[v], v});
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    string input_file = "";
    string output_file = "";
    bool show_solution = false;
    int initial_vertex = 1;

    for (int i = 1; i < argc; i++) 
    {
        if (strcmp(argv[i], "-h") == 0) 
        {
            cout << "Help:" << endl;
            cout << "-h: show the help" << endl;
            cout << "-o <file>: redirect output to the 'file'" << endl;
            cout << "-f <file>: specify the input 'file' containing the graph" << endl;
            cout << "-i: initial vertex" << endl;
            return 0;
        } 
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) { output_file = argv[++i]; } 
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) { input_file = argv[i + 1]; } 
        else if (strcmp(argv[i], "-i") == 0 && i < argc - 1) { initial_vertex = atoi(argv[++i]); }
    }

    if (input_file == "") 
    {
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin;
    fin.open(input_file);

    if (!fin) 
    {
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;
    vector<vector<int>> weights(n + 1, vector<int>(n + 1, numeric_limits<int>::max())); // Initialize with large values.
    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < m; i++) 
    {
        int u, v, weight;
        fin >> u >> v >> weight;

        if (u < 0 || v < 0 || weight < 0) 
        {
            cout << "Invalid input" << endl;
            return 0;
        }

        graph[u].push_back(v);
        graph[v].push_back(u);
        weights[u][v] = weight;
        weights[v][u] = weight;
    }

    // Initialization
    vector<int> dist(n + 1);
    vector<int> pre(n + 1, -1);
    dist[initial_vertex] = 0;
    for (int i = 1; i <= n; i++) 
    {
        if (i != initial_vertex) 
        { 
            dist[i] = numeric_limits<int>::max(); 
        }
    }

    fin.close();

    if (!(output_file == "")) 
    {
        ofstream fout(output_file);
        if (!fout) 
        {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }

        if (show_solution) 
        {
            dijkstra(graph, dist, pre, weights);

            for (int i = 1; i <= n; i++) 
            {
                if (dist[i] == numeric_limits<int>::max()) 
                {
                    dist[i] = -1; // Unreachable vertex
                }
                fout << i << ":" << dist[i] << endl;
            }

            fout.close();
            return 0;
        } 
        else 
        {
            dijkstra(graph, dist, pre, weights);

            for (int i = 1; i <= n; i++) 
            {
                if (dist[i] == numeric_limits<int>::max()) 
                {
                    dist[i] = -1; // Unreachable vertex
                }
                fout << i << ":" << dist[i] << endl;
            }
        }

        fout.close();
    } 
    else 
    {
        dijkstra(graph, dist, pre, weights);
        for (int i = 1; i <= n; i++) 
        {
            if (dist[i] == numeric_limits<int>::max()) 
            {
                dist[i] = -1; // Unreachable vertex
            }
            cout << i << ":" << dist[i];
            if (i != n) 
            {
                cout << " ";
            } 
            else 
            {
                cout << endl;
            }
        }
    }

    return 0;
}
