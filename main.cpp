#include "utils.hpp"
#include "tree.h"
#include <iostream>
#include <algorithm>

using namespace std;


class MyCircularDeque {
private:
    vector<int> arr;
    int begin = 0, end = 0;
    int capacity;

public:
    MyCircularDeque(int k) {
        capacity = k + 1;
        arr = vector(capacity, 0);
    }
    
    bool insertFront(int value) {
        if (isFull()) return false;

        begin = (begin - 1 + capacity) % capacity;
        arr[begin] = value;
        return true;
    }
    
    bool insertLast(int value) {
        if (isFull()) return false;

        arr[end] = value;
        end = (end + 1) % capacity;
        return true;
    }
    
    bool deleteFront() {
        if (isEmpty()) return false;

        begin = (begin + 1) % capacity;
        return true;
    }
    
    bool deleteLast() {
        if (isEmpty()) return false;

        end = (end - 1 + capacity) % capacity;
        return true;
    }
    
    int getFront() {
        if (isEmpty()) return -1;
        else return arr[begin];
    }
    
    int getRear() {
        if (isEmpty()) return -1;
        else return arr[(end - 1 + capacity) % capacity];
    }
    
    bool isEmpty() {
        return begin == end;
    }
    
    bool isFull() {
        return (end + 1) % capacity == begin;
    }
};


int main() {
    // string s = "a0b1c2";

    // auto sol = new Solution();
    // auto ans = sol->reformat(s);

    // cout << "Answer is:\n";
    // cout << ans << endl;
    // // utils::printVec1D(ans);
    // // utils::printVec2D(ans);
    
    // delete sol;
    int k = 3;

    MyCircularDeque* obj = new MyCircularDeque(k);
    cout << obj->insertLast(1) << endl;
    cout << obj->insertLast(2) << endl;
    cout << obj->insertFront(3) << endl;
    cout << obj->insertLast(4) << endl;
    cout << obj->getRear() << endl;
    cout << obj->isFull() << endl;
    cout << obj->deleteLast() << endl;
    cout << obj->insertFront(4) << endl;
    cout << obj->getFront() << endl;
    
    return 0;
}