/* First Question: 考试报名系统
 *
 * TODO:项目功能要求：
 * 完成对考生信息的建立，查找，插入，修改，删除等功能。
 * 考生信息包括准考证号，姓名，性别，年龄和报考类别等信息。
 * 项目在设计时应首先确定系统的数据结构，定义类的成员变量和成员函数；然后实现各成员函数以完成对数据操作的相应功能；
 * 最后完成主函数以验证各个成员函数的功能并得到运行结果。（建议采用链表实现）
 */

#include <vector>
#include <iostream>
#include <limits>
#include <string>
#include "ListNode.h"
#include "List.h"

class Examinee{
public:

    Examinee(int id, std::string name, std::string gender, int age, std::string category):
        _id(id), _name(name), _gender(gender), _age(age), _category(category){};
    Examinee():_id(0), _name("0"), _gender("0"), _age(0), _category("0"){};
    Examinee(const Examinee& right):_id(right.getId()), _name(right.getName()), _gender(right.getGender())
        , _age(right.getAge()), _category(right.getCategory()){};
    const int getId() const { return _id; }
    const std::string getName() const { return _name; }
    const std::string getGender() const { return _gender; }
    const int getAge() const { return _age; }
    const std::string getCategory() const { return _category; }
    Examinee& setId(int id){ _id = id; return *this; }
    Examinee& setName(std::string name){ _name = name; return *this; }
    Examinee& setGender(std::string gender){ _gender = gender; return *this; }
    Examinee& setAge(int age){ _age = age; return *this; }
    Examinee& setCategory(std::string category){ _category = category; return *this;}

    Examinee& operator=(Examinee const& right){
        setId(right.getId()).setName(right.getName()).setGender(right.getGender()).setAge(right.getAge())
        .setCategory(right.getCategory());
        return *this;
    }

    bool operator== (const Examinee& right) const {
        return getId() == right.getId() && getName() == right.getName() && getGender() == right.getGender() &&
        getAge() == right.getAge() && getCategory() == right.getCategory();
    }

private:
    int _id;
    std::string _name;
    std::string _gender;
    int _age;
    std::string _category;
};

std::ostream & operator << (std::ostream& outputStream, Examinee & examinee){
    outputStream << examinee.getId() << "\t\t" << examinee.getName() << "\t\t" << examinee.getGender() << "\t\t"
        << examinee.getAge() << "\t\t" << examinee.getCategory();
    return outputStream;
}

class ExamineeList : public Stack<Examinee>{
public:

    static Examinee defaultNull;

    bool deleteNodeById(int id){
        bool result = false;
        auto temp = gethead();
        for(auto i = 1; i <= getSize(); i++){
            temp = temp->getNext();
            if(temp->getData().getId() == id){
                result = deleteNodeByPos(i);
                break;
            }
        }
        return result;
    }

    Examinee& searchNodeById(int id){
        Examinee* result = nullptr;
        auto temp = gethead();
        for(auto i = 1; i <= getSize(); i++){
            temp = temp->getNext();
            if(temp->getData().getId() == id){
                result = &(temp->getData());
                break;
            }
        }
        if(result == nullptr){
            return ExamineeList::defaultNull;
        }
        else{
            return *result;
        }
    };

    void listAll(){
        std::cout << std::endl;
        std::cout << "考号" << "\t\t" << "姓名" << "\t\t" << "性别" << "\t\t" << "年龄" << "\t\t" << "报考类别"
            << std::endl;
        auto temp = gethead();
        for(auto i = 1; i <= getSize(); i++){
            temp = temp->getNext();
            Examinee data = temp->getData();
            std::cout << data << std::endl;
        }
        std::cout << std::endl;
    }
};

Examinee ExamineeList::defaultNull = Examinee(0, "0", "0", 0, "0");

void init(ExamineeList& systemList){
    std::cout << "首先请建立考生信息系统！" << std::endl << "请输入考生人数: ";
    int startNum = 0;
    while (!(std::cin >> startNum)){
        std::cin.clear();// 恢复状态标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
        std::cerr << "输入数据错误，请重新输入:" ;
    }
    std::cout << std::endl << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << std::endl;
    for(auto i = 1; i <= startNum; i++){
        int id;
        std::string name;
        std::string gender;
        int age;
        std::string category;
        while(!(std::cin >> id >> name >> gender >> age >> category) || std::cin.peek() != '\n'){
            std::cin.clear();// 恢复状态标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
            std::cerr << "考生信息类型不匹配，请重新输入:";
        }
        Examinee insertExaminee = Examinee(id, name, gender, age, category);
        systemList.insertBack(insertExaminee);
    }
    std::cout << std::endl;
}


