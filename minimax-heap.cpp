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

    void heapify() {
        int n = harr.size();

        int bottomLayer = layer(harr[n-1]);

        int i = n - 1;
        while (layer(harr[i]) == bottomLayer)
        {
            trickleUp(i);
            i--;
        }
        
        
    }
    public:
    vector<int> harr;

    int layer(int i) {
        // __countl_zero() - counts the amount of bits on the left side of number
        // returns the position of the most significant bit
        return sizeof(int) * 8 - __countl_zero<unsigned>(i+1);

        // Until parent is not zero, searches next parent and increases layer
        // Goes from the bottom layer to the first and on each passed level increments layer variable
        // if(i == 0) return 1;

        // int layer = 2;
        // int par = parent(i);
        // while(par != 0) {
        //     layer++;
        //     par = parent(par);
        // }
        // return layer;
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
        if(harr.empty()) {
            harr.push_back(val);
        } else {
            harr.push_back(val);
            int i = harr.size() - 1;
            trickleUp(i);
        }
    }
    void extract(int i) {
        harr.erase(harr.begin() + i);
        heapify();
    } 
};

void printVector(vector<int> vect) {
    for (int el : vect) {
        cout << el << " ";
    }
    cout << endl;
}

int main() {
    MinimaxHeap* heap = new MinimaxHeap();

    vector<int> arr = {9, 12, 15, 20, 4, 7, 45, 32, 14, 10, 22, 2};
    for(int el : arr) {
        heap->insert(el);
    }

    printVector(heap->harr);

    heap->extractMin();
    printVector(heap->harr);
    return 0;
}