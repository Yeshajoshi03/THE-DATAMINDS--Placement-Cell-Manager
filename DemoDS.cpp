#include <bits/stdc++.h>
using namespace std;

class DataBase;

int random_salary_genrator()
{
    srand(time(NULL));

    int num = rand() % 90;

    if (num >= 5)
    {
        return num * 100000;
    }
    else
    {
        return random_salary_genrator();
    }
}

class Student
{
private:
    int id;
    string sName;
    string intDate;
    string start_time;
    string end_time;
    string email;
    string program;
    string contact_no;
    string Whatsapp_no;
    string alt_no;
    string skypeID;

public:
    void setStudent(string n, string date, string st, string et, int i, string mail, string prog, string cont, string whats, string altNo, string skypeid)
    {
        id = i;
        sName = n;
        intDate = date;
        start_time = st;
        end_time = et;
        email = mail;
        program = prog;
        contact_no = cont;
        Whatsapp_no = whats;
        alt_no = altNo;
        skypeID = skypeid;
    }
    int getID()
    {
        return id;
    }
    friend class Round;
    friend int students_in_comp_branch_yearly(DataBase d, int y, string company_name, string branch);
    friend void display(vector<Student *> v);
    friend int students_in_company(DataBase d, string company_name);
    friend void Student_Complete_Information(string ID, DataBase D);



};

class Round
{
private:
    int numS;
    Student *student;

public:
    Round() {}
    Round(int sz) : numS(sz)
    {
        student = new Student[numS];
    }

    void allocateStuMemory(int sz)
    {
        numS = sz;
        student = new Student[numS];
    }
    Student *hashStudentId(int id)
    {
        int i = 0;
        while (1)
        {
            int h;
            h = (id % numS + i) % numS; // double hashing
            if (student[h].sName.empty())
            {
                return &student[h];
                break;
            }
            else
            {
                i++;
            }
        }
    }
    Student *accesshashStdId(int id)
    {
        int i = 0;
        for (i = 0; i < numS; i++)
        {
            int h;
            h = (id % numS + i) % numS; // double hashing
            if (student[h].id == id)
            {
                return &student[h];
                break;
            }
            else
            {
                i++;
            }
        }
    }

    friend int students_in_company(DataBase d, string company_name);
    friend int students_in_comp_year(DataBase d, int y, string company_name);
    friend int students_in_comp_branch_yearly(DataBase d, int y, string company_name, string branch);
    friend int students_in_company(DataBase d, string company_name);
    friend void Student_Complete_Information(string ID, DataBase D);



    friend int students_in_comp_branch_yearly(DataBase d, int y, string company_name, int branch_code);
    friend void student_company_application(DataBase s, int year, string company);
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
    Round *rptr[5];

    vector<Student *> BIct, MDes, MIct, MScIt, MScDS, BIctCs, BMnc, BEvd;

public:
    Company()
    {
        rptr[0] = &R1;
        rptr[1] = &R2;
        rptr[2] = &R3;
        rptr[3] = &HR;
        rptr[4] = &Final;
    }
    void set_comp_name(string s)
    {
        cName = s;
    }
    void separate_branchwise(string str, Student *s)
    {
        // cout << "In function" << endl;
        if (str[4] == '0')
        { // Bachelors
            if (str[5] == '1' && str[6] != '4')
            {
                BIct.push_back(s);
                // cout<<"Size: "<<BIct.size();
            }
            else if (str[5] == '1' && str[6] == '4')
                BIctCs.push_back(s);
            else if (str[5] == '3')
                BMnc.push_back(s);
            else if (str[5] == '4')
                BEvd.push_back(s);
        }
        else
        { // Masters
            if (str[5] == '2')
                MScIt.push_back(s);
            else if (str[5] == '4')
                MDes.push_back(s);
            else if (str[5] == '8')
                MScDS.push_back(s);
            else
                MIct.push_back(s);
        }
    }
    friend int students_in_comp_branch_yearly(DataBase d, int y, string company_name, string branch);
    friend class Year;
    friend void set_data(string year_file, DataBase *);
    friend int students_in_company(DataBase d, string company_name);
    friend int students_in_comp_year(DataBase d, int y, string company_name);
    friend int students_in_comp_branch_yearly(DataBase d, int y, string company_name, int branch_code);
    friend void display(vector<Student *> v);
    friend int students_in_comp_branch_yearly(DataBase d, int y, string company_name, string branch);
    friend int students_in_company(DataBase d, string company_name);
    friend void Student_Complete_Information(string ID, DataBase D);
    friend void students_in_comp_program_yearly(DataBase d, int y, string company_name);



