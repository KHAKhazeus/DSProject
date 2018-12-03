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
#include "ListNode.h"
#include "List.h"
#include <string>

class Examinee{
private:
    int _id;
    std::string _name;
    std::string _gender;
    int _age;
    std::string _category;

};

int main() {

    List<int> test;
    test.insertBack(1);
    test.insertBack(2);
    test.insertBack(3);
    test.makeEmpty();
    std::cout << test.getSize() << std::endl;
    return 0;
}