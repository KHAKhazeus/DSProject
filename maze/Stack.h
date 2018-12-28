//
// Created by Khazeus on 2018/10/24.
//

#ifndef DSPROJECT_LIST_H
#define DSPROJECT_LIST_H

#include "ListNode.h"

template <typename T>
class Stack{

    typedef T DataType;

public:
    ~Stack(){ makeEmpty(); delete _head;}
    void upSize(){ _size++; }
    void downSize(){ _size--;}
    void setSize(int size){ _size = size; }
    int getSize(){return _size;}
    Stack(): _head(ListNode<DataType>::getNewHeadNode()), _size(0), _rear(nullptr){ _rear = _head; }
    ListNode<DataType>* gethead(){ return _head; }

    bool push(DataType data){
        auto p = ListNode<DataType>::createNode(data);
        if(p != nullptr){
            if(!gethead()->getNext()){
                _rear = p;
            }
            p->setNext(gethead()->getNext());
            gethead()->setNext(p);
            p->upRef();
            upSize();
            return true;
        }
        else{
            return false;
        }
    }

    bool isEmpty(){
        return getSize() <= 0;
    }

    //如果队列为空，则peek返回nullptr
    DataType peek(){
        return gethead()->getNext()->getData();
    }

    bool pop(){
        if(getSize()){
            auto temp = gethead()->getNext();
            gethead()->setNext(temp->getNext());
            temp->deRef();
            this->downSize();
            if(!temp->getRef()){
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
