#include "QandA.h"
void InitQandA(vector<QandA>& qaa)
{
    ifstream file1("Question.txt");
    ifstream file2("Answer.txt");
    QandA qa;
    string temp;
    while (getline(file1, qa.question))
    {
        getline(file2, qa.answer);
        qaa.push_back(qa);
    }
    file1.close();
    file2.close();
}
void Exam(vector<QandA>& qa)
{
    string ans;
    int sum = 0;
    for (int i = 0; i < qa.size(); i++)
    {
        cout << qa[i].question << endl;
        cin >> ans;
        if (qa[i].answer == ans)
        {
            cout << "����ˣ���10��" << endl;
            sum += 10;
        }
        else
        {
            cout << "����ˣ����÷�" << endl;
        }
    };
    cout << "���Խ������÷�";
    cout << sum << endl;
}