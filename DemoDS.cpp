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

    void set_yr(int y){
        yr=y;
    }
};

class DataBase
{
    private:
    Year *year;
    int yr1;

    public:
    DataBase(){
        year = NULL;
    }
    DataBase(int y)
    {
        year = new Year[y];
        yr1 = y;
    }
    void allocateYearMemory(int y)
    {
        year = new Year[y];
        yr1 = y;
    }

    void setData(int y, int c, int r, int i, string n){
        year[y%yr1].setYear(c,r,i,n);
    }

    Year * hashRtYear(int y)
    {
        return &year[y%yr1];
    }
};


    

void set_data(){

    ifstream my_yr_file;
    my_yr_file.open("yearFile.txt");
    int No_yr = 0;

    while(my_yr_file.peek() != EOF)//Gets the number of year
    {   
        string year;
        getline(my_yr_file, year, '\n');
        No_yr++;
    }

    DataBase All_std_data(No_yr); 

    my_yr_file.seekg(0 , my_yr_file.beg);
    
    for(int i=0 ; i<No_yr ; i++)
    {
        ifstream my_comp_file;

        string yearF;
        getline(my_yr_file, yearF, '\n');

        int int_year=0;//string year to int year
        while(yearF[i]<4){
            int temp;
            temp=yearF[i]* pow(10,3-i);
            int_year= int_year+temp;
        }

        Year *yptr = All_std_data.hashRtYear(int_year);

        yptr->set_yr(int_year);

        my_comp_file.open(yearF);

        int No_c;

        while(my_comp_file.peek() != EOF)//Gets the number of company*5
        {   
            string c;
            getline(my_comp_file, c, '\n');
            No_c++;
        }

        No_c = No_c/5;//Gets the number of company

        yptr->allocateCompMemory(No_c);
        
    }
}
