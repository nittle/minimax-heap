#ifndef _MINIMAXHEAP_H
#define _MINIMAXHEAP_H
class MinimaxHeap {
    void swap(int& a, int& b);
    void trickleUp(int i);
    void trickleDown(int i);

    public:
    int* harr;
    unsigned capacity;
    unsigned size;

    MinimaxHeap(unsigned size);
    ~MinimaxHeap();
    bool empty();
    int layer(int i);
    int parent(int i);
    int left(int i);
    int right(int i);
    int getMin(int i);
    int getMax(int i);
    void insert(int val);
    void extract(int i);
};

#endif