//
// Created by Khazeus on 2018-12-29.
//

#ifndef DSPROJECT_MINHEAP_H
#define DSPROJECT_MINHEAP_H

//由于内容直接使用比较对象，从而不需要管理释放问题，只需要管理数组的释放问题
template <typename DataType>
class MinHeap{
public:
    explicit MinHeap(int size):_size(size){ store = new DataType[size]; }

    ~MinHeap(){
        delete []store;
    }

    DataType getStore(int pos){
        return store[pos];
    }

    int getSize(){
        return _size;
    }

    void insertItem(DataType target){
        store[_size] = target;
        _size++;
        siftUp(_size - 1);
    }

    //constructFromGraph

    virtual void siftDown(int rootPos) = 0;

    virtual void siftUp(int startPos) = 0;

    void constructMinHeap(){
        for(auto i = (_size - 1)/2; i >= 0; i++){
            siftDown(i);
        }
    }

    DataType popMin(){
        auto result = store[0];
        swap(0, _size - 1);
        siftDown(0);
        return result;
    }

    void swap(int first, int second){
        auto temp = store[first];
        store[first] = store[second];
        store[second] = temp;
    }

private:
    int _size;
    DataType* store;
};

#endif //DSPROJECT_MINHEAP_H
