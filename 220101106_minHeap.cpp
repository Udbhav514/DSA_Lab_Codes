#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
vector<int> heapInVector;
class MinHeap
{
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int i)
    {
        while (i > 0 && heap[i] < heap[parent(i)])
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i)
    {
        int minIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < heap.size() && heap[left] < heap[minIndex])
        {
            minIndex = left;
        }

        if (right < heap.size() && heap[right] < heap[minIndex])
        {
            minIndex = right;
        }

        if (i != minIndex)
        {
            swap(heap[i], heap[minIndex]);
            heapifyDown(minIndex);
        }
    }

public:
    MinHeap() {}

    void insert(int value)
    {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int extractMin()
    {
        if (heap.empty())
        {
            return -1; // or any appropriate error value
        }

        int minValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return minValue;
    }

    void status()
    {
        heapInVector.clear();
        for (int i = 0; i < heap.size(); i++)
        {
            // cout << heap[i] << " ";
            heapInVector.push_back(heap[i]);
        }
    }
};

int main()
{
    MinHeap minHeap;
    int extractedValue = -1; // Initialize extractedValue outside the switch
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int b;
        cin >> b;
        minHeap.insert(b);
    }

    int eleCount = 1;
    int level = 2;
    while (eleCount <= n)
    {
        eleCount = eleCount + level;
        level = level * 2;
    }
    minHeap.status();

    int toremove = n - (eleCount - level / 2);

    for (int i = 0; i < toremove; i++)
    {
        minHeap.extractMin();
    }
    minHeap.status();

    int lp = 1, rp = 3;
    int addlp = 2, addrp = 4;
    while (rp <= heapInVector.size())
    {
        auto itstarter = heapInVector.begin() + lp;
        auto itender = heapInVector.begin() + rp;
        reverse(itstarter, itender);
        lp = lp + addlp;
        rp = rp + addrp;
        addlp = addlp * 2;
        addrp = addrp * 2;
    }
    cout << heapInVector.size() << endl;
    for (int i = 0; i < heapInVector.size(); i++)
    {
        cout << heapInVector[i] << endl;
    }
    cout << endl;

    return 0;
}

