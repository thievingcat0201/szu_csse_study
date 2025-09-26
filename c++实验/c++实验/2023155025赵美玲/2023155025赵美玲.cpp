#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

class student
{
private:
    string id;
    string name;
    string birth;
    double score;

public:
    void set(string id, string name, string birth, double score)
    {
        id = id;
        name = name;
        birth = birth;
        score = score;
    }
    string getid()
    {
        return id;
    }
    string getname()
    {
        return name;
    }
    string getbirth()
    {
        return birth;
    }
    double getscore()
    {
        return score;
    }

};


int main()
{
    int t;
    cin >> t;
    student* obj = new student[t];
    int num = 0;
    while (t--)
    {
        string id;
        string name;
        string birth;
        int score;
        cin >> id >> name >> birth >> score;
        for (int j = 0; j < num; j++)
        {
            if (id == obj[j].getid())
            {
                obj[j].set(id, name, birth, score);
            }
            else
            {
                obj[num].set(id, name, birth, score);
                num++;
            }
        }
    }
    for (int i = 1; i < t; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (obj[i].getid() < obj[j].getid())
            {
                student temp;
                temp = obj[i];
                obj[i] = obj[j];
                obj[j] = temp;
            }
        }

    }
    for (int i = 0; i < t; i++)
    {
        cout << "id: " << obj[i].getid() << " name: " << obj[i].getname() << " birthday: " << obj[i].getbirth() << " score: " << obj[i].getscore() << endl;

    }
    cout << endl;

    delete[]obj;

    return 0;
}
