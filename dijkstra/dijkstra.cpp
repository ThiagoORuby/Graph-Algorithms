#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> edge;
typedef vector<edge> edges;

struct Graph{
    
    int n;
    vector<edges> adj_list;

    Graph(int n) : n(n){
        adj_list.resize(n + 1);
    }

    void add_edge(int u, int v, int weight)
    {
        adj_list[u].push_back(make_pair(v, weight));
        adj_list[v].push_back(make_pair(u, weight));
    }

    edges N(int vertex)
    {
        return adj_list[vertex];
    }
};

vector<int> djikstra(Graph g, int v0)
{
    vector<int> dist(g.n + 1, INT_MAX);
    vector<int> pre(g.n + 1, -1);

    priority_queue<edge, edges, greater<edge>> H;

    dist[v0] = 0;
    H.push(make_pair(dist[v0], v0));

    while(!H.empty())
    {
        int u = H.top().second;
        H.pop();

        for(const edge &e : g.N(u))
        {
            int v = e.first;
            int w = e.second;

            if(dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pre[v] = u;
                H.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}


int main(int argc, char const *argv[])
{
    string input_file, output_file, line;
    int vertices, edges, vertex = 1;
    vector<int> result;
    bool h = false, o = false;

    for(int i = 1; i < argc; i+=2)
    {
        string option = argv[i];
        if(option == "-h") h = true;
        else if (option == "-f") input_file = argv[i+1];
        else if (option == "-i") vertex = stoi(argv[i+1]);
        else if(option == "-o")
        {
            o = true;
            output_file = argv[i+1];
        }
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

    if(vertex < 1 || vertex > vertices+1)
    {
        cout << "invalid initial vertex." << endl;
        return 1;
    }

    Graph g(vertices);

    for(int i = 0; i < edges; i++)
    {
        int from, to, weight;
        file >> from >> to >> weight;
        g.add_edge(from, to, weight);
    }

    file.close();

    result = djikstra(g, vertex);

    for(int i = 1; i <= g.n; i++)
    {
        int dist = result[i] == INT_MAX ? -1 : result[i];
        if(o) output << i << ":" << dist << " ";
        else cout << i << ":" << dist << " ";
    }

    if(!o) cout << endl;

    output.close();

    return 0;
}
