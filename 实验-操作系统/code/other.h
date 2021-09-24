#include <string>
#include <iostream>
#include <vector>
using namespace::std;

class Student {
    public:
        string password;
        string userName;
        void show();
};
string studentnum[100];
string studentpassword[100];
string studentname[100];
void InitStudent();
void showMenu(); // 主页
bool log_in(vector<Student>& u);//登录
void fetchStu(vector<Student>& a);  //考生

