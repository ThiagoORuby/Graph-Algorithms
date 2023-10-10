#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct Edge{
    int u, v, weight;

    Edge(int u, int v, int w) : u(u), v(v), weight(w){}
};

struct Graph{
    int n, m;
    vector<Edge> edges;

    Graph(int n, int m) : n(n), m(m){}

    void add_edge(int u, int v, int w)
    {
        edges.push_back(Edge(u, v, w));
        edges.push_back(Edge(v, u, w));
    }
};

class UnionFind
{
    private:
        vector<int> parent;
        vector<int> rank;

    public:

        UnionFind(int n){
            parent.resize(n);
            rank.resize(n, 0);

            for(int i = 1; i < n; i++) parent[i] = i;
        }

        int find(int x)
        {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            
            return parent[x];
        }

        void unionSet(int x, int y)
        {
            int fx = find(x);
            int fy = find(y);

            if (rank[fx] >= rank[fy])
            {
                parent[fy] = fx;
                if(rank[fx] == rank[fy])
                    rank[fx]++;
            }
            else
            {
                parent[fx] = fy;
            }
        }

};

bool compare_weights(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}


vector<Edge> kruskal(Graph g)
{
    vector<Edge> T;
    UnionFind uf(g.n);

    vector<Edge> sortedEdges = g.edges;

    sort(sortedEdges.begin(), sortedEdges.end(), compare_weights);

    for(const Edge& e : sortedEdges)
    {
        if (uf.find(e.u) != uf.find(e.v))
        {
            T.push_back(e);
            uf.unionSet(e.u, e.v);
        }
    }

    return T;
}


int main(int argc, char const *argv[])
{
    string input_file, output_file, line;
    int vertices, edges, cost = 0;

    bool s = false, h = false, o = false;


    for(int i = 1; i < argc; i+=2)
    {
        string option = argv[i];
        if(option == "-h") h = true;
        else if (option == "-f") input_file = argv[i+1];
        else if(option == "-o") 
        {
            o = true;
            output_file = argv[i+1];
        }
        else if(option == "-s") s = true;
    }

    if (h)
    {
        ifstream help("help.txt");

        while(getline(help, line))
        {
            cout << line << endl;
        }
        return 0;
    }

    ifstream file(input_file);
    ofstream output(output_file);

    if(!file.good())
    {
        cout << "Error opening the file or the file does not exist." << endl;
        return 1;
    }

    file >> vertices >> edges;

    Graph g(vertices + 1, edges);

    for(int i = 0; i < edges; i++)
    {
        int from, to, weight;
        file >> from >> to >> weight;
        g.add_edge(from, to, weight);
    }

    vector<Edge> T = kruskal(g);

    for(const Edge& e : T)
    {
        if(s)
        {
            if(o) output << "(" << e.u << "," << e.v << ")" << " ";
            else cout << "(" << e.u << "," << e.v << ")" << " ";
        }
        cost += e.weight;
    }

    if(s)
    {
        if(!o) cout << endl;
    }
    else
    {
        if(o) output << cost << endl;
        else cout << cost << endl;
    }

    return 0;
}

