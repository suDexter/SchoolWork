#include "student.h"
#include "QandA.h"
int main()
{
    string num;
    vector<Student>ALLSTUDENTS;
    vector<QandA>ALLQA;
    InitStudent(ALLSTUDENTS);
    InitQandA(ALLQA);
    cout << "//////////////����ϵͳ////////////" << endl;
    cout << "������ѧ��" << endl;
    cin >> num;
    Register(ALLSTUDENTS, num);
    cout << "��ʼ���ԣ�" << endl;
    Exam(ALLQA);
}