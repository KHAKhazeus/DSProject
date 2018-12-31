//
// Created by Khazeus on 2018-12-29.
//

#ifndef DSPROJECT_GRAPH_H
#define DSPROJECT_GRAPH_H

#include "VerticesTable.h"
#include "EdgeList.h"
#include <fstream>
#include <random>

template <typename DataType>
class GraphMinHeap{
public:

    ~GraphMinHeap(){
        for(auto i = 0; i < _size; i++){
            store[i]->deRef();
        }
    }

    explicit GraphMinHeap(const int size):_size(0), store(nullptr){
        store = new Edge<DataType>*[size];
    }

    Edge<DataType>* getStore(int pos){
        return store[pos];
    }

    int getSize(){
        return _size;
    }

    void insertItem(Edge<DataType>* target){
        target->upRef();
        store[_size] = target;
        _size++;
        siftUp(_size - 1);
    }

    void swap(int first, int second){
        auto temp = store[first];
        store[first] = store[second];
        store[second] = temp;
    }

    static GraphMinHeap<DataType> constructMinHeapFromGraphEdges(EdgeList<DataType>& edges){
        GraphMinHeap<DataType> resultHeap = GraphMinHeap(edges.getSize());
        if(edges.getSize()){
            auto temp = edges.getEdgesList().gethead()->getNext();
            while(temp){
                temp->getData()->upRef();
                resultHeap.insertItem(temp->getData());
                temp = temp->getNext();
            }
        }
        return resultHeap;
    }

    void siftDown(int rootPos) {
        for(;rootPos <= (getSize() - 1)/2;){
            auto leftChild = rootPos * 2 + 1;
            auto rightChild = rootPos * 2 + 2;
            int target = rightChild;
            if(rightChild >= _size){
                if(leftChild < _size){
                    target = leftChild;
                }
                else{
                    break;
                }
            }
            else if(getStore(leftChild)->getValue() < getStore(rightChild)->getValue()){
                target = leftChild;
            }
            if(getStore(target)->getValue() < getStore(rootPos)->getValue()){
                swap(target, rootPos);
                rootPos = target;
            }
            else{
                break;
            }
        }
    }

    void siftUp(int startPos) {
        for(;startPos > 0;){
            auto parent = (startPos - 1)/2;
            if(getStore(parent)->getValue() > getStore(startPos)->getValue()){
                swap(parent, startPos);
                startPos = parent;
            }
            else{
                break;
            }
        }
    }

    Edge<DataType>* popMin(){
        auto result = store[0];
        swap(0, _size - 1);
        _size--;
        siftDown(0);
        return result;
    }


private:
    int _size;
    Edge<DataType>** store;
};

template <typename DataType>
class Graph{
public:

    ~Graph(){
        allEdges.getEdgesList().makeEmpty();
        allVertices.getVerticesList().makeEmpty();
    }

    List<Edge<DataType>*> getEdgesList(){
        return allEdges.getEdgesList();
    }

    int getVerticesSize(){
        return allVertices.getSize();
    }

    int getEdgesSize(){
        return allEdges.getSize();
    }

    Edge<DataType>* getEdgeByOrder(int order){
        Edge<DataType>* result = nullptr;
        if(allEdges.getSize()){
            ListNode<Edge<DataType>*>* node = allEdges.getEdgesList().gethead()->getNext();
            while(node){
                if(node->getData()->getInputOrder() == order){
                    result = node->getData();
                }
            }
        }
        return result;
    }

    Vertice<DataType>* getVerticeByTopo(int topoValue){
        Vertice<DataType>* result = nullptr;
        if(allVertices.getSize()){
            ListNode<Vertice<DataType>*>* node = allVertices.getVerticesList().gethead()->getNext();
            while(node){
                if(node->getData()->getTopographOrder() == topoValue){
                    result = node->getData();
                }
                node = node->getNext();
            }
        }
        return result;
    }

    bool isInVertices(DataType& value){
        if(allVertices.findVerticeByValue(value)){
            return true;
        }
        else{
            return false;
        }
    }

