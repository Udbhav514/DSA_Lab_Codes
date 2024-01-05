#include <bits/stdc++.h>
using namespace std;
vector<int> inorderVals;
vector<int> preorderVals;
vector<int> levelOrderVals;
vector<int> allchildren;
class TreeNode
{
public:
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int data) : data(data), left(nullptr), right(nullptr) {}
};

void levelOrderInsert(TreeNode *&root, int data)
{
    if (root == nullptr)
    {
        root = new TreeNode(data);
        return;
    }

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *current = q.front();
        q.pop();

        if (current->left == nullptr)
        {
            current->left = new TreeNode(data);
            break;
        }
        else
        {
            q.push(current->left);
        }

        if (current->right == nullptr)
        {
            current->right = new TreeNode(data);
            break;
        }
        else
        {
            q.push(current->right);
        }
    }
}

void preorderTraversal(TreeNode *root)
{
    if (root == nullptr)
        return;

    // cout << root->data << " ";
    preorderVals.push_back(root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void inorderTraversal(TreeNode *root)
{
    if (root == nullptr)
        return;

    inorderTraversal(root->left);
    // cout << root->data << " ";
    inorderVals.push_back(root->data);
    inorderTraversal(root->right);
}

void levelOrderTraversal(TreeNode *root)
{
    if (root == nullptr)
        return;

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *current = q.front();
        q.pop();

        // cout << current->data << " ";
        levelOrderVals.push_back(current->data);

        if (current->left)
        {
            q.push(current->left);
        }
        if (current->right)
        {
            q.push(current->right);
        }
    }
}
void all_children(int ind, int n)
{
    if (2 * ind <= n)
    {
        allchildren.push_back(2 * ind);
        all_children(2 * ind, n);
    }
    if (2 * ind + 1 <= n)
    {
        allchildren.push_back(2 * ind + 1);
        all_children(2 * ind + 1, n);
    }
    else
    {
        return;
    }
}
int main()
{
    int n;
    cin >> n;
    int a[n + 1];
    int sorted[n + 1];
    int sortedescend[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sorted[i] = a[i];
    }
    sort(sorted + 1, sorted + n + 1);
    for (int i = 1; i <= n; i++)
    {
        sortedescend[i] = sorted[n + 1 - i];
    }

    TreeNode *root = nullptr;
    for (int i = 1; i <= n; i++)
    {
        levelOrderInsert(root, i);
    }

    levelOrderTraversal(root);

    preorderTraversal(root);

    inorderTraversal(root);

    /*now after taking the preorder traversal.........
    allocate the values to its respective number*/
    int levelinar[n + 1];
    for (int i = 0; i < n; i++)
    {
        levelinar[preorderVals[i]] = a[i + 1];
    }

    // have the preorder(a)
    // got the level order(levellinar)
    int inorderar[n + 1];
    for (int i = 0; i < n; i++)
    {
        inorderar[i + 1] = levelinar[inorderVals[i]];
    }

    // now have the inorder(inorderar)

    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        if (sortedescend[i] == inorderar[i])
        {
            count++;
        }
    }
    if (count == n)
    {
        cout << "Yes" << endl;
    }
    // 7// 200 400 600 700 50 20 10
    else
    {
        // do more stuff
        cout << "No" << endl;
        /*now for every element in array a*/
        for (int i = 1; i <= n; i++)
        {
            int tosearch = a[i];
            int parind;
            for (int j = 1; j <= n; j++)
            {
                if (tosearch == levelinar[j])
                {
                    parind = j;
                    break;
                }
            }
            /*create a vector checker and pushback all the elements in it which need to be checked*/
            allchildren.push_back(2 * parind);
            all_children(2 * parind, n);
            int finalsss = 0;
            for (int i = 0; i < allchildren.size(); i++)
            {
                // checking for left
                if (levelinar[allchildren[i]] < tosearch)
                {
                    finalsss++;
                }
            }
            int k = allchildren.size();
            for (int i = 0; i < k; i++)
            {
                allchildren.pop_back();
            }

            allchildren.push_back(2 * parind + 1);
            all_children(2 * parind + 1, n);
            for (int i = 0; i < allchildren.size(); i++)
            {
                // checking for right
                if (levelinar[allchildren[i]] > tosearch)
                {

                    finalsss++;
                }
            }
            if (finalsss > 0)
            {
                cout << tosearch << endl;
                break;
            }
        }
    }

    return 0;
}
