//
// Created by Khazeus on 2018/10/24.
//

#ifndef DSPROJECT_LIST_H
#define DSPROJECT_LIST_H

#include "ListNode.h"

//Note: DataType Should be Comparable
template <typename T>
class NonDecreaseList{

    typedef T DataType;

public:

    ~NonDecreaseList(){ makeEmpty(); delete _head;}
    void upSize(){ _size++; }
    void downSize(){ _size--;}
    void setSize(int size){ _size = size; }
    int getSize(){return _size;}
    NonDecreaseList(): _head(ListNode<DataType>::getNewHeadNode()), _size(0), _rear(nullptr){ _rear = _head; }
    ListNode<DataType>* gethead(){ return _head; }

    NonDecreaseList intersectionWith(NonDecreaseList& that){
        auto newList = NonDecreaseList();
        auto thisPointer = this->gethead()->getNext();
        auto thatPointer = that.gethead()->getNext();
        auto thisEnd = this->_rear;
        auto thatEnd = that._rear;
        while(thisPointer && thatPointer){
            if(thisPointer->getData() == thatPointer->getData()) {
                newList.insert(thisPointer->getData());
                thisPointer = thisPointer->getNext();
                thatPointer = thatPointer->getNext();
            }
            else if(thisPointer->getData() > thatPointer->getData()){
                thatPointer = thatPointer->getNext();
            }
            else{
                thisPointer = thisPointer->getNext();
            }
        }
        return newList;
    }

    bool insert(DataType data){
        auto temp = gethead();
        while(temp->getNext() && temp->getNext()->getData() < data) {
            temp = temp->getNext();
        }
        if((temp->getNext()) && temp -> getNext() -> getData() == data){
            return false;
        }
        else{
            auto newNode = ListNode<DataType>::createNode(data);
            newNode->setNext(temp->getNext());
            temp->setNext(newNode);
            newNode->upRef();
            upSize();
            return true;
        }
    }

    bool deleteByValue(DataType value){
        bool result = false;
        int i = 0;
        auto temp = gethead();
        while(temp->getNext() && temp -> getNext() -> getData() < value){
            temp = temp->getNext();
            i++;
        }
        if(!temp->getNext()){
            result = false;
        }
        else if(temp -> getNext() -> getData() == value){
            result = deleteNodeByPos(++i);
            downSize();
        }
        return result;
    }

    bool searchByValue(DataType value){
        bool result = false;
        int i = 0;
        auto temp = gethead();
        while(temp->getNext() && temp -> getNext() -> getData() < value){
            temp = temp->getNext();
            i++;
        }
        if(!temp->getNext()){
            result = false;
        }
        if(temp -> getNext() -> getData() == value){
            result = true;
        }
        return result;
    }

    bool deleteNodeByPos(int pos){
        auto temp = gethead();
        if(pos >= 1 && pos <= getSize()){
            for(int i = 0; i < pos - 1; i++){
                temp = temp->getNext();
            }
            auto deleteNode = temp->getNext();
            temp->setNext(deleteNode->getNext());
            deleteNode->deRef();
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
