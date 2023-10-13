#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct Edge{
    int weight;
    int initial_vertex;
    int final_vertex;
};

class UnionFind 
{
public:
    UnionFind(int n) 
    {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; ++i) { parent[i] = i; }
    }

    void makeSet(int x) 
    {
        parent[x] = x;
        rank[x] = 0;
    }

    int find(int x) 
    {
        if (parent[x] != x) { parent[x] = find(parent[x]); }

        return parent[x];
    }

    void unionSets(int x, int y) 
    {
        if (rank[x] >= rank[y]) 
        {
            parent[y] = x;
            if (rank[x] == rank[y]) { rank[x]++; }
        } 

        else { parent[x] = y; }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int kruskal(vector<vector<int>> &graph, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> &weights, int n, int m, int initial_vertex, int show, vector<Edge> &edges) 
{
    UnionFind *uf = new UnionFind(n + 1);
    vector<vector<int>> tree;
    int cost = 0;

    vector<bool> added(m, false);

    for (int i = 1; i <= n; i++) { uf->makeSet(i); }

    uf->makeSet(initial_vertex);

    while (!weights.empty()) 
    {
        int i = weights.top().second;
        int weight = weights.top().first;
        int u = edges[i].initial_vertex;
        int v = edges[i].final_vertex;
        weights.pop();

        if (uf->find(u) != uf->find(v)) 
        {
            tree.push_back({u, v});
            uf->unionSets(uf->find(u), uf->find(v));
            if (edges[i].weight == weight) { cost += weight; }
            added[i] = true;
        }
    }

    if (show) 
    {
        for (int i = 0; i < m; i++) 
        {
            if (added[i]) 
            { 
                cout << "(" << edges[i].initial_vertex << "," << edges[i].final_vertex << ")"; 
            } 
        }
        cout << endl;
    }

    delete uf;
    return cost;
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
            cout << "-s: show the solution (in ascending order)" << endl;
            cout << "-i: initial vertex" << endl;
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) { output_file = argv[++i]; } 
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) { input_file = argv[++i]; }
        else if (strcmp(argv[i], "-s") == 0) { show_solution = true; } 
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
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> weights;
    vector<Edge> edges(m + 1);
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

        edges[i].weight = weight;
        edges[i].initial_vertex = u;
        edges[i].final_vertex = v;

        weights.push({weight, i});
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
            kruskal(graph, weights, n, m, initial_vertex, 1, edges);
            fout.close();
            return 0;
        } 
        else 
        {
            int cost = kruskal(graph, weights, n, m, initial_vertex, 0, edges);
            fout << cost;
        }

        fout.close();
    }
    else 
    {
        int cost = kruskal(graph, weights, n, m, initial_vertex, 0, edges);
        if (!show_solution) { cout << cost << endl; }
    }

    return 0;
}