    friend int students_branch_yearly(DataBase d, int y, int branch_code);
    friend void student_company_application(DataBase s, int year, string company);
};

class Year
{
private:
    int yr;
    int No_of_Comp;
    Company *company;

    int highest_package, lowest_package;

    vector<vector<Student *> *> Ybict;

public:
    Year() : highest_package(0), lowest_package(9000000) {}

    friend int highest_salery_year(DataBase *d, int y);
    friend int lowest_salery_year(DataBase *d, int y);
    void allocateCompMemory(int noC)
    {
        company = new Company[noC];
        No_of_Comp = noC;

        for (int i = 0; i < noC; i++)
        {
            Ybict.push_back(&company[i].BIct);
        }
    }
    Company *comptr()
    {
        return this->company;
    }
    void setYear(int c, int r, int i, string n);
    friend void set_data(string year_file, DataBase *);
    friend int students_in_company(DataBase d, string company_name);
    void set_yr(int y)
    {
        yr = y;
    }
    Company *hashCompName(string comp_name)
    {
        int comp_code = 0; // company name to company code for hashing
        for (int j = 0; j < 3; j++)
        {
            int temp;
            temp = comp_name[j] * pow(10, 4 - (2 * j));
            comp_code = comp_code + temp;
        }
        int i = 0;
        while (1)
        {
            int h;

            h = (comp_code % No_of_Comp + i) % No_of_Comp; // double hashing
            if (company[h].cName.empty())
            {
                company[h].cName = comp_name;
                return &company[h];
            }
            else
            {
                i++;
            }
        }
    }
    friend void Student_Complete_Information(string ID, DataBase D);

    Company *accessHashCompName(string company_name)
    {
        int comp_code = 0; // company name to company code given by user
        for (int j = 0; j < 3; j++)
        {
            int temp;
            temp = company_name[j] * pow(10, 4 - (2 * j));
            comp_code = comp_code + temp;
        }
        int i = 0;
        for (i = 0; i < No_of_Comp; i++)
        {

            int h;
            h = (comp_code % No_of_Comp + i) % No_of_Comp; // double hashing

            int comp_code1 = 0; // company name to company code given by user
            for (int j = 0; j < 3; j++)
            {
                int temp;
                temp = company[h].cName[j] * pow(10, 4 - (2 * j));
                comp_code1 = comp_code1 + temp;
            }
            if (comp_code == comp_code1)
            {
                return &company[h];
                break;
            }
            else
            {
                i++;
            }
        }
        return NULL;
    }
    friend int students_branch_yearly(DataBase d, int y, int branch_code);
};

class DataBase
{
private:
    Year *year;
    int No_yr;

public:
    DataBase()
    {
        year = NULL;
    }
    DataBase(int y)
    {
        year = new Year[y];
        No_yr = y;
    }
    friend void Student_Complete_Information(string ID, DataBase D);

    void allocateYearMemory(int y)
    {
        year = new Year[y];
        No_yr = y;
    }

    int no_of_years()
    {
        return No_yr;
    }
    void setData(int y, int c, int r, int i, string n)
    {
        year[y % No_yr].setYear(c, r, i, n);
    }

