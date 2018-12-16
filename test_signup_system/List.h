//
// Created by Khazeus on 2018/10/24.
//

#ifndef DSPROJECT_LIST_H
#define DSPROJECT_LIST_H

#include "ListNode.h"

template <typename T>
class List{

    typedef T DataType;

public:

    ~List(){ makeEmpty();}
    void upSize(){ _size++; }
    void downSize(){ _size--;}
    void setSize(int size){ _size = size; }
    int getSize(){return _size;}
    List(): _head(ListNode<DataType>::getNewHeadNode()), _size(0), _rear(nullptr){ _rear = _head; }
    ListNode<DataType>* gethead(){ return _head; }

    bool insertBack(DataType data){
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

    bool insert(int pos, DataType data){
        auto temp = gethead();
        if(pos >= 1 && pos <= getSize() + 1){
            for(int i = 0; i < pos - 1; i ++){
                temp = temp->getNext();
            }
            auto newNode = ListNode<DataType>::createNode(data);

            if(newNode != nullptr){
                newNode->setNext(temp->getNext());
                temp->setNext(newNode);
                upSize();
                if(temp == _rear){
                    _rear = newNode;
                }
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }

    bool deleteNodeByPos(int pos){
        auto temp = gethead();
        if(pos >= 1 && pos <= getSize()){
            for(int i = 0; i < pos - 1; i++){
                temp = temp->getNext();
            }
            auto deleteNode = temp->getNext();
            temp->setNext(deleteNode->getNext());
            if(deleteNode == _rear){
                _rear = temp;
            }
            downSize();
            if(deleteNode->getRef() == 0){
                delete deleteNode;
            }
            return true;
        }
        else{
            return false;
        }

    }

    ListNode<DataType>* searchByPos(int pos){
        auto goal = gethead();
        if(pos >= 1 && pos <= getSize()){
            for(int i = 0; i <= pos - 1; i ++){
                goal = goal->getNext();
            }
            return goal;
        }
        else{
            return nullptr;
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
