//Third Question
//TODO:项目功能要求
//迷宫问题的求解过程可以采用回溯法即在一定的约束条件下试探地搜索前进，
//若前进中受阻，则及时回头纠正错误另择通路继续搜索的方法。
//从入口出发，按某一方向向前探索，若能走通，即某处可达，则到达新点，否则探索下一个方向；
//若所有的方向均没有通路，则沿原路返回前一点，换下一个方向再继续试探，直到所有可能的道路都探索到，或找到一条通路，或无路可走又返回入口点。
//在求解过程中，为了保证在达到某一个点后不能向前继续行走时，能正确返回前一个以便从下一个方向向前试探，
//则需要在试探过程中保存所能够达到的每个点的下标以及该点前进的方向，当找到出口时试探过程就结束了。

#include <iostream>
#include <limits>
#include "Stack.h"

//存储迷宫
short** maze;
//防止重复遍历
bool** visited;
int startRow, startCol, endRow, endCol;
int rowSize, colSize;
enum Direction{left, up, right, down};
class StackItem{
public:
    int row;
    int col;
    Direction dir;
    StackItem():row(-1), col(-1), dir(Direction::left){}
    StackItem(int newRow, int newCol, Direction newDir):row(newRow), col(newCol), dir(newDir){}
    StackItem move(Direction dir){
        switch(dir){
            case Direction::left:
                return StackItem(row, col - 1, Direction::left);
            case Direction::up:
                return StackItem(row - 1, col, Direction::left);
            case Direction::right:
                return StackItem(row, col + 1, Direction::left);
            case Direction::down:
                return StackItem(row + 1, col, Direction::left);
        }
    }
};

std::ostream& operator<< (std::ostream& out, StackItem& target){
    out << "(" << target.row << "," << target.col << ")";
    return out;
}

class MazeStack: public Stack<StackItem>{
public:
    void mazeListAll(ListNode<StackItem>* startPoint){
        if(startPoint->getNext() != nullptr){
            mazeListAll(startPoint->getNext());
        }
        std::cout << startPoint->getData();
        std::cout << "--->";
        if(startPoint == gethead()->getNext()){
            std::cout << "(" << endRow << "," << endCol << ")" << std::endl;
        }
    }
    bool isInStack(int x, int y){
        if(getSize()){
            auto temp = gethead()->getNext();
            while(temp){
                if(temp->getData().row == x && temp->getData().col == y){
                    return true;
                }
                else{
                    temp = temp->getNext();
                }
            }
            return false;
        }
        else{
            return false;
        }
    }
};

bool isValidPoint(StackItem target){
    if(target.row >= rowSize || target.row < 0 || target.col >= colSize || target.col < 0
        || maze[target.row][target.col] || visited[target.row][target.col]){
        return false;
    }
    else{
        return true;
    }

}

bool isGoal(StackItem target){
    if(target.row == endRow && target.col == endCol){
        return true;
    }
    else{
        return false;
    }
}

void listMaze(bool result, MazeStack* stack){
    if(startCol == endCol && endRow == startRow){
        std::cout << "您构造的迷宫，起点与终点重合:" << std::endl;
    }
    if(result){
        std::cout << "迷宫路径用x来表示，#为墙, *为起点, @为终点" << std::endl;
    }
    else{
        std::cout << "迷宫中#为墙, *为起点，@为终点" << std::endl;
    }
    std::cout << "   " << "\t";
    for(auto col = 0; col < colSize; col++){
        std::cout << col << "列" << "\t";
    }
    for(auto row = 0; row < rowSize; row++){
        std::cout << std::endl;
        std::cout << row << "行" << "\t";
        for(auto col = 0; col < colSize; col++){
            if(row == startRow && col == startCol){
                std::cout << "*" << "\t";
            }
            else if (row == endRow && col == endCol){
                std::cout << "@" << "\t";
            }
            else if (result && stack->isInStack(row, col)){
                std::cout << "x" << "\t";
            }
            else{
                if(maze[row][col]){
                    std::cout << "#" << "\t";
                }
                else{
                    std::cout << "0" << "\t";
                }
            }
        }
    }
}