    Year *hashRtYear(int y) // ASSUMPTION: Continuous year data
    {
        return &year[y % No_yr];
    }
    friend int students_in_company(DataBase d, string company_name);
    friend void Student_Complete_Information(string ID, DataBase D);

};

int highest_salery_year(DataBase *d, int y)
{
    return d->hashRtYear(y)->highest_package;
}

int lowest_salery_year(DataBase *d, int y)
{
    return d->hashRtYear(y)->lowest_package;
}

void startdata(ifstream *f)
{
    string stemp;
    getline(*f, stemp, ',');
    while (stemp != "1")
    { // pointing to data in csv file
        string t;
        getline(*f, t, '\n');
        getline(*f, stemp, ',');
    }
}

int count(ifstream *f)
{ // pass by refernce
    int c = 0;
    while (f->peek() != EOF)
    {
        string str;
        getline(*f, str, '\n');
        c++;
    }
    return c;
}

// int MDes=0,MIct=0,MScIt=0, MScDS=0,BIct=0, BIctCs=0, BMnc=0, BEvd=0;//globally declared

void set_data(string year_file, DataBase *All_std_data)
{

    ifstream my_yr_file;
    my_yr_file.open(year_file);

    int No_yr;
    No_yr = count(&my_yr_file); // gets the number of year

    All_std_data->allocateYearMemory(No_yr);
    my_yr_file.close();
    my_yr_file.open(year_file);

    for (int i = 0; i < No_yr; i++)
    {
        ifstream my_comp_file;

        string yearF;
        getline(my_yr_file, yearF, '\n');

        int int_year = 0; // string year to int year
        for (int j = 0; j < 4; j++)
        { // first 4 chars from filename
            int temp;
            temp = (yearF[j] - '0') * pow(10, 3 - j);
            int_year = int_year + temp;
        }

        Year *yptr = All_std_data->hashRtYear(int_year);

        yptr->set_yr(int_year);

        my_comp_file.open(yearF);

        int No_c = count(&my_comp_file);
        No_c = No_c / 5; // Gets the number of company

        yptr->allocateCompMemory(No_c);

        my_comp_file.close();
        my_comp_file.open(yearF);

        for (int j = 0; j < No_c; j++)
        {
            string comp_name;
            getline(my_comp_file, comp_name, '\n'); // round1

            Company *cptr;
            cptr = yptr->hashCompName(comp_name); // points to individual company

            int sal = random_salary_genrator();
            cptr->salery = sal;

            if (sal > yptr->highest_package)
            {
                yptr->highest_package = sal;
            }
            else if (sal < yptr->lowest_package)
            {
                yptr->lowest_package = sal;
            }

            ifstream comp_round_file;
            comp_round_file.open(comp_name); // points to round1 file of a company

            startdata(&comp_round_file); // function to set pointer to start of data

            int No_std; // number of student in first round of a company
            No_std = count(&comp_round_file);

            cptr->rptr[0]->allocateStuMemory(No_std); // allocated student memory
            comp_round_file.close();
            comp_round_file.open(comp_name);

            startdata(&comp_round_file);

            int tempID1 = 0;
            string tempname1, tempdate1, tempstatus1, tempstr1, tempend1, tempid1, tempmail1, tempPro1, tempcont1, tempwhats1, tempalt1, tempskype1;

            getline(comp_round_file, tempname1, ',');
            getline(comp_round_file, tempdate1, ',');
            getline(comp_round_file, tempstatus1, ',');
            getline(comp_round_file, tempstr1, ',');
            getline(comp_round_file, tempend1, ',');
            getline(comp_round_file, tempid1, ',');
            getline(comp_round_file, tempmail1, ',');
            getline(comp_round_file, tempPro1, ',');
            getline(comp_round_file, tempcont1, ',');
            getline(comp_round_file, tempwhats1, ',');
            getline(comp_round_file, tempalt1, ',');
            getline(comp_round_file, tempskype1, '\n');

            // separate_branchwise(tempid);

            for (int j = 0; j < 9; j++) // string std_id to int std_id
            {
                int temp;
                temp = (tempid1[j] - '0') * pow(10, 8 - j);
                tempID1 = tempID1 + temp;
            }
            Student *sptr1 = cptr->rptr[0]->hashStudentId(tempID1);
            sptr1->setStudent(tempname1, tempdate1, tempstr1, tempend1, tempID1, tempmail1, tempPro1, tempcont1, tempwhats1, tempalt1, tempskype1);

            while (comp_round_file.peek() != EOF)
            {
                int tempID = 0;
                string tempsr, tempname, tempdate, tempstatus, tempstr, tempend, tempid, tempmail, tempPro, tempcont, tempwhats, tempalt, tempskype;
                getline(comp_round_file, tempsr, ',');
                getline(comp_round_file, tempname, ',');
                getline(comp_round_file, tempdate, ',');
                getline(comp_round_file, tempstatus, ',');
                getline(comp_round_file, tempstr, ',');
                getline(comp_round_file, tempend, ',');
                getline(comp_round_file, tempid, ',');
                getline(comp_round_file, tempmail, ',');
                getline(comp_round_file, tempPro, ',');
                getline(comp_round_file, tempcont, ',');
                getline(comp_round_file, tempwhats, ',');
                getline(comp_round_file, tempalt, ',');
                getline(comp_round_file, tempskype, '\n');

                for (int j = 0; j < 9; j++) // string std_id to int std_id
                {
                    int temp;
                    temp = (tempid[j] - '0') * pow(10, 8 - j);
                    tempID = tempID + temp;
                    temp = (tempid[j] - '0') * pow(10, 8 - j);
                    tempID = tempID + temp;
                }
                Student *sptr = cptr->rptr[0]->hashStudentId(tempID);
                sptr->setStudent(tempname, tempdate, tempstr, tempend, tempID, tempmail, tempPro, tempcont, tempwhats, tempalt, tempskype);
            }

            comp_round_file.close();

            for (int i = 1; i < 5; i++)
            {

                getline(my_comp_file, comp_name, '\n');

                comp_round_file.open(comp_name); // points to round i+1 file of a company

                startdata(&comp_round_file); // function to set pointer to start of data

                int No_std; // number of student in first round of a company
                No_std = count(&comp_round_file);

                cptr->rptr[i]->allocateStuMemory(No_std); // allocated student memory
                comp_round_file.close();
                comp_round_file.open(comp_name);

                startdata(&comp_round_file);

                tempID1 = 0;
                tempname1, tempdate1, tempstatus1, tempstr1, tempend1, tempid1, tempmail1, tempPro1, tempcont1, tempwhats1, tempalt1, tempskype1;

                getline(comp_round_file, tempname1, ',');
                getline(comp_round_file, tempdate1, ',');
                getline(comp_round_file, tempstatus1, ',');
                getline(comp_round_file, tempstr1, ',');
                getline(comp_round_file, tempend1, ',');
                getline(comp_round_file, tempid1, ',');
                getline(comp_round_file, tempmail1, ',');
                getline(comp_round_file, tempPro1, ',');
                getline(comp_round_file, tempcont1, ',');
                getline(comp_round_file, tempwhats1, ',');
                getline(comp_round_file, tempalt1, ',');
                getline(comp_round_file, tempskype1, '\n');

                for (int j = 0; j < 9; j++) // string std_id to int std_id
                {
                    int temp;
                    temp = (tempid1[j] - '0') * pow(10, 8 - j);
                    tempID1 = tempID1 + temp;
                }
                Student *sptr1 = cptr->rptr[i]->hashStudentId(tempID1);
                sptr1->setStudent(tempname1, tempdate1, tempstr1, tempend1, tempID1, tempmail1, tempPro1, tempcont1, tempwhats1, tempalt1, tempskype1);

                if (i == 4)
                {
                    cptr->separate_branchwise(tempid1, sptr1);
                    // cout<<sptr1->getID()<<endl;
                }

                while (comp_round_file.peek() != EOF)
                {
                    int tempID = 0;
                    string tempsr, tempname, tempdate, tempstatus, tempstr, tempend, tempid, tempmail, tempPro, tempcont, tempwhats, tempalt, tempskype;
                    getline(comp_round_file, tempsr, ',');
                    getline(comp_round_file, tempname, ',');
                    getline(comp_round_file, tempdate, ',');
                    getline(comp_round_file, tempstatus, ',');
                    getline(comp_round_file, tempstr, ',');
                    getline(comp_round_file, tempend, ',');
                    getline(comp_round_file, tempid, ',');
                    getline(comp_round_file, tempmail, ',');
                    getline(comp_round_file, tempPro, ',');
                    getline(comp_round_file, tempcont, ',');
                    getline(comp_round_file, tempwhats, ',');
                    getline(comp_round_file, tempalt, ',');
                    getline(comp_round_file, tempskype, '\n');

                    for (int j = 0; j < 9; j++) // string std_id to int std_id
                    {
                        int temp;
                        temp = (tempid[j] - '0') * pow(10, 8 - j);
                        tempID = tempID + temp;
                    }
                    Student *sptr = cptr->rptr[i]->hashStudentId(tempID);
                    sptr->setStudent(tempname, tempdate, tempstr, tempend, tempID, tempmail, tempPro, tempcont, tempwhats, tempalt, tempskype);
                    if (i == 4)
                    {
                        // cout << "gone" << endl;
                        cptr->separate_branchwise(tempid, sptr);
                        // cout<<sptr->getID()<<endl;
                    }
                }
                // cout<< All_std_data->hashRtYear(int_year)->accessHashCompName(comp_name)->rptr[i]->student[0].sName << endl;
                // cout << "hello"<<endl;
                comp_round_file.close();
            }
        }

            my_comp_file.close();
        }

        my_yr_file.close();
    }


    // void Student_Complete_Information(string ID, DataBase D)
    // {
    //     int year;
    //     if (ID.at(3) == 5)
    //     {
    //         year = 2019;
    //     }
    //     year += 4;
    //     int counter = 0, r = 0;
    //     for (int i = 0; i < D.hashRtYear(year)->No_of_Comp; i++)
    //     {
    //         for (int j = 0; j < 5; j++)
    //         {
    //             if (D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId((id) == NULL))
    //             {
    //                 continue;
    //             }
    //             else
    //             {
    //                 counter++;
    //                 r++;
    //                 if (counter == 1)
    //                 {
    //                     cout << "The name of student is : " << D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(id)->sName << endl;
    //                     cout << "The contact no. of student is : " << D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(id)->contact_no << endl;
    //                     cout << "The email ID of student is : " << D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(id)->email << endl;
    //                     cout << "The Whatsapp no. of stdudent is : " << D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(id)->Whatsapp_no << endl;
    //                     cout << "The skype ID of student is: " << D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(id)->skypeID << endl;
    //                     cout << "The program of student enrolled is : " << D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(id)->program << endl;
    //                 }
    //             }
    //         }
    //         if (r == 1)
    //         {
    //             cout << "The student appeared for Company " << i << " which is : " << D.hashRtYear(year)->company[i].cName << endl;
    //             cout << "He cleared till Round " << r << endl;
    //         }
    //         else if (r == 2)
    //         {
    //             cout << "The student appeared for Company " << i << " which is : " << D.hashRtYear(year)->company[i].cName << endl;
    //             cout << "He cleared till Round " << r << endl;
    //         }
    //         else if (r == 3)
    //         {
    //             cout << "The student appeared for Company " << i << " which is : " << D.hashRtYear(year)->company[i].cName << endl;
    //             cout << "He cleared till Round " << r << endl;
    //         }
    //         else if (r == 4)
    //         {
    //             cout << "The student appeared for Company " << i << " which is : " << D.hashRtYear(year)->company[i].cName << endl;
    //             cout << "He cleared till Round " << r << endl;
    //         }
    //         else if (r == 5)
    //         {
    //             cout << "The student appeared for Company " << i << " which is : " << D.hashRtYear(year)->company[i].cName << endl;
    //             cout << "He cleared till Round " << r << endl;
    //         }
    //         // D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(ID)==;
    //     }
    // }

    int students_in_comp_year(DataBase d, int y, string company_name);
