//
// Created by Khazeus on 2018-12-29.
//

#ifndef DSPROJECT_NODETABLE_H
#define DSPROJECT_NODETABLE_H

#include "Vertice.h"
#include "List.h"
#include <vector>

template <typename DataType>
class VerticesTable{

public:

    ~VerticesTable(){ _vertices.makeEmpty();}
    int getSize(){ return _vertices.getSize(); }
    VerticesTable(): _vertices(List<Vertice<DataType>*>()){}

    VerticesTable& operator=(const VerticesTable& right){
        ListNode<Vertice<DataType>*>* temp = right.getVerticesList().gethead();
        temp->upRef();
        temp = temp->getNext();
        while(temp){
            temp->upRef();
            temp->getData()->upRef();
            temp = temp->getNext();
        }
        _vertices = right.getVerticesList();
        return *this;
    }

    List<Vertice<DataType>*>& getVerticesList(){
        return _vertices;
    }

    const List<Vertice<DataType>*>& getVerticesList() const{
        return _vertices;
    }

    bool isIn(Vertice<DataType>* target){
        bool result = false;
        auto listNode = _vertices.gethead();
        if(_vertices.getSize()){
            listNode = listNode->getNext();
            while(listNode){
                if(listNode->getData() == target){
                    result = true;
                    break;
                }
                listNode = listNode->getNext();
            }
        }
        return result;
    }

    void insertNewVertices(Vertice<DataType>* target){
        target->upRef();
        _vertices.insertBack(target);
    }

    Vertice<DataType>* findVerticeByValue(DataType value){
        Vertice<DataType>* result = nullptr;
        auto listNode = _vertices.gethead();
        if(_vertices.getSize()){
            listNode = listNode->getNext();
            while(listNode){
                if(listNode->getData()->getData() == value){
                    result = listNode->getData();
                    break;
                }
                listNode = listNode->getNext();
            }
        }
        return result;
    }

private:

    List<Vertice<DataType>*> _vertices;
};
#endif //DSPROJECT_NODETABLE_H
