#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>

using namespace std;

// non-directional graph
class Graph{

    private:
        typedef vector<pair<int,int>> edge;
        map<int, edge> adj_list;
    
    public:
        int n;
        int m;

        void add_edge(int from, int to, int weight)
        {
            adj_list[from].push_back(make_pair(to, weight));
            adj_list[to].push_back(make_pair(from, weight));
        }

        edge N(int vertex)
        {
            return adj_list[vertex];
        }
};

// Minimal priority queue
class MinPriorityQueue{

    private:
        vector<pair<int, int>> _data;
        unordered_map<int, int> valueToIndex;

    public:

        int empty()
        {
            return _data.size() == 0;
        }

        int parent(int index)
        {
            return (index == 0) ? -1 : (index - 1) / 2;
        }

        void insert(pair<int, int> element)
        {
            int i, p;
            int value = element.first;

            // não tenho certeza se é necessário
            if(valueToIndex.find(value) != valueToIndex.end())
            {
                i = valueToIndex[value];
                if(element.second < _data[i].second)
                {
                    _data[i] = element;
                } 
            }
            else{
                _data.push_back(element);
                i = _data.size() - 1;
                valueToIndex[value] = i;
            }

            p = parent(i);
            
            while(p >= 0 && _data[i].second < _data[p].second)
            {
                swap(_data[i], _data[p]);
                i = p;
                p = parent(i);
            }
        }

        void heapify_rec(int size, int index)
        {
            int lowest = index;
            int left = 2*index + 1;
            int right = 2*index + 2;

            if(left < size && _data[left] < _data[lowest])
                lowest = left;
            if(right < size && _data[right] < _data[lowest])
                lowest = right;
            
            if(lowest != index)
            {
                swap(_data[index], _data[lowest]);
                heapify_rec(size, lowest);
            }
        }

        pair<int, int> min()
        {
            if (_data.size() == 0) return make_pair(-1,-1);

            pair<int, int> result = _data[0];
            _data[0] = _data[_data.size() - 1];
            _data.pop_back();

            heapify_rec(_data.size(), 0);

            return result;
        }

        void print_heap()
        {
            for(int i = 0; i < _data.size(); i++)
            {
                cout <<  "(" << _data[i].first << "," << _data[i].second << ")" << " ";
            }
            cout << endl;
        }

};


void djikstra(Graph g, int v0)
{
    vector<int> dist(g.n + 1, INT_MAX);
    vector<int> pre(g.n + 1, -1);
    MinPriorityQueue H;

    dist[v0] = 0;
    H.insert(make_pair(v0, dist[v0]));

    while (! H.empty())
    {
        int u = H.min().first;

        // precorrer os vizinho de u
        for(pair<int, int> edge : g.N(u))
        {
            int v = edge.first;
            int w = edge.second;
            if(dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pre[v] = u;
                H.insert(make_pair(v, dist[v]));
            }
        }
    }

    for(int i = 1; i < g.n + 1; i++)
    {
        cout << i << ":" << dist[i] << " ";
    }
    cout << endl;
}

void prim(Graph g, int v0)
{
    vector<bool> visited(g.n + 1, false);
    vector<int> dist(g.n + 1, INT_MAX);
    vector<int> pre(g.n + 1, -1);
    MinPriorityQueue H;

    dist[v0] = 0;
    H.insert(make_pair(v0, dist[v0]));

    while(!H.empty())
    {
        int u = H.min().first;
        visited[u] = true;

        for(pair<int, int> edge : g.N(u))
        {
            int v = edge.first;
            int w = edge.second;

            if(!visited[v] && w < dist[v])
            {
                pre[v] = u;
                dist[v] = w;
                H.insert(make_pair(v, dist[v]));
            }
        }
    }

    for(int i = 1; i < g.n + 1; i++)
    {
        if (pre[i] > 0)
            cout << "(" << pre[i] << "," << i << ")" << " ";
    }
    cout << endl;

}

void prim2(Graph g, int v0)
{
    vector<bool> visited(g.n + 1, false);
    vector<int> dist(g.n + 1, INT_MAX);
    vector<int> pre(g.n + 1, -1);
    //MinPriorityQueue H;

    typedef pair<int, int> edges;

    priority_queue<edges, vector<edges>, greater<edges>> H;

    dist[v0] = 0;
    H.push(make_pair(dist[v0], v0));

    while(!H.empty())
    {
        int u = H.top().second;
        H.pop();
        visited[u] = true;

        for(pair<int, int> edge : g.N(u))
        {
            int v = edge.first;
            int w = edge.second;

            if(!visited[v] && w < dist[v])
            {
                pre[v] = u;
                dist[v] = w;
                H.push(make_pair(dist[v], v));
            }
        }
    }

    for(int i = 1; i < g.n + 1; i++)
    {
        if (pre[i] > 0)
            cout << "(" << pre[i] << "," << i << ")" << " ";
    }
    cout << endl;
}

int main()
{
    int vertices, edges;
    Graph g;

    cin >> vertices >> edges;

    g.n = vertices;

    for(int i = 0; i < edges; i++)
    {
        int from, to, weight;
        cin >> from >> to >> weight;
        g.add_edge(from, to, weight);
    }

    //djikstra(g, 1);
    prim2(g, 1);

    return 0;
}