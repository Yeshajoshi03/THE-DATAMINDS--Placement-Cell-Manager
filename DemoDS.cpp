#include <bits/stdc++.h>
using namespace std;


struct table
{
    int branch;
    Student *ptr;
};

class Student
{
    private:
    int id;
    string sName;
    
    public:
    void setStudent(int i, string n);

};

class Round
{
    private:
    // string rName;
    int numS;

    Student * student;

    public:
    Round(){}
    Round(int sz): numS(sz)
    {
        student = new Student[numS];
    }

    void allocateStuMemory(int sz)
    {
        numS = sz;
        student = new Student[numS];
    }
};

class Company
{
    private:
    string cName;
    int salery;

    Round R1;
    Round R2;
    Round R3;
    Round HR;
    Round Final;

    public:
    void setComp(int r, int i, string n);
};

class Year
{
    private:
    int yr;
    Company * company;

    public:
    void allocateCompMemory(int noC)
    {
        company = new Company[noC];
    }

    void setYear(int c, int r, int i, string n);
};

class DataBase
{
    private:
    Year *year;

    public:
    DataBase(){}
    DataBase(int y)
    {
        year = new Year[y];
    }
    void allocateYearMemory(int y)
    {
        year = new Year[y];
    }

    void setData(int y, int c, int r, int i, string n){
        year[y].setYear(c,r,i,n);
    }
};


