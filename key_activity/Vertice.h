//
// Created by Khazeus on 2018-12-29.
//

#ifndef DSPROJECT_VERTICE_H
#define DSPROJECT_VERTICE_H


template<typename T>
class Edge;

template <typename DataType>
class Vertice{
public:

    friend class VerticeTable;

    DataType getData(){
        return _data;
    }

    void setData(const DataType& data){
        _data = data;
    }

    void setFirstInEdge(Edge<DataType>* edge){
        _firstIn = edge;
    }

    void setFirstOutEdge(Edge<DataType>* edge){
        _firstOut = edge;
    }

    Edge<DataType>* getFirstIn(){
        return _firstIn;
    }

    Edge<DataType>* getFirstOut(){
        return _firstOut;
    }

    void setTopographOrder(int order){
        _topographOrder = order;
    }

    int getTopographOrder(){
        return _topographOrder;
    }

    static Vertice* createVertice(DataType data){
        auto *p = new Vertice(data);
        return p;
    };

    static Vertice* getNewHeadNode(){
        auto *p = new Vertice();
        return p;
    };

    const int getRef(){ return _ref; }
    void upRef(){ _ref++; }
    void deRef(){ _ref--; }
    ~Vertice(){
//        std::cout << "destruct one" << "data:" << typeid(_data).hash_code() << std::endl;
    }

private:

    explicit Vertice(const DataType data): _data(data), _firstOut(nullptr), _firstIn(nullptr), _topographOrder(-1),
        _ref(0){
//        std::cout << "construct one" << "data:" << typeid(_data).hash_code() << std::endl;
    }
    //_data must have auto constructor
    Vertice(): _data(), _firstOut(nullptr), _firstIn(nullptr), _topographOrder(-1), _ref(0){
//        std::cout << "construct one" << "data:" << typeid(_data).hash_code() << std::endl;
    }

    DataType _data;
    Edge<DataType>* _firstIn;
    Edge<DataType>* _firstOut;
    int _topographOrder;
    int _ref;
};

#endif //DSPROJECT_VERTICE_H
