//Fourth Question
//TODO:项目功能要求
//算数表达式有前缀表示法，中缀表示法和后缀表示法等形式。
//日常使用的算术表达式是采用中缀表示法，即二元运算符位于两个运算数中间。
//请设计程序将中缀表达式转换成为后缀表达式。

#include <limits>
#include <iostream>
#include <string>
#include <sstream>
#include "Stack.h"

bool isAllowed(const std::string& allowance, char op){
    return (allowance.find(op, 0) != std::string::npos);
}

int inStackPriority(char op){
    switch (op){
        case '#':
            return 0;
        case '(':
            return 1;
        case '*':
        case '/':
            return 5;
        case ')':
            return 6;
        case '+':
        case '-':
            return 3;
        default:
            return -1;
    }
}

int offStackPriority(char op){
    switch (op){
        case '#':
            return 0;
        case '(':
            return 6;
        case '*':
        case '/':
            return 4;
        case ')':
            return 1;
        case '+':
        case '-':
            return 2;
        default:
            return -1;
    }
}

void solveOnce(){
    bool point = false;
    bool failed = false;
    bool number = false;
    std::string result;
    std::string from;
    std::string allowedOps = "#(*/)+-";
    std::stringstream buffer;
    Stack<char> stack = Stack<char>();
    stack.push('#');
    std::cout << "请输入表达式:" << std::endl;
    getline(std::cin, from);
    from = from + "#";
    for(auto currentChar = from.begin(); currentChar < from.end(); currentChar++){
        if(isspace(*currentChar)){
            continue;
        }
        else if(!isdigit(*currentChar) && *currentChar != '.'){
            if(point){
                failed = true;
                break;
            }
            if(number){
                buffer << " ";
            }
            if(!number && (*currentChar == '+' || *currentChar == '-') && (currentChar + 1 != from.end() )
            && isdigit(*(currentChar + 1))){
                if(*currentChar != '+'){
                    buffer << *currentChar;
                }
            }
            else if(isAllowed(allowedOps, *currentChar)){
                auto stackTop = stack.peek();
                while(inStackPriority(stackTop) > offStackPriority(*currentChar)){
                    buffer << stackTop << " ";
                    stack.pop();
                    stackTop = stack.peek();
                }
                if(inStackPriority(stackTop) < offStackPriority(*currentChar)){
                    stack.push(*currentChar);
                }
                else{
                    stack.pop();
                }
            }
            else{
                failed = true;
                break;
            }
            number = false;
        }
        else if(*currentChar == '.'){
            if(number){
                buffer << ".";
                point = true;
            }
            else{
                failed = true;
                break;
            }
        }
        else{
            point = false;
            buffer << *currentChar;
            number = true;
        }
    }
    buffer << "\n";
    if(!failed && stack.getSize() == 0){
        std::cout << "后缀形式如下" << std::endl;
        getline(buffer, result);
        //去除前置多余空格
        result.erase(0,result.find_first_not_of(" "));
        std::cout << result << std::endl;
    }
    else{
        std::cout << "这个表达式并不是合法的表达式" << std::endl;
    }
}

int main(){

    std::cout << "表达式转换器:(中缀转后缀)" << std::endl;
    int control;
    while(true){
        std::cout << "输入1以继续，输入0以退出:";
        while (!(std::cin >> control) || ((control != 0) && (control != 1))){
            std::cin.clear();// 恢复状态标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
            std::cerr << "请输入0或1:" ;
        }
        getchar();
        if(control){
            solveOnce();
        }
        else{
            break;
        }
    }

    return 0;
}