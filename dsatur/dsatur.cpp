/**
 * DSATUR (Degree of Saturation) Algorithm
 * 
 * An efficient heuristic algorithm for graph colouring. This algorithm is based on
 * the Greedy Coloring and use the 'Degree of Saturation' - number of different colors
 * to all of the neighbors of a vertex - as your heuristic.
 * 
 * ALGORITHM STEPS
 * 1. Select uncolored vertex v with the highest degree of saturation (DSAT). If two or more
 * vertices have the same DSAT, select one with the largest degree in the subgraph induced by
 * the uncolored vertices;
 * 2. Set v to the lowest ununsed color not being used by any of its neighbors;
 * 3. Repeat the steps for all the vertices.
 * 
 * OBS: The Set was chosen to represent the priority queue because its structure allows for the
 * removal of elements for the insertion of the updated element in O(log n) time, preventing the
 * repetition of vertices in the queue and, consequently, reducing the number of loop iterations.
*/

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> edge;

// Non-directional Graph struct
struct Graph{

    int n;
    vector<edge> adj_list;

    Graph(int n) : n(n){
        adj_list.resize(n + 1);
    }

    void add_edge(int u, int v)
    {
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    edge N(int vertex)
    {
        return adj_list[vertex];
    }
};

// Vertex informations for DSATUR
struct vertexData
{
    int satur;
    int deg;
    int vertex;
};

// Comparision Operator to the Priority Queue
struct maxSat
{
    bool operator()(const vertexData &v, const vertexData &u) const
    {
        return tie(v.satur, v.deg, v.vertex) > tie(u.satur, u.deg, u.vertex);
    }
};


// DSATUR Algorithm
pair<int, vector<int>> DSATUR2(Graph g)
{
    // Initialize color, degree e DSAT vectors
    vector<int> color(g.n + 1, -1), d(g.n + 1);
    vector<unordered_set<int>> saturDeg(g.n + 1);

    // Initializet the Priority Queue using Set Data Structure
    set<vertexData, maxSat> H;

    // Set the degrees and insert the vertices data on the Queue
    for(int i = 1; i <= g.n; i++)
    {
        saturDeg[i] = unordered_set<int>();
        d[i] = g.N(i).size();
        H.insert(vertexData{0, d[i], i});
    }

    // Execute the loop while the queue is not empty
    while(!H.empty())
    {   
        // Get the top vertex (Max DSAT or Max degree)
        auto top = H.begin();
        int u = (*top).vertex;
        H.erase(top);

        // check if it's colored
        if(color[u] != -1) continue;


        vector<bool> usedColor(g.n + 1, false);
        for(const int v : g.N(u))
        {
            if(color[v] != -1)
                usedColor[color[v]] = true;
        }

        // Set the lowest availabe color to the vertex
        for(int c = 1; c <= g.n; c++)
        {
            if(usedColor[c] == false)
            {
                color[u] = c;
                break;
            }
        }

        //cout << "Coloring u" << u << " with the color " << color[u] << endl;

        // for each neighbor, if its not colored, update DSAT and degree on the queue
        for(const int v : g.N(u))
        {
            if(color[v] == -1)
            {
                H.erase(vertexData{(int) saturDeg[v].size(), d[v], v}); // O(log n)
                saturDeg[v].insert(u); // O(1)
                d[v]--;
                H.insert(vertexData{(int) saturDeg[v].size(), d[v], v}); // O(log n)
            }
        }
    }

    // calc the cromatic number in O(log(n)) using set 
    set<int> crom;
    for(int i = 1; i <= g.n; i++)
        crom.insert(color[i]);
    
    return make_pair(crom.size(), color);
}

int main(int argc, char const *argv[])
{
    string input_file, output_file, line;
    int vertices, edges, crom, vertex = 1;
    vector<int> color;
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

        help.close();
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
        int from, to;
        file >> from >> to;
        g.add_edge(from, to);
    }

    file.close();

    result = DSATUR2(g);
    crom = result.first;
    color = result.second;

    if(s)
    {
        for(int j = 1; j < (int) color.size(); j++)
        {
            if(o) output << "v" << j << ":" << color[j] << " ";
            else cout << "v" << j << ":" << color[j] << " ";
        }
        if(!o) cout << endl;
    }
    else
    {
        if(o) output << crom;
        else cout << crom;
    }

    output.close();


    return 0;
}