int students_in_comp_branch_yearly(DataBase d, int y, string company_name, int branch_code);
void display(vector<Student *> v);
int students_branch_yearly(DataBase d, int y, int branch_code);
void students_in_comp_program_yearly(DataBase d, int y, string company_name);

    int main()
    {
        DataBase database;

    set_data("Year.txt", &database);
    int year;
    string company;
    // int x;
    // x=students_in_comp_year(database,2019,"Google");
    // cout<<x;
    // cout << database.no_of_years()<<endl;
    // // cout<<database.year[1].accessHashCompName("Bell")->Final.numS;
    // // cout<<"Hi";
    // cout << database.year[0].yr<<endl;
    // cout << database.year[1].yr<<endl;

    // string st="2019";
    // int int_year=0;//string year to int year
    //     for(int j=0; j<4; j++){//first 4 chars from filename
    //         int temp;
    //         temp=(st[j]-'0')* pow(10,3-j);
    //         int_year= int_year+temp;
    //     }
    // cout<<int_year<<endl;
    // database
    // int branch_code;
    // int Prog;
    // cout << "Enter 0 for B.Tech and 1 for M.Tech" << endl;
    // cin >> Prog;
    // cout << "Enter Branchcode for respective branches: " << endl
    //      << "Enter " << endl
    //      << "01 for B.Tech ICT" << endl
    //      << "0144 for B.Tech ICT-CS" << endl
    //      << "03 for B.Tech MNC" << endl
    //      << "04 for B.Tech EVD" << endl
    //      << "11 for M.Tech ICT" << endl;
    // cin >> branch_code;
    // cout << students_in_comp_branch_yearly(database, 2019, "Google", branch_code) << endl;
    // cout<< students_branch_yearly(database,2019,branch_code);

    
    // cout<<"Enter company and year to get number of students who applied to a specific company"<<endl;\
    // cin>>year;
    // cin>>company;
    //student_company_application(database, year, company);
    int year2;
    string company2;
    cout<<"Enter the name of the company and year to get the number of studets who are placed according to the program"<<endl;
    cin>>year2;
    cin>>company2;
    students_in_comp_program_yearly(database, year2, company2);
    return 0;

    
}
void student_company_application(DataBase s, int year, string company)
{
   if(s.hashRtYear(year)->accessHashCompName(company)==NULL)
   {
    cout<<"Company did not came for placement"<<endl;
   }
   else
   {
    int x= s.hashRtYear(year)->accessHashCompName(company)->R1.numS;
    cout<<x<<" Student applied for the company"<<endl;
   }
}
int students_in_company(DataBase d, string company_name)
{ // total number of students in a company till last year
    int num = 0;
    for (int i = 0; i < d.no_of_years(); i++)
    {
        if (d.year[i].accessHashCompName(company_name) == NULL)
        {
            continue;
        }
        else
        {
            num = num + d.year[i].accessHashCompName(company_name)->Final.numS;
        }
    }
    return num;
}

