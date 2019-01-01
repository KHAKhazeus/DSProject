//
// Created by Khazeus on 2018-12-29.
//

#ifndef DSPROJECT_MINHEAP_H
#define DSPROJECT_MINHEAP_H

class IntMinHeap{
public:
    explicit IntMinHeap(int size):_size(0){ store = new int[size]; }

    ~IntMinHeap(){
        delete []store;
    }

    int getStore(int pos){
        return store[pos];
    }

    int getSize(){
        return _size;
    }

    void insertItem(int target, long int& swapTimes){
        store[_size] = target;
        _size++;
        siftUp(_size - 1, swapTimes);
    }

    void siftDown(int rootPos, long int& swapTimes){
        for(;rootPos <= (getSize() - 1)/2;){
            auto leftChild = rootPos * 2 + 1;
            auto rightChild = rootPos * 2 + 2;
            int target = rightChild;
            if(rightChild >= _size){
                if(leftChild < _size){
                    target = leftChild;
                }
                else{
                    break;
                }
            }
            else if(getStore(leftChild) < getStore(rightChild)){
                target = leftChild;
            }
            if(getStore(target) < getStore(rootPos)){
                swap(target, rootPos);
                swapTimes++;
                rootPos = target;
            }
            else{
                break;
            }
        }
    }

    void siftUp(int startPos, long int& swapTimes){
        for(;startPos > 0;){
            auto parent = (startPos - 1)/2;
            if(getStore(parent) > getStore(startPos)){
                swap(parent, startPos);
                swapTimes++;
                startPos = parent;
            }
            else{
                break;
            }
        }
    }

    int popMin(long int& swapTimes){
        auto result = store[0];
        swap(0, _size - 1);
        _size--;
        siftDown(0, swapTimes);
        return result;
    }

    void swap(int first, int second){
        auto temp = store[first];
        store[first] = store[second];
        store[second] = temp;
    }

private:
    int _size;
    int* store;
};

#endif //DSPROJECT_MINHEAP_H
