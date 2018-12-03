//
// Created by Khazeus on 2018/10/24.
//

#ifndef DSPROJECT_LIST_H
#define DSPROJECT_LIST_H

#include "ListNode.h"

template <typename T>
class List{

    typedef T DataType;
//    void test(){
//        _head<int>;
//        _head<float>;
//    }



public:

    ~List(){ makeEmpty();}

    void upSize(){ _size++; }
    void setSize(int size){ _size = size; }
    int getSize(){return _size;}

    void insertBack(DataType data){
        auto p = new ListNode<DataType>(data);
        _rear->setNext(p);
        p->upRef();
        upSize();
        _rear = _rear->getNext();
    }

    void makeEmpty();

    List(): _head(ListNode<DataType>::getNewHeadNode()), _size(0), _rear(nullptr){ _rear = _head; }

private:
    /*
     * template <typename U>
     * static ListNode<U> *_head;
     */

    ListNode<DataType> *_head;
    int _size;
    ListNode<DataType> *_rear;

};

template <typename DataType>
void List<DataType>::makeEmpty() {
    auto cur = _head;
    while(_head->getNext()){
        cur = _head->getNext();
        _head->setNext(cur->getNext());
        cur->deRef();
        if( cur->getRef() == 0){
            delete cur;
        }
    }
    _rear = _head;
    setSize(0);
}

#endif //DSPROJECT_LIST_H
