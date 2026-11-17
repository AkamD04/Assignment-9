#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, w;
};

bool compare(Edge a, Edge b)
{
    return a.w < b.w;
}

int findParent(int v, vector<int>& parent)
{
    if (parent[v] == v)
        return v;

    return parent[v] = findParent(parent[v], parent);
}

void unite(int u, int v, vector<int>& parent, vector<int>& rank)
{
    u = findParent(u, parent);
    v = findParent(v, parent);

    if (rank[u] < rank[v])
        parent[u] = v;
    else if (rank[u] > rank[v])
        parent[v] = u;
    else
    {
        parent[v] = u;
        rank[u]++;
    }
}

int main()
{
    int n, e;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;

    vector<Edge> edges(e);

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < e; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(n), rank(n, 0);

    for (int i = 0; i < n; i++)
        parent[i] = i;

    int cost = 0;

    cout << "Minimum Spanning Tree:\n";

    for (Edge edge : edges)
    {
        if (findParent(edge.u, parent) != findParent(edge.v, parent))
        {
            cout << edge.u << " - " << edge.v
                 << " : " << edge.w << endl;

            cost += edge.w;
            unite(edge.u, edge.v, parent, rank);
        }
    }

    cout << "Minimum Cost: " << cost;

    return 0;
}