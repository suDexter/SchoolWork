#include "other.h"
#include <iostream>
#include <vector>
#include <fstream>
void InitStudent()
{
    ifstream infile;
    char data[100];
    infile.open("QandA.txt");
    cout << data << endl;
    
    getchar();
    infile.close();
}
int main()
{
    int a;
    //InitStudent();
    cout << "5+6565" << endl;
    cin >> a;
    getchar();
    
	
    return 0;
}
/*
bool Register(vector<Student> &u) {
    string name, password;
    cout << "请输入考生姓名" << endl;
    cin >> name;
    int a = isUserExist(name, u);
    if (a == -1) {
        cout << "考生不存在，登录失败" << endl;
        return false;
    }
    else
    {
        cout << "请输入密码" << endl;
        cin >> password;
        if (u[a].judge(password)) {
            cout << "登录成功" << endl;
            return true;
        }
        else
        {
            cout << "密码错误，登录失败" << endl;
            return false;
        }
    }
}*/