    Graph& operator=(const Graph& right){
        if(this != &right){
            auto tempVer = right.allVertices.getVerticesList().gethead();
            tempVer->upRef();
            tempVer = tempVer->getNext();
            while(tempVer){
                tempVer->upRef();
                tempVer->getData()->upRef();
                tempVer = tempVer->getNext();
            }
            auto tempEdge = right.allEdges.getEdgesList().gethead();
            tempEdge->upRef();
            tempEdge = tempEdge->getNext();
            while(tempEdge){
                tempEdge->upRef();
                tempEdge->getData()->upRef();
                tempEdge = tempEdge->getNext();
            }
        }
        allVertices = right.allVertices;
        allEdges = right.allEdges;
        return *this;
    }

    Graph(): allVertices(VerticesTable<DataType>()), allEdges(EdgeList<DataType>()){}

    Vertice<DataType>* findVertice(const DataType& data){
        return allVertices.findVerticeByValue(data);
    }

    void outputAllEdges(){
        if(allEdges.getSize()){
            auto temp = allEdges.getEdgesList().gethead()->getNext();
            while(temp){
                std::cout << temp->getData()->getInVertice()->getData() << "<-("
                    << temp->getData()->getValue() << ")->" << temp->getData()->getOutVertice()->getData() << "\t";
                temp = temp->getNext();
            }
            std::cout << std::endl;
        }
    }

    void outputAllEdgesasHTML(){

        std::ofstream jsFile;
#ifdef _WIN32
        jsFile.open("..\\electric_network\\graph.html");
#else
        jsFile.open("../electric_network/graph.html");
#endif
        jsFile << "<!DOCTYPE html>\n"
                  "<html>\n"
                  "  <head>\n"
                  "    <meta charset=\"utf-8\">\n"
                  "    <title>一个简单的关系图</title>\n"
                  "    <!-- 引入 G6 文件 -->\n"
                  "    <script src=\"./g6.js\"></script>\n"
                  "  </head>\n"
                  "  <body>\n"
                  "    <!-- 创建图容器 -->\n"
                  "    <div id=\"mountNode\"></div>\n"
                  "    <script>\n"
                  "      const data = {\n"
                  "        nodes: [";
        if(allVertices.getSize()){
            auto temp = allVertices.getVerticesList().gethead()->getNext();
            while(temp){
                auto value = temp->getData()->getData();
                long xplace = (random()%(100 - 1 + 1) + 1) * 10;
                long yplace = (random()%(50 - 1 + 1) + 1) * 20;
                jsFile << "{ id: '" << value << "', x: " << xplace << ", y:" << yplace << ", label: '" << value <<
                    "'},";
                temp = temp->getNext();
            }
        }
        jsFile << "], edges:[ ";
        if(allEdges.getSize()){
            auto temp = allEdges.getEdgesList().gethead()->getNext();
            while(temp){
                auto first = temp->getData()->getInVertice()->getData();
                auto second = temp->getData()->getOutVertice()->getData();
                auto value = temp->getData()->getValue();
                jsFile << "{id: '" << temp << "', source: '" << first << "', target: '"
                    << second << "', label: '" << value << "'},";
                temp = temp->getNext();
            }
        }
        jsFile << "]";
        jsFile << "      };\n"
                  "      const graph = new G6.Graph({\n"
                  "        container: 'mountNode',\n"
                  "        width: 1000,\n"
                  "        height: 1000\n"
                  "      });\n"
                  "      graph.read(data);\n"
                  "    </script>\n"
                  "  </body>\n"
                  "</html>";
        jsFile.close();
    }

    bool insertNewVertice(const DataType& value){
        auto temp = Vertice<DataType>::createVertice(value);
        if(temp != nullptr){
            allVertices.insertNewVertices(temp);
            return true;
        }
        else{
            return false;
        }
    }

    bool insertNewVertice(Vertice<DataType>* value){
        if(value != nullptr){
            allVertices.insertNewVertices(value);
            return true;
        }
        else{
            return false;
        }
    }

