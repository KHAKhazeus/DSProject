//
// Created by Khazeus on 2018-12-29.
//

#ifndef DSPROJECT_EDGELIST_H
#define DSPROJECT_EDGELIST_H

#include "Edge.h"
#include <vector>
#include "List.h"

template <typename DataType>
class EdgeList{

public:
    ~EdgeList(){  allEdges.makeEmpty();}
    int getSize(){return allEdges.getSize();}
    EdgeList(): allEdges(List<Edge<DataType>*>()){}

    EdgeList& operator=(const EdgeList& right){
        ListNode<Edge<DataType>*>* temp = right.getEdgesList().gethead();
        temp->upRef();
        temp = temp->getNext();
        while(temp){
            temp->upRef();
            temp->getData()->upRef();
            temp = temp->getNext();
        }
        allEdges = right.getEdgesList();
        return *this;
    }

    List<Edge<DataType>*>& getEdgesList(){
        return allEdges;
    }

    const List<Edge<DataType>*>& getEdgesList() const{
        return allEdges;
    }

    Edge<DataType>* getHead(){
        return allEdges.gethead();
    }

    void insertNewEdges(Edge<DataType>* newEdge){
        newEdge->upRef();
        allEdges.insertBack(newEdge);
    }

private:

    List<Edge<DataType>*> allEdges;
};

#endif //DSPROJECT_EDGELIST_H
