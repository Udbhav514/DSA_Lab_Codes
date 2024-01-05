#include <bits/stdc++.h>
using namespace std;
vector<int> prin;

class Graph
{
public:
    Graph(int vertices) : V(vertices)
    {
        adj = new vector<int>[V];
    }

    void addEdge(int u, int v)
    {
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    void MDFTUtil(int v, vector<bool> &visited, stack<int> &s)
    {
        visited[v] = true;
        s.push(v);

        vector<pair<int, int>> neighborsWithDegrees;

        for (int neighbor : adj[v])
        {
            int degree = adj[neighbor].size();
            neighborsWithDegrees.push_back({degree, neighbor});
        }

        sort(neighborsWithDegrees.rbegin(), neighborsWithDegrees.rend());

        for (const auto &neighborDegreePair : neighborsWithDegrees)
        {
            int neighbor = neighborDegreePair.second;
            if (!visited[neighbor])
            {
                MDFTUtil(neighbor, visited, s);
            }
        }
    }

    void MDFT(int startVertex)
    {
        vector<bool> visited(V, false);
        stack<int> s;
        MDFTUtil(startVertex, visited, s);

        while (!s.empty())
        {
            prin.push_back(s.top() + 1);
            s.pop();
        }
        for (int i = prin.size() - 1; i >= 0; i--)
        {
            cout << prin[i] << " ";
        }
        prin.clear();

        cout << endl;
    }

    void printMDFTComponents()
    {
        vector<bool> visited(V, false);
        vector<pair<int, int>> componentLastVertices;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                stack<int> s;
                MDFTUtil(i, visited, s);
                componentLastVertices.emplace_back(i, s.top());
            }
        }

        sort(componentLastVertices.begin(), componentLastVertices.end(), [](pair<int, int> a, pair<int, int> b)
             { return a.second < b.second; });

        int numComponents = componentLastVertices.size();
        for (int i = 0; i < numComponents; i++)
        {
            MDFT(componentLastVertices[i].first);
        }
        cout << numComponents << endl;
    }

private:
    int V;
    vector<int> *adj;
};

int main()
{
    int n;
    cin >> n;
    Graph g(n);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        g.addEdge(a, b);
    }
    g.printMDFTComponents();

    return 0;
}
