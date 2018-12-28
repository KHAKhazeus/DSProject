//
// Created by Khazeus on 2018-12-28.
//

#ifndef DSPROJECT_TREE_H
#define DSPROJECT_TREE_H
#include "TreeNode.h"

template <typename DataType>
class Tree{
public:

    ~Tree(){
        makeEmpty();
        delete _root;
    }

    Tree():_root(TreeNode<DataType>::getNewHeadNode()), _size(0){}

    TreeNode<DataType>* getRoot(){
        return _root;
    }

    TreeNode<DataType>* searchFor(DataType& target){

    }

    bool insertAsChild(TreeNode<DataType>* target, DataType value){
        auto newNode = new TreeNode<DataType>(value);
        if(newNode != nullptr){
            auto temp = target->getFirstChild();
            if(temp){
                while(temp->getNextSibling()){
                    temp = temp->getNextSibling();
                };
                temp->setNextSibling(newNode);
                newNode->setPreviousSibling(temp);
            }
            else{
                target->setFirstChild(newNode);
                newNode->setParent(target);
            }
            upSize();
            return true;
        }
        else{
            return false;
        }
    }

    void deleteFromRoot(TreeNode<DataType> *target){
        auto nextSibling = target->getNextSibling();
        auto previousSibling = target->getPreviousSibling();
        auto parent = target->getParent();
        if(parent){
            //FirstChild
            parent->setFirstChild(nextSibling);
        }
        if(previousSibling){
            //前面有兄弟
            previousSibling->setNextSibling(nextSibling);
        }
        if(nextSibling){
            nextSibling->setPreviousSibling(previousSibling);
        }
        deleteNode(target->getFirstChild());
        delete target;
        downSize();
    }

    //按照二叉树形式删除
    void deleteNode(TreeNode<DataType> *target){
        while(target->getNextSibling() != nullptr || target->getFirstChild() != nullptr){
            if(target->getFirstChild()){
                deleteNode(target->getFirstChild());
            }
            else{
                deleteNode(target->getNextSibling());
            }
        }
        auto nextSibling = target->getParent();
        auto previousSibling = target->getPreviousSibling();
        auto parent = target->getParent();
        if(parent){
            //FirstChild
            parent->setFirstChild(nextSibling);
        }
        if(previousSibling){
            //前面有兄弟
            previousSibling->setNextSibling(nextSibling);
        }
        delete target;
        downSize();
    }

    void downSize(){
        _size--;
    }

    void upSize(){
        _size++;
    }

    void makeEmpty(){
        if(getSize()){
            deleteNode(getRoot()->getFirstChild());
        }
        _size = 0;
    };

    int getSize(){
        return _size;
    }


private:
    TreeNode<DataType>* _root;
    int _size;
};


#endif //DSPROJECT_TREE_H