int main() {

    ExamineeList systemList;
    init(systemList);
    std::cout << "考生信息系统初始化成功:";
    systemList.listAll();

    bool firstTime = true;
    int operation;

    while(true){
        if(firstTime){
            std::cout << "操作指导（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << std::endl;
            std::cout << std::endl;
            firstTime = false;
        }
        std::cout << "请选择您要进行的操作:";
        while (!(std::cin >> operation))
        {
            std::cin.clear();// 恢复状态标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
            std::cerr << "请输入0 - 5的操作数，请重新输入:" ;
        }
        switch(operation){
            case 0:
                return 0;

            case 1:
                int pos;
                std::cout << "请输入你要插入的考生的位置:（输入-1为插入至最后）";
                std::cin >> pos;
                if(pos > 0 && pos <= systemList.getSize() + 1){
                    std::cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别:" << std::endl;
                    int id, age;
                    std::string name, gender, category;
                    while(!(std::cin >> id >> name >> gender >> age >> category)){
                        std::cin.clear();// 恢复状态标志
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                        std::cerr << "考生信息类型不匹配，请重新输入:";
                    }
                    Examinee newExaminee = Examinee(id, name, gender, age, category);
                    if(systemList.insert(pos, newExaminee)){
                        std::cout << "考生信息系统更改完毕:";
                        systemList.listAll();
                    }
                    else{
                        std::cerr << "系统出错,未能插入信息" << std::endl;
                    }
                }
                else if(pos == -1){
                    std::cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别:" << std::endl;
                    int id, age;
                    std::string name, gender, category;
                    while(!(std::cin >> id >> name >> gender >> age >> category)){
                        std::cin.clear();// 恢复状态标志
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                        std::cerr << "考生信息类型不匹配，请重新输入:";
                    }
                    Examinee newExaminee = Examinee(id, name, gender, age, category);
                    if(systemList.insertBack(newExaminee)){
                        std::cout << "考生信息系统更改完毕:";
                        systemList.listAll();
                    }
                    else{
                        std::cerr << "系统出错,未能插入信息" << std::endl;
                    }
                }
                else {
                    std::cerr << "插入位置越界，请再尝试一次" << std::endl;
                }
                break;

            case 2: {
                std::cout << "请输入要删除的考生的考号:";
                int id;
                while (!(std::cin >> id)) {
                    std::cin.clear();// 恢复状态标志
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                    std::cerr << "输入类型与考号数据类型不匹配，请重新输入:";
                }
                auto& result = systemList.searchNodeById(id);
                if(result == ExamineeList::defaultNull){
                    std::cerr << "无此考号的考生" << std::endl;
                    std::cout << "重新输出系统目前所有考生";
                    systemList.listAll();
                }
                else{
                    std::cout << "你要删除的考生信息是:" << result << std::endl;
                    auto haveDeleted = systemList.deleteNodeById(id);
                    if(haveDeleted){
                        std::cout << "删除成功：" << std::endl;
                        std::cout << "系统已更新";
                        systemList.listAll();
                    }
                    else{
                        std::cerr << "系统出错, 未能执行删除指令" << std::endl;
                    }
                }
                break;
            }

            case 3: {
                std::cout << "请输入要查找的考生的考号:";
                int id;
                while (!(std::cin >> id)) {
                    std::cin.clear();// 恢复状态标志
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                    std::cerr << "输入类型与考号数据类型不匹配，请重新输入:";
                }
                auto& result = systemList.searchNodeById(id);
                if (result == ExamineeList::defaultNull){
                    std::cerr << "无此考号的考生" << std::endl;
                    std::cout << "重新输出系统目前所有考生:";
                    systemList.listAll();
                }
                else{
                    std::cout << "查找成功, 该考生的所有信息为:" << std::endl;
                    std::cout << "考号" << "\t\t" << "姓名" << "\t\t" << "性别" << "\t\t" << "年龄" << "\t\t" << "报考类别"
                              << std::endl;
                    std::cout << result << std::endl;
                }
                break;
            }

            case 4:{
                std::cout << "请输入要修改的考生的考号:";
                int id;
                while (!(std::cin >> id)) {
                    std::cin.clear();// 恢复状态标志
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                    std::cerr << "输入类型与考号数据类型不匹配，请重新输入:";
                }
                auto& result = systemList.searchNodeById(id);
                if(result == ExamineeList::defaultNull){
                    std::cerr << "无此考生的考生" << std::endl;
                    std::cout << "重新输出系统目前所有考生:";
                    systemList.listAll();
                }
                else{
                    std::cout << "此考生现在的信息为:" << std::endl;
                    std::cout << "考号" << "\t\t" << "姓名" << "\t\t" << "性别" << "\t\t" << "年龄" << "\t\t" << "报考类别"
                              << std::endl;
                    std::cout << result << std::endl;
                    std::cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别:" << std::endl;
                    int newId, age;
                    std::string name, gender, category;
                    while(!(std::cin >> newId >> name >> gender >> age >> category)){
                        std::cin.clear();// 恢复状态标志
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 略过缓存
                        std::cerr << "考生信息类型不匹配，请重新输入:";
                    }
                    result.setId(newId).setAge(age).setName(name).setGender(gender).setCategory(category);
                    std::cout << "系统考生信息更新完毕:";
                    systemList.listAll();
                }
                break;
            }

            case 5:{
                std::cout << "系统所有考生信息如下:";
                systemList.listAll();
                break;
            }
            default:
                std::cerr << "未知操作，请输入0-5之间的正整数" << std::endl;
        }

    }
}