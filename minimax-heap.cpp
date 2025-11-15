#include<bit>
#include "minimax-heap.hpp"

using namespace std;

// swap two integers
void MinimaxHeap::swap(int& a, int& b) {
    int temp = a;
    a=b;
    b=temp;
}
void MinimaxHeap::trickleUp(int i) {
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

void MinimaxHeap::trickleDown(int i) {
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

MinimaxHeap::MinimaxHeap(unsigned size) {
    harr = new int[size];
    capacity = size;
    size = 0;
}

MinimaxHeap::~MinimaxHeap() {
    delete [] harr;
}

bool MinimaxHeap::empty() {
    return !size;
}

int MinimaxHeap::layer(int i) {
    // __countl_zero() - counts the amount of bits on the left side of number
    // returns the position of the most significant bit
    return sizeof(int) * 8 - __countl_zero<unsigned>(i+1);
}
int MinimaxHeap::parent(int i) {
    return (i - 1) / 2;
}
int MinimaxHeap::left(int i) {
    return i*2 + 1;
}
int MinimaxHeap::right(int i) {
    return i*2 + 2;
}

// return min element in subtree that starts from i
// (root element is considered to be the minimal one)
int MinimaxHeap::getMin(int i) {
    return harr[0];
}
int MinimaxHeap::getMax(int i) {
    if(size < 3) {
        return harr[size - 1];
    } else {
        return harr[harr[1] > harr[2] ? 1 : 2];
    }
}
void MinimaxHeap::insert(int val) {
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
void MinimaxHeap::extract(int i) {
    swap(harr[i], harr[size-1]);
    size--;
    trickleUp(harr[i]);
    trickleDown(harr[i]);
} 

