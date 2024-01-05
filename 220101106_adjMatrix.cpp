#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 2;
int m, n, counts;
bool vis[N];
vector<int> adj[N];
vector<int> components;
void dfs(int node)
{
    // preorder
    vis[node] = 1;
    components.push_back(node);
    // inorder
    vector<int>::iterator it;

    for (it = adj[node].begin(); it != adj[node].end(); it++)
    {
        if (vis[*it])
        {
            // do nothing
        }
        else
        {
            dfs(*it);
        }
    }
    // postorder
}

int main()
{
    cin >> n >> m;
    /*try to store degree of each and then sort on the basis of the degree*/
    /*after that also higher index will get more priority*/
    int x, y;
    counts = 0;
    for (int i = 0; i < N; i++)
    {
        vis[i] = false;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    for (int i = 1; i <= n; i++)
    {
        if (vis[i] != 1)
        {
            dfs(i);
            sort(components.begin(), components.end());
            components.clear();
            counts++;
        }
    }
    for (int i = 0; i < N; i++)
    {
        vis[i] = false;
    }
    for (int i = 1; i <= n; i++)
    {
        if (vis[i] != 1)
        {
            dfs(i);
            sort(components.begin(), components.end());
            for (int j = 0; j < components.size(); j++)
            {
                cout << components[j] << " ";
            }
            cout << endl;
            components.clear();
        }
    }
    cout << counts << endl;
    /*after all of this then u wud have to sort the output on the basis of the last vertex*/

    return 0;
}