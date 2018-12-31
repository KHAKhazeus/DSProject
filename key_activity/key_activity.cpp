//
// Created by Khazeus on 2018-12-30.
//


#include <iostream>
#include "Graph.h"
#include <limits>
#include <vector>
#include <algorithm>

void inputGraph(Graph<int>& systemGraph){
    int numberOfVertices, numberOfEdges;
    while (!(std::cin >> numberOfVertices >> numberOfEdges) || numberOfVertices <= 0 || numberOfEdges <= 0) {
        std::cin.clear();// 恢复状态标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
        std::cerr << "请输入正整数:";
    }
    for(auto i = 1; i <= numberOfEdges; i++){
        int outVertice, inVertice, value;
        while (!(std::cin >> outVertice >> inVertice >> value) || outVertice <= 0 || inVertice <= 0 || value <= 0) {
            std::cin.clear();// 恢复状态标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
            std::cerr << "请输入正整数:";
        }
        if(!systemGraph.isInVertices(outVertice)){
            systemGraph.insertNewVertice(outVertice);
        }
        if(!systemGraph.isInVertices(inVertice)){
            systemGraph.insertNewVertice(inVertice);
        }
        systemGraph.addNewEdge(inVertice, outVertice, value, i);
    }

}

void generateKeyActivity(Graph<int>& systemGraph){
    int* Ve = new int[systemGraph.getVerticesSize() + 1]();
    int* Vl = new int[systemGraph.getVerticesSize() + 1];
    for(auto topo = 2; topo <= systemGraph.getVerticesSize(); topo++){
        auto target = systemGraph.getVerticeByTopo(topo);
        if(target->getFirstIn() != nullptr){
            auto edge = target->getFirstIn();
            while(edge){
                if(Ve[edge->getOutVertice()->getTopographOrder()] + edge->getValue() > Ve[topo]){
                    Ve[topo] = Ve[edge->getOutVertice()->getTopographOrder()] + edge->getValue();
                }
                edge = edge->getNextInEdge();
            }
        }
    }

    std::cout << Ve[systemGraph.getVerticesSize()] << std::endl;

    for(auto init = 1; init <= systemGraph.getVerticesSize(); init++){
        Vl[init] = Ve[systemGraph.getVerticesSize()];
    }
    for(auto topo = systemGraph.getVerticesSize() - 1; topo >= 1; topo--){
        auto target = systemGraph.getVerticeByTopo(topo);
        if(target->getFirstOut() != nullptr){
            auto edge = target->getFirstOut();
            while(edge){
                if(Vl[edge->getInVertice()->getTopographOrder()] - edge->getValue() < Vl[topo]){
                    Vl[topo] = Vl[edge->getInVertice()->getTopographOrder()] - edge->getValue();
                }
                edge = edge->getNextOutEdge();
            }
        }
    }

    std::vector<Edge<int>*> result;
    List<Edge<int>*> edgesList = systemGraph.getEdgesList();
    if(edgesList.getSize()){
        auto edge = edgesList.gethead()->getNext();
        while(edge){
            auto outVertice = edge->getData()->getOutVertice();
            auto inVertive = edge->getData()->getInVertice();
            if(Ve[outVertice->getTopographOrder()] ==
               Vl[inVertive->getTopographOrder()] - edge->getData()->getValue()){
                result.push_back(edge->getData());
            }
            edge = edge->getNext();
        }
    }
    std::stable_sort(result.begin(), result.end(), [](Edge<int>* first, Edge<int>* second){
        auto firstOut = first->getOutVertice();
        auto secondOut = second->getOutVertice();
        if(firstOut->getData() < secondOut->getData()){
            return true;
        }
        else if(firstOut->getData() == secondOut->getData()){
            auto firstOrder = first->getInputOrder();
            auto secondOrder = second->getInputOrder();
            if(firstOrder > secondOrder){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    });

    for(auto edge : result){
        std::cout << edge->getOutVertice()->getData() << " -> " << edge->getInVertice()->getData() << std::endl;
    }

}

int main(){

    while(true){
        Graph<int> systemGraph = Graph<int>();
        inputGraph(systemGraph);
        bool feasiblility = systemGraph.generateTopologicalOrder();
        if(feasiblility){
            generateKeyActivity(systemGraph);
        }
        else{
            std::cout << "0" << std::endl;
        }

        int control;
        std::cout << "是否继续(1为继续, 0为停止):";
        while (!(std::cin >> control) || (control != 0 && control != 1)) {
            std::cin.clear();// 恢复状态标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
            std::cerr << "请输入正整数:";
        }
        if(control == 0){
            break;
        }
    }

    return 0;
}