#include <iostream>
#include <strings.h>
using namespace std;
/*Searching for the root*/
int search(char array[], char c, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (array[i] == c)
        {
            return i;
            break;
        }
    }
    return -1;
}
/*printing postorder using reccursion*/
void printing_post_order(char in[], char pre[], int size)
{
    int root = search(in, pre[0], size);
    if (root != 0)
    {
        printing_post_order(in, pre + 1, root);
    }
    if (root != size - 1)
    {
        printing_post_order(in + root + 1, pre + root + 1, size - root - 1);
    }
    cout << pre[0];
}
int main()
{
    string preorders;
    string inorders;
    cin >> preorders >> inorders;
    char pre[preorders.size()];
    char in[inorders.size()];
    for (int i = 0; i < preorders.size(); i++)
    {
        pre[i] = preorders[i];
        in[i] = inorders[i];
    }

    printing_post_order(in, pre, preorders.size());
    cout << endl;
    return 0;
}