#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> edge;
typedef vector<edge> edges;

class Graph{

    private:
        int n;
        vector<edges> adj_list;
    
    public:

        Graph(int n) : n(n){
            adj_list.resize(n);
        }

        int get_n(){return n;}

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

pair<int, vector<int>> prim(Graph g, int v0)
{
    int cost = 0;
    vector<bool> visited(g.get_n(), false);
    vector<int> dist(g.get_n(), INT_MAX);
    vector<int> pre(g.get_n(), -1);

    priority_queue<edge, edges, greater<edge>> H;

    dist[v0] = 0;
    H.push(make_pair(dist[v0], v0));

    while(!H.empty())
    {
        int u = H.top().second;
        H.pop();
        visited[u] = true;

        for(const edge &e : g.N(u))
        {
            int v = e.first;
            int w = e.second;

            if(!visited[v] && w < dist[v])
            {
                pre[v] = u;
                dist[v] = w;
                H.push(make_pair(dist[v], v));
            }
        }
    }

    for(int i = 1; i < g.get_n(); i++) cost += dist[i];
    
    return make_pair(cost, pre);
}


int main(int argc, char const *argv[])
{
    string input_file, output_file, line;
    int vertices, edges, cost, vertex = 1;
    vector<int> pre;
    pair<int, vector<int>> result;
    bool s = false, h = false, o = false;

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

    if(vertex < 1 || vertex > vertices+1)
    {
        cout << "invalid initial vertex." << endl;
        return 1;
    }

    Graph g(vertices + 1);

    for(int i = 0; i < edges; i++)
    {
        int from, to, weight;
        file >> from >> to >> weight;
        g.add_edge(from, to, weight);
    }

    result = prim(g, vertex);

    cost = result.first;
    pre = result.second;

    if(s)
    {
        for(int j = 1; j < pre.size(); j++)
        {
            if(pre[j] > 0)
            {
                if(o) output << "(" << pre[j] << "," << j << ")" << " ";
                else cout << "(" << pre[j] << "," << j << ")" << " ";
            }
        }
        if(!o) cout << endl;
    }
    else
    {
        if(o) output << cost;
        else cout << cost;
    }

    return 0;
}
