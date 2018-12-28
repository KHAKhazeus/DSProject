//
// Created by Khazeus on 2018/10/24.
//

#ifndef DSPROJECT_LISTNODE_H
#define DSPROJECT_LISTNODE_H

#define TEST

#ifdef TEST

#include <iostream>

#endif

template <typename T>
class ListNode {

    typedef T DataType;
    template <typename U>
    friend class List;

public:

    static ListNode* createNode(DataType data){
        auto *p = new ListNode(data);
        return p;
    };

    static ListNode* getCopyof(const ListNode &from){
        auto *p = new ListNode(from.getData());
        return p;
    };

    static ListNode* getNewHeadNode(){
        auto *p = new ListNode();
        return p;
    };

    void setNext(ListNode *next_node){
        auto p= _next_node;
        _next_node = next_node;
    };

    DataType& getData(){ return _data; }
    void setData(DataType data){ _data = data; }
    ListNode* getNext(){ return _next_node; }
    const int getRef(){ return _ref; }
    void upRef(){ _ref++; }
    void deRef(){ _ref--; }
    ~ListNode(){
//        std::cout << "destruct one" << "data:" << typeid(_data).hash_code() << std::endl;
    }

private:

    explicit ListNode(const DataType data): _data(data), _next_node(nullptr), _ref(0){
//        std::cout << "construct one" << "data:" << typeid(_data).hash_code() << std::endl;
    }
    //_data must have auto constructor
    ListNode(): _data(), _next_node(nullptr),_ref(-1){
//        std::cout << "construct one" << "data:" << typeid(_data).hash_code() << std::endl;
    }
    DataType _data;
    ListNode *_next_node;
    int _ref;
};




#endif //DSPROJECT_LISTNODE_H
