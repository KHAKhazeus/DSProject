//
// Created by Khazeus on 2018-12-29.
//


#ifndef DSPROJECT_EDGE_H
#define DSPROJECT_EDGE_H

#include "Vertice.h"

template<typename DataType>
class Edge{
public:
    template <typename U>
    friend class EdgeList;

    int getValue(){
        return _value;
    }

    void setValue(int value){
        _value = value;
    }

    void setNextInEdge(Edge* edge){
        _nextInEdge = edge;
    }

    void setNextOutEdge(Edge* edge){
        _nextOutEdge = edge;
    }

    Edge* getNextInEdge(){
        return _nextInEdge;
    }

    Edge* getNextOutEdge(){
        return _nextOutEdge;
    }

    void setInVertice(Vertice<DataType>* vertice){
        _inVertice = vertice;
    }

    void setOutVertice(Vertice<DataType>* vertice){
        _outVertice = vertice;
    }

    Vertice<DataType>* getInVertice(){
        return _inVertice;
    }

    Vertice<DataType>* getOutVertice(){
        return _outVertice;
    }

    static Edge* createEdge(int value){
        auto *p = new Edge(value);
        return p;
    };

    static Edge* getNewHeadNode(){
        auto *p = new Edge();
        return p;
    };

    const int getRef(){ return _ref; }
    void upRef(){ _ref++; }
    void deRef(){ _ref--; }
    ~Edge(){
//        std::cout << "destruct one" << "data:" << typeid(_data).hash_code() << std::endl;
    }

    explicit Edge(const int value): _value(value), _nextInEdge(nullptr), _nextOutEdge(nullptr), _outVertice(nullptr),
                                    _inVertice(nullptr), _ref(0){
//        std::cout << "construct one" << "data:" << typeid(_data).hash_code() << std::endl;
    }

    //_data must have auto constructor
    Edge(): _value(-1), _nextInEdge(nullptr), _nextOutEdge(nullptr), _outVertice(nullptr),
            _inVertice(nullptr), _ref(0){
//        std::cout << "construct one" << "data:" << typeid(_data).hash_code() << std::endl;
    }

    Edge<DataType>& operator=(const Edge<DataType>& right){
        _value = right.getValue();
        _nextOutEdge = right.getNextOutEdge();
        _nextInEdge = right.getNextInEdge();
        _outVertice = right.getOutVertice();
        _inVertice = right.getInVertice();
        if(this != &right){
            right.upRef();
            _ref = right._ref;
        }
    }

private:

    int _value;
    Edge* _nextInEdge;
    Edge* _nextOutEdge;
    Vertice<DataType>* _outVertice;
    Vertice<DataType>* _inVertice;
    int _ref;
};

#endif //DSPROJECT_EDGE_H