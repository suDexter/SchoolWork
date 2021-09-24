#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace::std;
class QandA
{
    public:
        string question;//问题
        string answer;//答案
};
void InitQandA(vector<QandA>& qa);//初始化考题答案
void Exam(vector<QandA>& qa);//考试
