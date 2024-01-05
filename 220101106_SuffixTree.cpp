#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    string sub = ""; // a substring of the input string
    vector<int> ch;  // vector of child nodes

    Node()
    {
        // empty
    }

    Node(const string &sub, initializer_list<int> children) : sub(sub)
    {
        ch.insert(ch.end(), children);
    }
};

class SuffixTree
{
private:
    vector<Node> nodes;

    void addSuffix(const string &suf)
    {
        int n = 0;
        size_t i = 0;
        while (i < suf.length())
        {
            char b = suf[i];
            int x2 = 0;
            int n2;
            while (true)
            {
                auto children = nodes[n].ch;
                if (x2 == children.size())
                {
                    // no matching child, remainder of suf becomes new node
                    n2 = nodes.size();
                    nodes.push_back(Node(suf.substr(i), {}));
                    nodes[n].ch.push_back(n2);
                    return;
                }
                n2 = children[x2];
                if (nodes[n2].sub[0] == b)
                {
                    break;
                }
                x2++;
            }
            // find the prefix of the remaining suffix in common with the child
            auto sub2 = nodes[n2].sub;
            size_t j = 0;
            while (j < sub2.size())
            {
                if (suf[i + j] != sub2[j])
                {
                    // split n2
                    auto n3 = n2;
                    // new node for the part in common
                    n2 = nodes.size();
                    nodes.push_back(Node(sub2.substr(0, j), {n3}));
                    nodes[n3].sub = sub2.substr(j); // old node loses the part in common
                    nodes[n].ch[x2] = n2;
                    break; // continue down the tree
                }
                j++;
            }
            i += j; // advance past the part in common
            n = n2; // continue down the tree
        }
    }

    void dfs(int n, string currentSubstring, vector<string> &substrings)
    {
        auto children = nodes[n].ch;
        if (children.size() == 0)
        {
            substrings.push_back(currentSubstring + nodes[n].sub);
            return;
        }

        for (int child : children)
        {
            dfs(child, currentSubstring + nodes[n].sub, substrings);
        }
    }

    void inorderTraversal(int n, vector<string> &substrings)
    {
        auto children = nodes[n].ch;
        if (children.size() > 0)
        {
            for (int child : children)
            {
                inorderTraversal(child, substrings);
                substrings.push_back(nodes[child].sub);
            }
        }
    }

    void levelOrderTraversal(vector<string> &substrings)
    {
        queue<int> q;
        q.push(0);

        while (!q.empty())
        {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++)
            {
                int n = q.front();
                q.pop();

                substrings.push_back(nodes[n].sub);

                for (int child : nodes[n].ch)
                {
                    q.push(child);
                }
            }
            // Add a newline after each level
            substrings.push_back("\n");
        }
    }

public:
    SuffixTree(const vector<string> &strings)
    {
        nodes.push_back(Node{});
        for (const string &str : strings)
        {
            for (size_t i = 0; i < str.length(); i++)
            {
                addSuffix(str.substr(i));
            }
        }
    }

    void visualize()
    {
        if (nodes.size() == 0)
        {
            // cout << "\n";
            return;
        }

        function<void(int, const string &)> f;
        f = [&](int n, const string &pre)
        {
            auto children = nodes[n].ch;
            if (children.size() == 0)
            {
                // cout << "- " << nodes[n].sub << '\n';
                return;
            }
            // cout << "+ " << nodes[n].sub << '\n';

            auto it = begin(children);
            if (it != end(children))
                do
                {
                    if (next(it) == end(children))
                        break;
                    // cout << pre << "+-";
                    f(*it, pre + "| ");
                    it = next(it);
                } while (true);

            // cout << pre << "+-";
            f(children[children.size() - 1], pre + "  ");
        };

        f(0, "");
    }

    vector<string> getAllSubstrings()
    {
        vector<string> substrings;
        dfs(0, "", substrings);
        return substrings;
    }

    vector<string> getInorderTraversal()
    {
        vector<string> substrings;
        inorderTraversal(0, substrings);
        return substrings;
    }

    vector<string> getLevelOrderTraversal()
    {
        vector<string> substrings;
        levelOrderTraversal(substrings);
        return substrings;
    }
};

int main()
{
    // vector<string> strings = {"baba$", "abab$"};

    int height = 0;
    int count = 0;
    // cout << "\nLevel Order Traversal:\n";
    vector<string> strings;
    while (cin)
    {
        string a;
        cin >> a;
        strings.push_back(a + "$");
    }
    strings.pop_back();
    SuffixTree suffixTree(strings);
    suffixTree.visualize();
    for (int i = 0; i < strings.size(); i++)
    {
        cout << strings[i] << " ";
    }
    cout << endl;

    vector<string> levelOrderTraversal = suffixTree.getLevelOrderTraversal();
    for (const string &substring : levelOrderTraversal)
    {
        if (substring == "\n")
        {
            // cout << substring; // Print newline
            height++;
        }
        else
        {
            // cout << substring << " ";
            count++;
        }
    }
    cout << count - 1 << endl;
    cout << height - 1 << endl;

    return 0;
    // cout
}
