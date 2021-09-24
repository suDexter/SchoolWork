#include "student.h"
#include "QandA.h"
int main()
{
    string num;
    vector<Student>ALLSTUDENTS;
    vector<QandA>ALLQA;
    InitStudent(ALLSTUDENTS);
    InitQandA(ALLQA);
    cout << "//////////////考试系统////////////" << endl;
    cout << "请输入学号" << endl;
    cin >> num;
    Register(ALLSTUDENTS, num);
    cout << "开始考试！" << endl;
    Exam(ALLQA);
}