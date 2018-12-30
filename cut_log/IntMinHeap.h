//
// Created by Khazeus on 2018-12-29.
//

#ifndef DSPROJECT_MINHEAP_H
#define DSPROJECT_MINHEAP_H

//由于内容直接使用比较对象，从而不需要管理释放问题，只需要管理数组的释放问题
class IntMinHeap{
public:
    explicit IntMinHeap(const int* origin, int size):_size(size){
        store = new int[size];
        for(auto i = 1; i <= size; i++){
            store[i - 1] = origin[i - 1];
        }
        for(auto i = (size - 1)/2; i >= 0; i --){
            siftDown(i);
        }
    }

    explicit IntMinHeap(int size): _size(0){
        store = new int[size];
    }

    void insert(int newNumber){
        store[_size] = newNumber;
        _size++;
        siftUp(_size - 1);
    }

    ~IntMinHeap(){
        delete []store;
    }

    int getStore(int pos){
        return store[pos];
    }

    int getSize(){
        return _size;
    }

    //constructFromGraph

    void siftDown(int rootPos){
        auto root = rootPos;
        auto target = rootPos * 2 + 1;
        auto temp = store[root];
        while(target <= _size - 1){
            if(target < _size - 1 && store[target] > store[target + 1]){
                target = target + 1;
            }
            if(temp > store[target]){
                store[root] = store[target];
                root = target;
                target = root * 2 + 1;
            }
            else{
                break;
            }
        }
        store[root] = temp;
    }

    void siftUp(int startPos){
        auto temp = store[startPos];
        auto target = startPos;
        auto parent = (startPos - 1)/2;
        while(parent >= 0){
            if(temp < store[parent]){
                store[target] = store[parent];
                target = parent;
                if(target - 1 < 0){
                    break;
                }
                parent = (target - 1)/2;
            }
            else{
                break;
            }
        }
        store[target] = temp;
    }

    int popMin(){
        auto result = store[0];
        store[0] = store[_size - 1];
        _size--;
        siftDown(0);
        return result;
    }

private:
    int _size;
    int* store;
};

#endif //DSPROJECT_MINHEAP_H
