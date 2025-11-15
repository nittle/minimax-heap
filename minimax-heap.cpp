#include<iostream>
#include<vector>
#include<bit>

using namespace std;
class MinimaxHeap {

    // swap two integers
    void swap(int& a, int& b) {
        int temp = a;
        a=b;
        b=temp;
    }
    void trickleUp(int i) {
            int currLayer = layer(i);
            int par = parent(i);
            int grandPar = parent(par);

            if(currLayer % 2 == 0) { // even layer
                // if on even layer and new el is smaller than parent, swap
                if(harr[i] < harr[par])
                    swap(harr[i], harr[par]);
                if(harr[i] > harr[grandPar] && currLayer > 2)
                    swap(harr[i], harr[grandPar]);
            } else { // odd
                if(harr[i] > harr[par]) 
                    swap(harr[i], harr[par]);
                if(harr[i] < harr[grandPar] && currLayer > 2) 
                    swap(harr[i], harr[grandPar]);
            }

            if(i != 0)  {
                trickleUp(par);
            }
    }

    void trickleDown(int i) {
        // current layer - layer of the current element
        int currLayer = layer(i);
        int lastLayer = layer(size - 1);

        // If element is on the last layer then it doesnt have children
        if(currLayer == lastLayer) return;

        int swappedWith = -1;
        int leftChild = left(i);
        int rightChild = right(i);

        if(currLayer % 2 == 0) { // even layer
            if(harr[i] > harr[leftChild]) {
                    swappedWith = leftChild;
                    swap(harr[i], harr[leftChild]);
                }
            if(harr[i] > harr[rightChild]) {
                swappedWith = rightChild;
                swap(harr[i], harr[rightChild]);
            }
        } else { // odd
            if(harr[i] < harr[leftChild]) {
                swappedWith = leftChild;
                swap(harr[i], harr[leftChild]);
            }
            if(harr[i] < harr[rightChild]) {
                swappedWith = rightChild;
                swap(harr[i], harr[rightChild]);
            }
        }

        if(swappedWith != -1)  {
            trickleUp(swappedWith);
        }
    }

    void heapify() {
        int n = size;

        int bottomLayer = layer(harr[n-1]);

        int i = n - 1;
        while (layer(harr[i]) == bottomLayer)
        {
            trickleUp(i);
            i--;
        }
        
        
    }
    public:
    int* harr;
    unsigned capacity;
    unsigned size;

    MinimaxHeap(unsigned size) {
        harr = new int[size];
        capacity = size;
        size = 0;
    }

    ~MinimaxHeap() {
        delete [] harr;
    }

    bool empty() {
        return !size;
    }

    int layer(int i) {
        // __countl_zero() - counts the amount of bits on the left side of number
        // returns the position of the most significant bit
        return sizeof(int) * 8 - __countl_zero<unsigned>(i+1);
    }
    int parent(int i) {
        return (i - 1) / 2;
    }
    int left(int i) {
        return i*2 + 1;
    }
    int right(int i) {
        return i*2 + 2;
    }

    // return min element in subtree that starts from i
    // (root element is considered to be the minimal one)
    int getMin(int i) {
        return harr[0];
    }
    void extractMin() {
        extract(0);
    }
    // int decreaseKey(int i, int newKey) {

    // }
    void insert(int val) {
        if(empty()) {
            harr[0] = val;
        } else {
            int ind = size;
            harr[ind] = val;
            int i = ind;
            trickleUp(i);
        }
        size++;
    }
    void extract(int i) {
        swap(harr[i], harr[size-1]);
        size--;
        trickleUp(harr[i]);
        trickleDown(harr[i]);
    } 
};

void printArr(int* arr, int size) {
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    const int capacity = 100;
    MinimaxHeap* heap = new MinimaxHeap(capacity);

    vector<int> arr = {9, 12, 15, 20, 4, 7, 45, 32, 14, 10, 22, 2};
    for(int el : arr) {
        heap->insert(el);
    }
    
    printArr(heap->harr, heap->size);
    cout << heap->size << endl;

    heap->extract(2);
    printArr(heap->harr, heap->size);
    return 0;
}