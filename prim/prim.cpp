#include <bits/stdc++.h>

using namespace std;

void prim(vector<vector<int>> weights, vector<vector<int>> graph, vector<int> &mst, vector<bool> &visited, vector<int> &dist, int start, int n)
{
    priority_queue<pair<int, pair<int, int>>> pq; // Priority queue with specification GREATER = smaller to larger
    dist[start] = 0;
    pq.push({0, {start, start}}); // Change to -start instead of 1 always         // Since 1 is the initial vertex, its distance to itself is 0, the pair is (dist[v], v)
    int count = 0;

    while (!pq.empty())
    {
        pair<int, int> edge = pq.top().second; // Second part of the pair / y (x, y) -> Top element -> of the queue
        pq.pop();
        int u = edge.first;       // Current vertex
        int parent = edge.second; // Vertex before the current one
        visited[u] = true;

        if (count != n && parent != u && weights[parent][u] == dist[u])
        {
            if (mst[parent] == -1)
            {
                mst[parent] = u;
            }
            else if (mst[u] == -1)
            {
                mst[u] = parent;
            }

            count++;
        }

        for (auto neighbor : graph[u])
        {
            int v = neighbor;
            int weight_uv = weights[u][v];

            if (visited[v])
                continue;

            if (weight_uv < dist[v])
            {
                dist[v] = weight_uv;
                pq.push({-weight_uv, {v, u}}); // Orders in descending order as well, just with a negative approach!
            }
        }
    }
}

vector<priority_queue<int>> sort_mst(vector<int> mst, int n)
{
    vector<priority_queue<int>> graph_mst(n + 1);

    // Sorting the tree
    for (int i = 0; i <= n; i++)
    {
        if (mst[i] != -1)
        {
            if (i > mst[i])
            {
                graph_mst[mst[i]].push(-i);
            }
            else
            {
                graph_mst[i].push(-mst[i]);
            }
        }
    }

    return graph_mst;
}

int main(int argc, char *argv[])
{
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
            cout << "-s: show the solution (in ascending order)" << endl;
            cout << "-i: initial vertex" << endl;
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1)
        {
            output_file = argv[++i];
        }
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1)
        {
            input_file = argv[++i];
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            show_solution = true;
        }
        else if (strcmp(argv[i], "-i") == 0 && i < argc - 1)
        {
            initial_vertex = atoi(argv[++i]);
        }
    }

    if (input_file == "")
    {
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin)
    {
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;

    vector<vector<int>> weights(n + 1, vector<int>(n + 1, numeric_limits<int>::max())); // Initialize with large values
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

        graph[u].push_back(v); // Read arcs and add to the adjacency list who is the neighbor of whom
        graph[v].push_back(u);
        weights[u][v] = weight; // Weight of edge 0-1 = 50, for example
        weights[v][u] = weight; // 1 - 0 = the same
    }

    // Initializations
    vector<int> mst(n + 1, -1);
    vector<bool> visited(n + 1, false);
    vector<int> dist(n + 1, numeric_limits<int>::max());

    fin.close();

    prim(weights, graph, mst, visited, dist, initial_vertex, n);

    int total_cost = 0;

    for (int i = 1; i <= n; i++)
        if (dist[i] != numeric_limits<int>::max())
            total_cost += dist[i];

    if (show_solution)
    {
        vector<priority_queue<int>> graph_mst = sort_mst(mst, n);

        for (int i = 0; i < graph_mst.size(); i++)
        {
            while (!graph_mst[i].empty())
            {
                int j = graph_mst[i].top();
                graph_mst[i].pop();

                cout << "(" << i << "," << -j << ") ";
            }
        }

        cout << endl;
    }
    else
    {
        cout << total_cost << endl;
    }

    if (!(output_file == ""))
    {
        ofstream fout(output_file);
        if (!fout)
        {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }

        fout << "MST cost = " << total_cost << endl;

        if (show_solution)
        {
            vector<priority_queue<int>> graph_mst = sort_mst(mst, n);

            for (int i = 0; i < graph_mst.size(); i++)
            {
                while (!graph_mst[i].empty())
                {
                    int j = graph_mst[i].top();
                    graph_mst[i].pop();

                    fout << "(" << i << "," << -j << ") ";
                }
            }

            fout << endl;
        }
        else
        {
            for (int i = 1; i <= n; i++)
            {
                if (mst[i] != -1)
                {
                    fout << "(" << i << "," << mst[i] << ") ";
                }
            }

            fout << endl;
        }

        fout.close();
    }

    return 0;
}