void constructMaze(){
    std::cout << "请分别输入迷宫的行数与列数(用空格进行分割)" << std::endl;
    //TODO:测试输完一个按下回车
    while(!(std::cin >> rowSize >> colSize) || rowSize <=0 || colSize <=0 ){
        std::cin.clear();// 恢复状态标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
        std::cerr << "请输入正整数, 重新输入:" ;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //创造迷宫存储空间
    maze = new short*[rowSize];
    for(auto i = 0; i < rowSize; i++){
        maze[i] = new short[colSize];
    }
    visited = new bool*[rowSize];
    for(auto i = 0; i < rowSize; i++){
        visited[i] = new bool[colSize];
    }
    std::cout << "下面请输入迷宫的样式(0表示通路，1表示阻隔，按照矩阵方式输入即可):" << std::endl;
    for(auto row = 0; row < rowSize; row++){
        for (auto col = 0; col < colSize; col++){
            short mazePiece;
            while(!(std::cin >> mazePiece) || (mazePiece != 1 && mazePiece != 0)){
                std::cin.clear();// 恢复状态标志
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                std::cerr << "位置坐标为(" << row << "," << col
                    << ")的迷宫点输入的数据不符合要求，请从该位置开始重新输入:" << std::endl;
            }
            maze[row][col] = mazePiece;
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "下面输入起点的坐标(以空格隔开):" << std::endl;
    while(!(std::cin >> startRow >> startCol) || startRow < 0 || startRow >= rowSize ||
        startCol < 0 || startCol >= colSize || maze[startRow][startCol]){
        std::cin.clear();// 恢复状态标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
        std::cerr << "起点坐标超出所输入迷宫范围 或者 类型不匹配 或者 起点设在了墙上，重新输入:" << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "下面输入终点的坐标(以空格隔开):" << std::endl;
    while(!(std::cin >> endRow >> endCol) || endRow < 0 || endRow >= rowSize ||
        endCol < 0 || endCol >= colSize || maze[endRow][endCol]){
        std::cin.clear();// 恢复状态标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
        std::cerr << "终点坐标超出所输入迷宫范围 或者 类型不匹配 或者 终点设在了墙上，重新输入:" << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "迷宫构造完成, 您构造的迷宫如下:" << std::endl;
    listMaze(false, nullptr);
    std::cout << std::endl;
}

void solveMaze(){
    //初始化
    for(auto i = 0; i < rowSize; i++){
        for(auto j = 0; j < colSize; j++){
            visited[i][j] = false;
        }
    }
    //记录路径
    MazeStack stack = MazeStack();
    StackItem temp = StackItem(startRow, startCol, Direction::left);
    stack.push(temp);
    visited[startRow][startCol] = true;
    if(startRow == endRow && startCol == endCol){
        listMaze(true, &stack);
        std::cout << std::endl;
        std::cout << "迷宫路径:" << std::endl;
        stack.mazeListAll(stack.gethead()->getNext());
    }
    while(!stack.isEmpty()){
        temp = stack.peek();
        stack.pop();
        while(temp.dir <= Direction::down){
            auto newTemp = temp.move(temp.dir);
            if(isGoal(newTemp)){
                stack.push(temp);
                visited[newTemp.row][newTemp.col] = true;
                listMaze(true, &stack);
                std::cout << "迷宫路径:" << std::endl;
                stack.mazeListAll(stack.gethead()->getNext());
                return;
            }
            else if(isValidPoint(newTemp)){
                stack.push(temp);
                visited[newTemp.row][newTemp.col] = true;
                temp = newTemp;
            }
            else{
                if(temp.dir == Direction::down){
                    break;
                }
                else{
                    temp.dir = Direction(temp.dir + 1);
                }
            }
        }
    }
    std::cout << "此迷宫无解" << std::endl;
}

void solveOnce(){
    constructMaze();
    solveMaze();
}

int main(){
    std::cout << "欢迎来到勇闯迷宫游戏" << std::endl;
    int control;
    while(true){
        std::cout << "输入1以继续游戏，输入0退出" << std::endl;
        while (!(std::cin >> control) || ((control != 0) && (control != 1))){
            std::cin.clear();// 恢复状态标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
            std::cerr << "请输入0或1:" ;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(control){
            solveOnce();
        }
        else{
            break;
        }
    }

    return 0;
}