int students_in_comp_year(DataBase d, int y, string company_name)
{ // Number of students placed in a particular company in a given year
    if (d.hashRtYear(y)->accessHashCompName(company_name) != NULL)
    {
        return d.hashRtYear(y)->accessHashCompName(company_name)->Final.numS;
    }
    else
    {
        return 0;
    }
}
int students_in_comp_branch_yearly(DataBase d, int y, string company_name, int branch_code)
{
    if (d.hashRtYear(y)->accessHashCompName(company_name) == NULL)
    {
        return 0;
    }
    int result;
    switch (branch_code)
    {
    case (01):
        result = d.hashRtYear(y)->accessHashCompName(company_name)->BIct.size();
        display(d.hashRtYear(y)->accessHashCompName(company_name)->BIct);
        break;
    case (0144):
        result = d.hashRtYear(y)->accessHashCompName(company_name)->BIctCs.size();
        display(d.hashRtYear(y)->accessHashCompName(company_name)->BIctCs);
        break;
    case (03):
        result = d.hashRtYear(y)->accessHashCompName(company_name)->BMnc.size();
        display(d.hashRtYear(y)->accessHashCompName(company_name)->BMnc);
        break;
    case (04):
        result = d.hashRtYear(y)->accessHashCompName(company_name)->BEvd.size();
        display(d.hashRtYear(y)->accessHashCompName(company_name)->BEvd);
        break;
    case (11):
        result = d.hashRtYear(y)->accessHashCompName(company_name)->MIct.size();
        display(d.hashRtYear(y)->accessHashCompName(company_name)->MIct);
        break;
    case (12):
        result = d.hashRtYear(y)->accessHashCompName(company_name)->MScIt.size();
        display(d.hashRtYear(y)->accessHashCompName(company_name)->MScIt);
        break;
    case (14):
        result = d.hashRtYear(y)->accessHashCompName(company_name)->MDes.size();
        display(d.hashRtYear(y)->accessHashCompName(company_name)->MDes);
        break;
    case (18):
        result = d.hashRtYear(y)->accessHashCompName(company_name)->MScDS.size();
        display(d.hashRtYear(y)->accessHashCompName(company_name)->MScDS);
        break;
    }

    return result;
}
void students_in_comp_program_yearly(DataBase d, int y, string company_name)
{
    if (d.hashRtYear(y)->accessHashCompName(company_name) == NULL)
    {
        cout<<"The company did not visit the campus for placement that year"<<endl;
    }
    else{
    int Btech_result,Mtech_result,Msc_result,Mdes_result;
    Btech_result = d.hashRtYear(y)->accessHashCompName(company_name)->BIct.size()+d.hashRtYear(y)->accessHashCompName(company_name)->BIctCs.size()+ d.hashRtYear(y)->accessHashCompName(company_name)->BMnc.size()+d.hashRtYear(y)->accessHashCompName(company_name)->BEvd.size();
    Mtech_result=d.hashRtYear(y)->accessHashCompName(company_name)->MIct.size();
    Msc_result=d.hashRtYear(y)->accessHashCompName(company_name)->MScIt.size()+d.hashRtYear(y)->accessHashCompName(company_name)->MScDS.size();
    Mdes_result=d.hashRtYear(y)->accessHashCompName(company_name)->MDes.size();
    cout<<"Number of students place in "<<company_name<<"for Btech Program: "<<Btech_result<<endl;
    cout<<"Number of students place in "<<company_name<<"for Mtech Program: "<<Mtech_result<<endl;
    cout<<"Number of students place in "<<company_name<<"for MSc Program: "<<Msc_result<<endl;
    cout<<"Number of students place in "<<company_name<<"for Mdes Program: "<<Mdes_result<<endl;
    }
}


void display(vector<Student *> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i]->sName << endl;
    }
}

int students_branch_yearly(DataBase d, int y, int branch_code)
{
    int result=0;
    for(int i=0 ; i<d.hashRtYear(y)->No_of_Comp ; i++){
        result=result+ d.hashRtYear(y)->company[i].BIct.size();
        display(d.hashRtYear(y)->company[i].BIct);
    }
    ofstream fp;
    fp.open("students_branch_yearly.csv");
    
    return result;
}