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
        string question;//����
        string answer;//��
};
void InitQandA(vector<QandA>& qa);//��ʼ�������
void Exam(vector<QandA>& qa);//����
