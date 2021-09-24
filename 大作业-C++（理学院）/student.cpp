#include "student.h"
void InitStudent(vector<Student>&s)
{
    ifstream file1("StudentsNum.txt");
    ifstream file2("StudentsName.txt");
    Student stu;
    string temp;
    while (getline(file1, stu.studentnum))
    {
        getline(file2, stu.studentname);
        s.push_back(stu);
    }
    file1.close();
    file2.close();
}
void Register(vector<Student>&s, string num)
{
    int flag = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i].studentnum == num)
        {
            cout << "登录成功" + s[i].studentname << endl;
            flag = 1;
        }    
    };
    if (flag == 0)
    {
        cout << "无此考生！" << endl;
        exit(0);
    }
}