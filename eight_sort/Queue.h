//
// Created by Khazeus on 2018/10/24.
//

#ifndef DSPROJECT_LIST_H
#define DSPROJECT_LIST_H

#include "ListNode.h"

template <typename T>
class Queue{

    typedef T DataType;

public:
    ~Queue(){ makeEmpty(); delete _head;}
    void upSize(){ _size++; }
    void downSize(){ _size--;}
    void setSize(int size){ _size = size; }
    int getSize(){return _size;}
    Queue(): _head(ListNode<DataType>::getNewHeadNode()), _size(0), _rear(nullptr){ _rear = _head; }
    ListNode<DataType>* gethead(){ return _head; }

    bool enQueue(DataType data){
        auto p = ListNode<DataType>::createNode(data);
        if(p != nullptr){
            _rear->setNext(p);
            p->upRef();
            upSize();
            _rear = _rear->getNext();
            return true;
        }
        else{
            return false;
        }
    }

    DataType peekQueue(){
        assert(getSize() != 0);
        return gethead()->getNext()->getData();
    }

    bool deQueue(){
        if(getSize()){
            auto temp = gethead()->getNext();
            gethead()->setNext(temp->getNext());
            temp->deRef();
            downSize();
            if(!getSize()){
                _rear = _head;
            }
            if(temp->getRef() == 0){
                delete temp;
            }
            return true;
        }
        else{
            return false;
        }
    }

    void makeEmpty(){
        while(_head->getNext()){
            auto cur = _head->getNext();
            _head->setNext(cur->getNext());
            cur->deRef();
            if( cur->getRef() == 0){
                delete cur;
            }
        }
        _rear = _head;
        setSize(0);
    };

private:

    ListNode<DataType> *_head;
    int _size;
    ListNode<DataType> *_rear;

};

#endif //DSPROJECT_LIST_H
