#include <bits/stdc++.h>

using namespace std;


struct Graph{

    int n;
    map<int, vector<int>> adj_list;

    Graph(int n) : n(n){}

    int get_n(){return n;}

    void add_edge(int u, int v)
    {
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    vector<int> N(int vertex)
    {
        return adj_list[vertex];
    }
};

bool compareDegrees(pair<int, int> a, pair<int, int> b)
{
    return a.second > b.second;
}

void welshPowell(Graph g)
{
    vector<pair<int,int>> vertexDegrees;

    for(int i = 1; i < g.n; i++)
    {
        int degree = g.N(i).size();
        vertexDegrees.push_back(make_pair(i, degree));
    }

    sort(vertexDegrees.begin(), vertexDegrees.end(), compareDegrees);

    vector<int> vertexColor(g.n, -1);

    vertexColor[vertexDegrees[0].first] = 1;

    for(const auto &d : vertexDegrees)
    {
        int v = d.first;

        vector<bool> usedColors(g.n, false);

        for(int u : g.N(v))
        {
            if(vertexColor[u] != -1)
                usedColors[vertexColor[u]] = true;
        }

        for(int color = 1; color < g.n; color++)
        {
            if(!usedColors[color])
            {
                vertexColor[v] = color;
                break;
            }
        }
    }

    for(int i = 1; i < g.n; i++)
    {
        cout << "v" << i << ":" << vertexColor[i] << " ";
    }
    cout << endl;

}

int main()
{
    int vertices, edges;

    ifstream file("teste.dat");

    file >> vertices >> edges;

    Graph g(vertices + 1);

    for(int i = 0; i < edges; i++)
    {
        int from, to, weight;
        file >> from >> to >> weight;
        g.add_edge(from, to);
    }
    
    welshPowell(g);

    return 0;
}