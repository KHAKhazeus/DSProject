//
// Created by Khazeus on 2018-12-30.
//

#include <iostream>
#include <limits>
#include "IntMinHeap.h"

int main(){
    while(true){
        int pieces;
        int total = 0;
        while (!(std::cin >> pieces) || pieces <= 0) {
            std::cin.clear();// 恢复状态标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
            std::cerr << "请输入正整数:";
        }
        IntMinHeap minHeap = IntMinHeap(pieces);
        for(auto i = 1; i <= pieces; i++){
            int newNumber;
            while (!(std::cin >> newNumber) || newNumber <= 0) {
                std::cin.clear();// 恢复状态标志
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                std::cerr << "请输入正整数:";
            }
            minHeap.insert(newNumber);
        }

        while(minHeap.getSize() > 1){
            auto first = minHeap.popMin();
            auto second = minHeap.popMin();
            auto result = first + second;
            total += result;
            minHeap.insert(result);
        }

        std::cout << total << std::endl;

        int control;
        std::cout << "是否继续, 是则输入1, 停止的话输入0: ";
        while (!(std::cin >> control) || (control != 0 && control != 1)) {
            std::cin.clear();// 恢复状态标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
            std::cerr << "请输入1或0:";
        }
        if(control == 0){
            break;
        }
    }
    return 0;
}