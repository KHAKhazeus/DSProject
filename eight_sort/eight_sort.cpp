//
// Created by Khazeus on 2018-12-31.
//

#include <iostream>
#include <limits>
#include <random>
#include <vector>
#include <ctime>
#include "IntMeanHeap.h"

void outputTitle(){
    std::cout << "**" << "\t\t\t\t" << "排序算法比较" << "\t\t\t\t" << "**" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "**" << "\t\t\t\t" << "1 --- 冒泡排序" << "\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t\t" << "2 --- 选择排序" << "\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t\t" << "3 --- 直接插入排序" << "\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t\t" << "4 --- 希尔排序" << "\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t\t" << "5 --- 快速排序" << "\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t\t" << "6 --- 堆排序" << "\t\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t\t" << "7 --- 归并排序" << "\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t\t" << "8 --- 基数排序" << "\t\t\t" << "**" << std::endl;
    std::cout << "**" << "\t\t\t\t" << "9 --- 退出程序" << "\t\t\t" << "**" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << std::endl;
}

int partition(int left, int right, std::vector<int>& source, long int& swapTimes){
    auto pivot = left;
    for(auto i = left + 1; i <= right; i++){
        if(source[i] < source[left]){
            pivot++;
            auto temp = source[i];
            source[i] = source[pivot];
            source[pivot] = temp;
            swapTimes++;
        }
    }
    auto temp = source[pivot];
    source[pivot] = source[left];
    source[left] = temp;
    swapTimes++;
    return pivot;
}

void quick_sort(int left, int right, std::vector<int>& source, long int& swapTimes){
    if(left < right){
        auto pivot = partition(left, right, source, swapTimes);
        quick_sort(left, pivot -1, source, swapTimes);
        quick_sort(pivot + 1, right, source, swapTimes);
    }
    else{
        return;
    }
}

void quick_sort(std::vector<int> source){
    long int swapTimes = 0;
    auto left = 0;
    auto right = static_cast<int>(source.size() - 1);
    auto start = clock();
    quick_sort(left, right, source, swapTimes);
    auto stop = clock();
    std::cout << "快速排序所用时间: " << stop - start << std::endl;
    std::cout << "快速排序交换次数: " << swapTimes << std::endl;
}

void heap_sort(std::vector<int> source){
    long int swapTimes = 0;
    IntMinHeap minHeap = IntMinHeap(static_cast<int>(source.size()));
    auto start = clock();
    for(auto i: source){
        minHeap.insertItem(i, swapTimes);
    }
    for(auto i = 0; i <= source.size() - 1; i++){
        auto target = minHeap.popMin(swapTimes);
        source[i] = target;
    }
    auto stop = clock();
    std::cout << "堆排序所用时间: " << stop - start << std::endl;
    std::cout << "堆排序交换次数: " << swapTimes << std::endl;
    for(auto i: source){
        std::cout << i << " ";
    }
    std::cout << std::endl;
}


void shell_sort(std::vector<int> source){
    long int swapTimes = 0;
    auto start = clock();
    int gap = static_cast<int>(floor(source.size()/2.2));
    while(gap){
        for(auto groupHead = 0; groupHead < gap; groupHead++){
            for(auto inGroup = groupHead; inGroup <= source.size() - 1; inGroup += gap){
                auto target = source[inGroup];
                int compPos;
                for(compPos = inGroup - gap; compPos >= 0; compPos -= gap){
                    if(source[compPos] > target){
                        source[compPos + gap] = source[compPos];
                        swapTimes++;
                    }
                    else{
                        break;
                    }
                }
                source[compPos + gap] = target;
                swapTimes++;
            }
        }
        if(gap == 1){
            break;
        }
        gap = static_cast<int>(floor(gap/2.2));
        if(gap == 0){
            gap = 1;
        }
    }
    auto stop = clock();
    std::cout << "希尔插入排序所用时间: " << stop - start << std::endl;
    std::cout << "希尔插入排序交换次数: " << swapTimes << std::endl;
}

void insert_sort(std::vector<int> source){
    long int swapTimes = 0;
    auto start = clock();
    for(auto out = 1; out < source.size(); out++){
        auto target = source[out];
        int in;
        for(in = out - 1; in >=0 ; in--){
            if(target < source[in]){
                source[in + 1] = source[in];
                swapTimes++;
            }
            else{
                break;
            }
        }
        source[in + 1] = target;
        swapTimes++;
    }
    auto stop = clock();
    std::cout << "直接插入排序所用时间: " << stop - start << std::endl;
    std::cout << "直接插入排序交换次数: " << swapTimes << std::endl;
}

void select_sort(std::vector<int> source){
    long int swapTimes = 0;
    auto start = clock();
    for(auto out = 0; out < source.size() - 1; out++){
        auto smallest = out;
        for(auto times = out; times <= source.size() - 1; times++){
            if(source[times] < source[smallest]){
                smallest = times;
            }
        }
        auto temp = source[out];
        source[out] = source[smallest];
        source[smallest] = temp;
        swapTimes++;
    };
    auto stop = clock();
    std::cout << "选择排序所用时间: " << stop - start << std::endl;
    std::cout << "选择排序交换次数: " << swapTimes << std::endl;
    std::cout << std::endl;
}

void bubble_sort(std::vector<int> source){
    long int swapTimes = 0;
    auto start = clock();
    for(auto out = 1; out < source.size(); out++){
        bool swap = false;
        for(auto times = source.size() - 1; times >= out; times-- ){
            if(source[times] < source[times - 1]){
                auto temp = source[times];
                source[times] = source[times - 1];
                source[times - 1] = temp;
                swap = true;
                swapTimes++;
            }
        }
        if(!swap){
            break;
        }
    }
    auto stop = clock();
    std::cout << "冒泡排序所用时间: " << stop - start << std::endl;
    std::cout << "冒泡排序交换次数: " << swapTimes << std::endl;
    std::cout << std::endl;
}

void cardinal_sort(std::vector<int> source){
    long int swapTimes = 0;
    auto start = clock();

    auto stop = clock();
}


int main(){
    outputTitle();
    std::vector<int> source;
    int size;
    std::cout << "请输入要产生的随机数的个数" << std::endl;
    while (!(std::cin >> size) || size <= 0) {
        std::cin.clear();// 恢复状态标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
        std::cerr << "请输入正整数";
    }
    for(auto i = 1; i <= size; i++){
        source.push_back(i - 1);
    }
    long long int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(source.begin(), source.end(), std::default_random_engine(seed));
    while(true){
        int control;
        std::cout << "请选择排序算法: ";
        while (!(std::cin >> control) || control <= 0 || control >=10) {
            std::cin.clear();// 恢复状态标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
            std::cerr << "请输入1-9的整数";
        }
        if(control == 9){
            break;
        }
        else{
            switch(control){
                case 1:{
                    bubble_sort(source);
                    break;
                }
                case 2:{
                    select_sort(source);
                    break;
                }
                case 3:{
                    insert_sort(source);
                    break;
                }
                case 4:{
                    shell_sort(source);
                    break;
                }
                case 5:{
                    quick_sort(source);
                    break;
                }
                case 6:{
                    heap_sort(source);
                    break;
                }
                case 8:{

                }
            }
        }
    }
}