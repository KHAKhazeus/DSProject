//
// Created by Khazeus on 2018-12-29.
//

#include "Graph.h"
#include <iostream>
#include <limits>
#include <string>

void outputTitle(){
    std::cout << "**" << "\t\t\t\t" << "电网造价模拟系统" << "\t\t\t" << "**" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "**" << "\t\t\t" << "请选择要执行的操作:" << "\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t  " << "A --- 创建电网顶点" << "\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t  " << "B --- 添加电网的边" << "\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t  " << "C --- 构造最小生成树" << "\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t  " << "D --- 显示最小生成树" << "\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t\t" << "E --- 退出程序" << "\t\t\t" << "**" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << std::endl;
}

Graph<std::string> systemGraph = Graph<std::string>();
Graph<std::string> MST = Graph<std::string>();

void basic_control(){
    while(true){
        char control;
        std::cout << "请选择操作:";
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
                std::cout << "请输入顶点的个数: ";
                int number;
                while (!(std::cin >> number) || number <= 0) {
                    std::cin.clear();// 恢复状态标志
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                    std::cerr << "请输入正整数:";
                }
                std::cout << "请依次输入各顶点的名称:" << std::endl;
                for(auto i = 1; i <= number; i++){
                    std::string newName;
                    while(!(std::cin >> newName)){
                        std::cin.clear();// 恢复状态标志
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                        std::cerr << "请重新输入";
                    }
                    systemGraph.insertNewVertice(newName);
                }
                break;
            }

            case 'B':{
                while(true){
                    std::cout << "请输入两个顶点以及边:";
                    std::string firstVertice, secondVertice;
                    int edgeValue;
                    while (!(std::cin >> firstVertice >> secondVertice >> edgeValue)) {
                        std::cin.clear();// 恢复状态标志
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                        std::cerr << "请重新输入:";
                    }
                    if(firstVertice == "?" || systemGraph.findVertice(firstVertice) == nullptr
                         || systemGraph.findVertice(secondVertice) == nullptr){
                        break;
                    }
                    systemGraph.addNewEdge(firstVertice, secondVertice, edgeValue);
                }
                break;
            }

            case 'C':{
                std::cout << "请输入起始顶点: " << std::endl;
                std::string startName;
                while (!(std::cin >> startName) || !systemGraph.findVertice(startName)) {
                    std::cin.clear();// 恢复状态标志
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                    std::cerr << "请重新输入:";
                }
                MST = systemGraph.primMinSpanTree(systemGraph.findVertice(startName));
                std::cout << "生成Prim最小树" << std::endl;
                break;
            }

            case 'D':{
                std::cout << "最小生成树的顶点及边为:" << std::endl;
                MST.outputAllEdges();
                MST.outputAllEdgesasHTML();
            }

            default:
                break;
        }
        std::cout << std::endl;
    }
}

int main(){

    outputTitle();
    basic_control();

    return 0;
}