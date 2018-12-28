//First Question: 考试报名系统
//TODO:项目功能要求：
//已知两个非降序链表序列S1和S2，设计函数构造出S1和S2的交集新链表S3。
//输入说明：输入分2行，分别在每行给出由若干个正整数构成的非降序序列，用-1表示序列的结尾（-1不属于这个序列）。数字用空格间隔。
//输出说明：在一行中输出两个输入序列的交集序列，数字间用空格分开，结尾不能有多余空格；若新链表为空，输出NULL。

#include <iostream>
#include <limits>
#include "NonDecreaseList.h"

//根据需要重载
std::istream& operator>>(std::istream& in, NonDecreaseList<int>& target){
    //输入保护
    int value;
    while(true){
        while(!(std::cin >> value)){
            std::cin.clear();// 恢复状态标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
            std::cerr << "链表数据类型错误，请重新输入:" << std::endl;
        }
        if(value == -1){
            break;
        }
        else{
            target.insert(value);
        }
    }
    return in;
}

template<typename DataType>
std::ostream& operator<<(std::ostream& out, NonDecreaseList<DataType>& target){
    auto temp = target.gethead();
    for(auto i = 1; i <= target.getSize(); i++){
        temp = temp->getNext();
        DataType data = temp->getData();
        out << data << std::endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, NonDecreaseList<int>& target){
    auto size = target.getSize();
    if(size){
        auto temp = target.gethead();
        for(auto i = 1; i <= size; i++){
            temp = temp->getNext();
            int data = temp->getData();
            if(i == size){
                out << data;
            }
            else{
                out << data << " ";
            }
        }
        out << std::endl;
    }
    else{
        out << "NULL" << std::endl;
    }
    return out;
}

//memory test passed
int main(){
    NonDecreaseList<int> first = NonDecreaseList<int>();
    NonDecreaseList<int> second = NonDecreaseList<int>();
    std::cin >> first >> second;
    auto result = first.intersectionWith(second);
    std::cout << result;
    return 0;
}

