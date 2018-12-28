//
// Created by Khazeus on 2018-12-28.
//

#ifndef DSPROJECT_TREENODE_H
#define DSPROJECT_TREENODE_H

#define TEST

#ifdef TEST

#include <iostream>

#endif



template <typename T>
class TreeNode {

    typedef T DataType;
    template <typename U>
    friend class Tree;

public:

    static TreeNode* createNode(DataType data){
        auto *p = new TreeNode(data);
        return p;
    };

    static TreeNode* getCopyof(const TreeNode &from){
        auto *p = new TreeNode(from.getData());
        return p;
    };

    static TreeNode* getNewHeadNode(){
        auto *p = new TreeNode();
        return p;
    };

    void setNextSibling(TreeNode *next_sibling){
        auto p= _next_sibling;
        _next_sibling = next_sibling;
    };

    void setFirstChild(TreeNode *first_child){
        _first_child = first_child;
    }

    void setParent(TreeNode *parent){
        _parent = parent;
    }

    void setPreviousSibling(TreeNode *previousSibling){
        _previous_sibling = previousSibling;
    }

    DataType& getData(){ return _data; }
    void setData(DataType data){ _data = data; }
    TreeNode* getNextSibling(){ return _next_sibling; }
    TreeNode* getFirstChild(){ return _first_child; }
    TreeNode* getParent(){ return _parent; }
    TreeNode* getPreviousSibling(){ return _previous_sibling; }
    ~TreeNode(){
//        std::cout << "destruct one" << "data:" << typeid(_data).hash_code() << std::endl;
    }

private:

    explicit TreeNode(const DataType data): _data(data), _next_sibling(nullptr), _first_child(nullptr),
        _previous_sibling(nullptr), _parent(nullptr){
//        std::cout << "construct one" << "data:" << typeid(_data).hash_code() << std::endl;
    }
    //_data must have auto constructor
    TreeNode(): _data(), _next_sibling(nullptr), _first_child(nullptr), _previous_sibling(nullptr),
        _parent(nullptr){
//        std::cout << "construct one" << "data:" << typeid(_data).hash_code() << std::endl;
    }
    DataType _data;
    TreeNode *_next_sibling;
    TreeNode *_previous_sibling;
    TreeNode *_first_child;
    TreeNode *_parent;
};

#endif //DSPROJECT_TREENODE_H
