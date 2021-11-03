#include <bits/stdc++.h>
#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <omp.h>
using namespace std;
typedef pair<int, int> iPair;
struct Graph
{
    int V, E;
    vector<pair<int, iPair>> edges;
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }
    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }
    int kruskalMST();
};
struct DisjointSets
{
    int *parent, *rnk;
    int n;
    DisjointSets(int n)
    {
        this->n = n;
        parent = new int[n + 1];
        rnk = new int[n + 1];
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
            parent[i] = i;
        }
    }
    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};
int Graph::kruskalMST()
{
    int mst_wt = 0;
    sort(edges.begin(), edges.end());
    DisjointSets ds(V);
    vector<pair<int, iPair>>::iterator it;
    for (it = edges.begin(); it != edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);
        if (set_u != set_v)
        {
            cout << u << " - " << v << endl;
            mst_wt += it->first;
            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;
}
int main()
{
    int V = 28;
    int E = 250;
    int j = -2;
    Graph g(V, E);
    fstream newfile;
    newfile.open("out.moreno_sheep_sheep", ios::in);
    if (newfile.is_open())
    {
        string tp;
        while (getline(newfile, tp))
        {
            regex regex("([0-9/-]+)");
            if (j < 0)
            {
                j++;
                continue;
            }
            vector<std::string> out(
                sregex_token_iterator(tp.begin(), tp.end(), regex, 1),
                sregex_token_iterator());
            int i = 1;
            int a, b, c;
            for (auto &s : out)
            {
                if (i == 1)
                {
                    a = stoi(s) - 1;
                }
                else if (i == 2)
                {
                    b = stoi(s) - 1;
                }
                else if (i == 3)
                {
                    c = stoi(s);
                    g.addEdge(a, b, c);
                    j++;
                }
                i++;
            }
        }
        newfile.close();
    }
    cout << "Edges of MST are \n";
    int mst_wt = g.kruskalMST();

    cout << "\nWeight of MST is " << mst_wt;

    return 0;
}