    bool addNewEdge(DataType InValue, DataType OutValue, int edgeValue, int order){
        auto inVertice = allVertices.findVerticeByValue(InValue);
        auto outVertice = allVertices.findVerticeByValue(OutValue);
        auto newEdge = Edge<DataType>::createEdge(edgeValue);
        newEdge->setValue(edgeValue);
        if(inVertice == nullptr || outVertice == nullptr){
            return false;
        }
        else{
            newEdge->setInVertice(inVertice);
            newEdge->setOutVertice(outVertice);
            if(inVertice->getFirstIn() == nullptr){
                inVertice->setFirstInEdge(newEdge);
            }
            else{
                auto temp = inVertice->getFirstIn();
                while(temp->getNextInEdge()){
                    temp = temp->getNextInEdge();
                }
                temp->setNextInEdge(newEdge);
            }
            if(outVertice->getFirstOut() == nullptr){
                outVertice->setFirstOutEdge(newEdge);
            }
            else{
                auto temp = outVertice->getFirstOut();
                while(temp->getNextOutEdge()){
                    temp = temp->getNextOutEdge();
                }
                temp->setNextOutEdge(newEdge);
            }
            //最后存入边的list之中以备删除时执行内存释放
            newEdge->setInputOrder(order);
            allEdges.insertNewEdges(newEdge);
            return true;
        }
    }

    Graph primMinSpanTree(Vertice<DataType>* start){
        auto MST = Graph();
        auto minHeap = GraphMinHeap<DataType>(allEdges.getSize());
        VerticesTable<DataType> selectedList;
        int size = 1;
        selectedList.insertNewVertices(start);
        if(allVertices.getSize()){
            auto temp = allVertices.getVerticesList().gethead()->getNext();
            while(temp){
                MST.insertNewVertice(temp->getData()->getData());
                temp->getData()->upRef();
                temp = temp->getNext();
            }
        }
        auto in = start->getFirstIn();
        auto out = start->getFirstOut();
        while(in){
            minHeap.insertItem(in);
            in->upRef();
            in = in->getNextInEdge();
        }
        while(out){
            minHeap.insertItem(out);
            out->upRef();
            out = out->getNextOutEdge();
        }
        while(size != allVertices.getSize()){
            auto temp = minHeap.popMin();
            auto newVertices = temp->getInVertice();
            if(selectedList.isIn(newVertices)){
                newVertices = temp->getOutVertice();
                if(selectedList.isIn(newVertices)){
                    continue;
                }
            }
            selectedList.insertNewVertices(newVertices);
            newVertices->upRef();
            size++;
            MST.addNewEdge(temp->getInVertice()->getData(), temp->getOutVertice()->getData(), temp->getValue());
            auto newIn = newVertices->getFirstIn();
            auto newOut = newVertices->getFirstOut();
            while(newIn){
                minHeap.insertItem(newIn);
                newIn->upRef();
                newIn = newIn->getNextInEdge();
            }
            while(newOut){
                minHeap.insertItem(newOut);
                newOut->upRef();
                newOut = newOut->getNextOutEdge();
            }
        }
        return MST;
    }

    bool generateTopologicalOrder(){

    }

private:
    VerticesTable<DataType> allVertices;
    EdgeList<DataType> allEdges;
};

template <>
bool Graph<int>::generateTopologicalOrder(){
    if(allVertices.getSize()){
        int topo = 1;
        int* count = new int[allVertices.getSize() + 1]();
        int top = -1;
        List<Vertice<int>*> vertice = allVertices.getVerticesList();
        ListNode<Vertice<int>*>* verticeNext = vertice.gethead()->getNext();
        while(verticeNext != nullptr){
            auto inEdge = verticeNext->getData()->getFirstIn();
            while(inEdge){
                count[verticeNext->getData()->getData()]++;
                inEdge = inEdge->getNextInEdge();
            }
            verticeNext = verticeNext->getNext();
        }
        for(auto i = 1; i <= allVertices.getSize(); i++){
            if(count[i] == 0){
                count[i] = top;
                top = i;
            }
        }
        auto topoCount = 0;
        while(topoCount < allVertices.getSize()){
            if(top == -1){
                return false;
            }
            else{
                auto target = top;
                top = count[target];
                topoCount++;
                Vertice<int>* targetVertice = allVertices.findVerticeByValue(target);
                targetVertice->setTopographOrder(topoCount);
                auto edge = targetVertice->getFirstOut();
                while(edge){
                    count[edge->getInVertice()->getData()]--;
                    edge = edge->getNextOutEdge();
                }
                for(auto i = 1; i <= allVertices.getSize(); i++){
                    if(count[i] == 0){
                        count[i] = top;
                        top = i;
                    }
                }
            }
        }
        return true;
    }
    else{
        return false;
    }
}
#endif //DSPROJECT_GRAPH_H
