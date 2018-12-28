//Sixth Question
//TODO:项目功能要求
//本项目的实质是完成兑家谱成员信息的建立，查找，插入，修改，删除等功能，
//可以首先定义家族成员数据结构，然后将每个功能作为一个成员函数来完成对数据的操作，
//最后完成主函数以验证各个函数功能并得到运行结果。

#include "Tree.h"
#include <iostream>

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

int main(){
    outputTitle();

    return 0;
}