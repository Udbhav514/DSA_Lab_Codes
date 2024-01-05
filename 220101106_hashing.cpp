#include <bits/stdc++.h>
using namespace std;
int hashf(int n, int k)
{
    return (n) % (k);
}
int main()
{
    float threshold;
    cin >> threshold;
    float buckets;
    cin >> buckets;
    vector<vector<int>> v(buckets);

    // how to take input till it is available

    float numkeys = 0;
    vector<int> keysinserted;
    vector<int> realkeys;
    while (cin)
    {
        int n;
        cin >> n;
        realkeys.push_back(n);
    }
    realkeys.pop_back();
    for (int i = 0; i < realkeys.size(); i++)
    {
        int n = realkeys[i];
        int checker = 0;
        for (int i = 0; i < buckets; i++)
        {
            for (int j = 0; j < v[i].size(); j++)
            {
                if (v[i][j] == n)
                {
                    checker++;
                }
            }
        }
        if (checker > 0)
        {
            cout << "Key " << n << " already present in the hash table. Status of the hash table." << endl;
            cout << "Number of keys: " << numkeys << endl;
            cout << "Number of buckets: " << buckets << endl;

            for (int i = 0; i < buckets; i++)
            {
                cout << "Bucket " << i << ":  ";
                if (v[i].size() >= 1)
                {

                    for (int j = 0; j < v[i].size() - 1; j++)
                    {
                        cout << v[i][j] << ", ";
                    }
                    cout << v[i][v[i].size() - 1] << " ";
                }
                else
                {
                    for (int j = 0; j < v[i].size(); j++)
                    {
                        cout << v[i][j] << ", ";
                    }
                }
                cout << endl;
            }
            cout << endl;
        }
        else
        {
            numkeys++;
            if ((numkeys / buckets) > threshold)
            {
                v[hashf(n, buckets)].push_back(n);
                keysinserted.push_back(n);
                // have to do some complicated stuff
                v.clear();

                buckets = buckets * 3;
                // vector<vector<int>> v(buckets);
                v.resize(buckets);
                for (int m = 0; m < keysinserted.size(); m++)
                {
                    int p = keysinserted[m];

                    v[hashf(p, buckets)].push_back(p);
                }
            }
            else
            {
                // cout << numkeys / buckets << " threshold check" << endl;
                v[hashf(n, buckets)].push_back(n);
                keysinserted.push_back(n);
            }
        }
    }

    return 0;
}
