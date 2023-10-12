#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> edge;
typedef vector<edge> edges;


// Non-directional Graph Struct
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

// Prim Algorithm
pair<int, vector<int>> prim(Graph g, int v0)
{
    // Initialize the cost and visited, distance and previous vectors
    int cost = 0;
    vector<bool> visited(g.n + 1, false);
    vector<int> dist(g.n + 1, INT_MAX);
    vector<int> pre(g.n + 1, -1);

    // Initialize the max priority queue
    priority_queue<edge, edges, greater<edge>> H;

    // Set the v0 distance and push to the queue
    dist[v0] = 0;
    H.push(make_pair(dist[v0], v0));

    // Execute the loop while the queue isn't empty
    while(!H.empty())
    {
        // Get the first vector on the queue (minimal distance) and set has visited
        int u = H.top().second;
        H.pop();
        visited[u] = true;

        // For each edge of u, updates the MST information by the distances
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

    // Calc the cost
    for(int i = 1; i <= g.n; i++) cost += dist[i];
    
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

    Graph g(vertices);

    for(int i = 0; i < edges; i++)
    {
        int from, to, weight;
        file >> from >> to >> weight;
        g.add_edge(from, to, weight);
    }

    file.close();

    result = prim(g, vertex);
    cost = result.first;
    pre = result.second;

    if(s)
    {
        for(int j = 1; j < (int) pre.size(); j++)
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

    output.close();

    return 0;
}
