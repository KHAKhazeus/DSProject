//FifthQuestion
//TODO:项目要求
//项目内容：
//设某银行有A，B两个业务窗口，且处理业务的速度不一样，
//其中A窗口处理速度是B窗口的2倍----即当A窗口每处理完2个顾客是，B窗口处理完1个顾客。
//给定到达银行的顾客序列，请按照业务完成的顺序输出顾客序列。
//假定不考虑顾客信后到达的时间间隔，并且当不同窗口同时处理完2个顾客时，A窗口的顾客优先输出。

#include <limits>
#include <iostream>
#include "Queue.h"

//class Customer{
//public:
//    int id;
//    int time;
//    Customer():id(-1), time(-1){}
//    Customer(int newId, int newTime):id(newId), time(newTime){}
//};

//class TimeQueue: public Queue<Customer>{
//public:
//    void addTime(){
//        if(getSize()){
//            auto temp = gethead()->getNext();
//            while(temp){
//                temp->getData().time++;
//                temp = temp->getNext();
//            }
//        }
//    }
//};

void constructQueues(Queue<int>& queueA, Queue<int>& queueB){
    std::cout << "请输入:" << std::endl;
    int number;
    while (!(std::cin >> number) || number <= 0) {
        std::cin.clear();// 恢复状态标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
        std::cerr << "第一个数为总人数，目前输入不符合要求，请重新输入";
    }
    for(auto i = 1; i <= number; i++){
        int id;
        while (!(std::cin >> id) || id <= 0) {
            std::cin.clear();// 恢复状态标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
            std::cerr << "第" << i << "个人id不符合要求，请从该人重新输入";
        }
        if(id % 2 == 0){
            queueB.enQueue(id);
        }
        else{
            queueA.enQueue(id);
        }
    }
}

void solveOnce(Queue<int>& queueA, Queue<int>& queueB){
    int time = 0;
    while(queueA.getSize() || queueB.getSize()){
        time++;
        if(!queueA.getSize()){
            while(queueB.getSize()){
                auto next = queueB.peekQueue();
                queueB.deQueue();
                std::cout << next << " ";
            }
        }
        else if(!queueB.getSize()){
            while(queueA.getSize()){
                auto next = queueA.peekQueue();
                queueA.deQueue();
                std::cout << next << " ";
            }
        }
        else{
            if(time % 2 == 0){
                auto nextA = queueA.peekQueue();
                auto nextB = queueB.peekQueue();
                queueA.deQueue();
                queueB.deQueue();
                std::cout << nextA << " " << nextB << " ";
            }
            else{
                auto nextA = queueA.peekQueue();
                queueA.deQueue();
                std::cout << nextA << " ";
            }
        }
    }
    std::cout << std::endl;
}


int main(){
    std::cout << "银行业务窗口模拟:" << std::endl;
    while(true){
        int control;
        Queue<int> queueA = Queue<int>();
        Queue<int> queueB = Queue<int>();
        std::cout << "输入1以继续，输入0退出";
        while (!(std::cin >> control) || ((control != 0) && (control != 1))) {
            std::cin.clear();// 恢复状态标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
            std::cerr << "请输入0或1:";
        }
        if(control){
            constructQueues(queueA, queueB);
            solveOnce(queueA, queueB);
        }
        else{
            break;
        }
    }


    return 0;
}