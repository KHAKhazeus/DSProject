//Sixth Question
//TODO:项目功能要求
//本项目的实质是完成兑家谱成员信息的建立，查找，插入，修改，删除等功能，
//可以首先定义家族成员数据结构，然后将每个功能作为一个成员函数来完成对数据的操作，
//最后完成主函数以验证各个函数功能并得到运行结果。

#include "Tree.h"
#include <iostream>
#include <string>
#include <limits>

class FamilyTree: public Tree<std::string>{
public:
    TreeNode<std::string>* getAncestor(){
        return getRoot()->getFirstChild();
    }

    void outputFirstGenerationChild(TreeNode<std::string>* parent){
        for(auto i = parent->getFirstChild(); i != nullptr; i = i->getNextSibling()){
            std::cout << i->getData() << " ";
        }
        std::cout << std::endl;
    }

    void seperateFamily(TreeNode<std::string>* target){
        std::cout << "要解散家庭的人是: " << target->getData() << std::endl;
        std::cout << target->getData() << "的第一代子孙是: ";
        outputFirstGenerationChild(target);
        deleteNode(target->getFirstChild());
    }
};

FamilyTree familyTree = FamilyTree();

void outputTitle(){
    std::cout << "**" << "\t\t\t\t" << "家谱管理系统" << "\t\t\t\t" << "**" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "**" << "\t\t\t" << "请选择要执行的操作:" << "\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t\t" << "A --- 完善家谱" << "\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t  " << "B --- 添加家庭成员" << "\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t  " << "C --- 解散局部家庭" << "\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t  " << "D --- 更改家庭成员姓名" << "\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t\t" << "E --- 退出程序" << "\t\t\t" << "**" << std::endl;
    std::cout << "==========================================" << std::endl;
}

void initiateAncestor(){
    std::cout << "首先请建立一个家谱" << std::endl;
    std::cout << "请输入祖先的名字: ";
    std::string ancestor;
    while (!(std::cin >> ancestor)) {
        std::cin.clear();// 恢复状态标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
        std::cerr << "请重新输入:";
    }
    familyTree.insertAsChild(familyTree.getRoot(), ancestor);
    auto ancestorNode = familyTree.getAncestor();
    std::cout << "此家谱的祖先是: " << ancestorNode->getData() << std::endl << std::endl;
}

void basic_function(){
    while(true){
        char control;
        std::cout << "请输入要执行的操作:";
        while (!(std::cin >> control) || (control != 'A' && control != 'B' && control != 'C' && control != 'D'
            && control != 'E')) {
            std::cin.clear();// 恢复状态标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
            std::cerr << "请重新输入:";
        }
        if(control == 'E'){
            break;
        }
        switch(control){
            case 'A': {
                std::string parentName;
                std::cout << "请输入要建立家庭的人的姓名:";
                while (!(std::cin >> parentName)) {
                    std::cin.clear();// 恢复状态标志
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                    std::cerr << "请重新输入:";
                }
                auto target = familyTree.searchNode(parentName, familyTree.getRoot());
                if (target == nullptr) {
                    std::cerr << "家谱中暂无此人" << std::endl;
                } else if (target->getFirstChild()) {
                    std::cerr << "该人已有家庭, 如需要添加子女，请使用添加操作" << std::endl;
                } else {
                    std::cout << "请输入儿女人数: ";
                    int number;
                    while (!(std::cin >> number) || number <= 0) {
                        std::cin.clear();// 恢复状态标志
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                        std::cerr << "儿女人数应是正整数，请重新输入: ";
                    }
                    std::cout << "请依次输入" << target->getData() << "儿女的姓名: ";
                    for (auto i = 1; i <= number; i++) {
                        std::string childName;
                        while (!(std::cin >> childName)) {
                            std::cin.clear();// 恢复状态标志
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                            std::cerr << "儿女名字读入异常, 请重新输入";
                        }
                        familyTree.insertAsChild(target, childName);
                    }
                    std::cout << "现在" << target->getData() << "的第一代子孙有:";
                    familyTree.outputFirstGenerationChild(target);
                }
                std::cout << std::endl;
                break;
            }
            case 'B': {
                std::cout << "请输入要添加儿女的人的姓名: ";
                std::string parentName;
                while (!(std::cin >> parentName)) {
                    std::cin.clear();// 恢复状态标志
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                    std::cerr << "请重新输入:";
                }
                auto target = familyTree.searchNode(parentName, familyTree.getRoot());
                if (target == nullptr) {
                    std::cerr << "家谱中暂无此人" << std::endl;
                }
                else {
                    std::cout << "请输入需要添加的儿女人数: ";
                    int number;
                    while (!(std::cin >> number) || number <= 0) {
                        std::cin.clear();// 恢复状态标志
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                        std::cerr << "儿女人数应是正整数，请重新输入: ";
                    }
                    std::cout << "请依次输入" << target->getData() << "新添加的儿女的姓名: ";
                    for (auto i = 1; i <= number; i++) {
                        std::string childName;
                        while (!(std::cin >> childName)) {
                            std::cin.clear();// 恢复状态标志
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                            std::cerr << "儿女名字读入异常, 请重新输入";
                        }
                        familyTree.insertAsChild(target, childName);
                    }
                    std::cout << "现在" << target->getData() << "的第一代子孙有:";
                    familyTree.outputFirstGenerationChild(target);
                    std::cout << std::endl;
                    break;
                }
            }
            case 'C':{
                std::cout << "请输入要解散家庭的人的姓名:";
                std::string parentName;
                while (!(std::cin >> parentName)) {
                    std::cin.clear();// 恢复状态标志
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                    std::cerr << "请重新输入:";
                }
                auto target = familyTree.searchNode(parentName, familyTree.getRoot());
                if(target == nullptr){
                    std::cerr << "家谱中暂无此人" << std::endl;
                }
                else{
                    familyTree.seperateFamily(target);
                }
                std::cout << std::endl;
                break;
            }

            case 'D':{
                std::cout << "请输入要更改姓名的人现在的姓名:";
                std::string previousName;
                while (!(std::cin >> previousName)) {
                    std::cin.clear();// 恢复状态标志
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                    std::cerr << "请重新输入:";
                }
                auto target = familyTree.searchNode(previousName, familyTree.getRoot());
                if(target == nullptr){
                    std::cerr << "家谱中暂无此人" << std::endl;
                }
                else{
                    std::cout << "请输入更改后的姓名: ";
                    std::string currentName;
                    while (!(std::cin >> currentName)) {
                        std::cin.clear();// 恢复状态标志
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                        std::cerr << "请重新输入:";
                    }
                    target->setData(currentName);
                    std::cout << previousName <<"已更名为" << target->getData() << std::endl;
                }
                std::cout << std::endl;
                break;
            }
            
            default:
                break;
        }
    }
}

int main(){
    outputTitle();
    initiateAncestor();
    basic_function();
    return 0;
}