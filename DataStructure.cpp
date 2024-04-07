#include <bits/stdc++.h>
using namespace std;

class DataBase;

int random_salary_genrator()
{
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
    friend void display(vector<Student *> v);
    friend void Student_Complete_Information(int ID, DataBase D);
    friend void infile(vector<Student *> v, ofstream &f);
    friend int students_in_company(DataBase d, string company_name);
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
            h = (id % numS + i) % numS; // linear probing
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
        return NULL;
    }

    friend int students_in_comp_year(DataBase d, int y, string company_name);
    friend int students_in_company(DataBase d, string company_name);
    friend void Student_Complete_Information(string ID, DataBase D);

    friend int students_in_comp_branch_yearly(DataBase d, int y, string company_name, int branch_code);
    friend void student_company_application(DataBase s, int year, string company);
    friend void studet_year_company_passpercentage(DataBase d,int year, string company);

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
        if (str[4] == '0')
        { // Bachelors
            if (str[5] == '1' && str[6] != '4')
            {
                BIct.push_back(s);
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
    friend class Year;
    friend void set_data(string year_file, DataBase *);
    friend int students_in_comp_year(DataBase d, int y, string company_name);
    friend int students_in_comp_branch_yearly(DataBase d, int y, string company_name, int branch_code);
    friend int students_in_company(DataBase d, string company_name);
    friend void Student_Complete_Information(int ID, DataBase D);
    friend void students_in_comp_program_yearly(DataBase d, int y, string company_name);
    friend void student_allcompany_applied(DataBase s, string sID);
    friend int students_branch_yearly(DataBase d, int y, int branch_code);
    friend void student_company_application(DataBase s, int year, string company);
    friend int average_salary_year_branch(DataBase *d, int y, int b_code);
    friend int highest_salary_year_branch(DataBase *d, int y, int b_code);
    friend void studet_year_company_passpercentage(DataBase d,int year, string company);

};

class Year
{
private:
    int yr;
    int No_of_Comp;
    Company *company;

    int highest_package, lowest_package, average_package;

    vector<vector<Student *> *> Ybict;

public:
    Year() : highest_package(0), lowest_package(9000000), average_package(0) {}

    friend int highest_salary_year(DataBase *d, int y);
    friend int lowest_salary_year(DataBase *d, int y);
    friend int average_salary_year(DataBase *d, int y);

    void allocateCompMemory(int noC)
    {
        company = new Company[noC];
        No_of_Comp = noC;

        for (int i = 0; i < noC; i++)
        {
            Ybict.push_back(&company[i].BIct);
        }
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
                company[h].cName = comp_name.erase(comp_name.length()-12,12);
                return &company[h];
            }
            else
            {
                i++;
            }
        }
    }
    friend void Student_Complete_Information(int ID, DataBase D);
    friend int average_salary_year_branch(DataBase *d, int y, int b_code);
    friend int highest_salary_year_branch(DataBase *d, int y, int b_code);

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
            h = (comp_code % No_of_Comp + i) % No_of_Comp; // hashing

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
    friend void studet_year_company_passpercentage(DataBase d,int year, string company);

    
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

int highest_salary_year(DataBase *d, int y)
{
    return d->hashRtYear(y)->highest_package;
}

int lowest_salary_year(DataBase *d, int y)
{
    return d->hashRtYear(y)->lowest_package;
}

int average_salary_year(DataBase *d, int y)
{
    return d->hashRtYear(y)->average_package;
}

int average_salary_year_branch(DataBase *d, int y, int b_code)
{
    int sum=0;
    int no_st=0;

    switch (b_code)
    {
    case (01):
        for(int i=0 ; i<d->hashRtYear(y)->No_of_Comp ; i++)
        {
            Company *cptr = &d->hashRtYear(y)->company[i];
            sum = sum + (cptr->salery * cptr->BIct.size());
            no_st = no_st + cptr->BIct.size();
        }
        break;
    case (0144):
        for(int i=0 ; i<d->hashRtYear(y)->No_of_Comp ; i++)
        {
            Company *cptr = &d->hashRtYear(y)->company[i];
            sum = sum + (cptr->salery * cptr->BIctCs.size());
            no_st = no_st + cptr->BIctCs.size();
        }
        break;
    case (03):
        for(int i=0 ; i<d->hashRtYear(y)->No_of_Comp ; i++)
        {
            Company *cptr = &d->hashRtYear(y)->company[i];
            sum = sum + (cptr->salery * cptr->BMnc.size());
            no_st = no_st + cptr->BMnc.size();
        }
        break;
    case (04):
        for(int i=0 ; i<d->hashRtYear(y)->No_of_Comp ; i++)
        {
            Company *cptr = &d->hashRtYear(y)->company[i];
            sum = sum + (cptr->salery * cptr->BEvd.size());
            no_st = no_st + cptr->BEvd.size();
        }
        break;
    case (11):
       for(int i=0 ; i<d->hashRtYear(y)->No_of_Comp ; i++)
        {
            Company *cptr = &d->hashRtYear(y)->company[i];
            sum = sum + (cptr->salery * cptr->MIct.size());
            no_st = no_st + cptr->MIct.size();
        }
        break;
    case (12):
        for(int i=0 ; i<d->hashRtYear(y)->No_of_Comp ; i++)
        {
            Company *cptr = &d->hashRtYear(y)->company[i];
            sum = sum + (cptr->salery * cptr->MScIt.size());
            no_st = no_st + cptr->MScIt.size();
        }
        break;
    case (14):
       for(int i=0 ; i<d->hashRtYear(y)->No_of_Comp ; i++)
        {
            Company *cptr = &d->hashRtYear(y)->company[i];
            sum = sum + (cptr->salery * cptr->MDes.size());
            no_st = no_st + cptr->MDes.size();
        }
        break;
    case (18):
      for(int i=0 ; i<d->hashRtYear(y)->No_of_Comp ; i++)
        {
            Company *cptr = &d->hashRtYear(y)->company[i];
            sum = sum + (cptr->salery * cptr->MScDS.size());
            no_st = no_st + cptr->MScDS.size();
        }
        break;
    }
    
    return sum/no_st;
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

        int t_std=0;

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
            if (sal < yptr->lowest_package)
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

            tempID1 = stoi(tempid1);
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

                tempID = stoi(tempid);
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

                tempID1 = stoi(tempid1);
                Student *sptr1 = cptr->rptr[i]->hashStudentId(tempID1);
                sptr1->setStudent(tempname1, tempdate1, tempstr1, tempend1, tempID1, tempmail1, tempPro1, tempcont1, tempwhats1, tempalt1, tempskype1);

                if (i == 4)
                {
                    cptr->separate_branchwise(tempid1, sptr1);

                    t_std = t_std + No_std;
                    yptr->average_package = yptr->average_package + (sal*No_std);
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

                    tempID = stoi(tempid);
                    Student *sptr = cptr->rptr[i]->hashStudentId(tempID);
                    sptr->setStudent(tempname, tempdate, tempstr, tempend, tempID, tempmail, tempPro, tempcont, tempwhats, tempalt, tempskype);
                    if (i == 4)
                    {
                        cptr->separate_branchwise(tempid, sptr);
                    }
                }
                
                comp_round_file.close();
            }
        }

        my_comp_file.close();

        yptr->average_package = yptr->average_package/t_std;

    }
    my_yr_file.close();
}

void Student_Complete_Information(int ID, DataBase D)
{

    int year = ID / 100000;

    int check = (ID / 10000) % 10;
    // int id = 0, b = 0;

    // for (int i = 0; i < 9; i++){
    //     id = id + ((int)ID.at(i) - 48) * pow(10, 8 - i);
    // }
    // int year = 0;
    // for (int i = 0; i < 4; i++){
    //     year = year + ((int)(ID[i]) - 48) * (pow(10, 3 - i));
    // }
    // for (int i = 4; i < 6; i++)
    // {
    //     b = b + ((int)ID[i] - 48) * (pow(10, 5 - i));
    // }
    if (check == 0)
    {
        year += 4;
        // cout << "test" << endl;
    }
    else if (check == 1)
    {
        year += 2;
        // cout << "test" << endl;
    }
    // cout << year << endl;
    // cout<<D.hashRtYear(2020)->accessHashCompName("Google")->R1.accesshashStdId(201601244)->sName;
    for (int i = 0; i < D.hashRtYear(year)->No_of_Comp; i++)
    {
        int counter = 0;
        for (int j = 0; j < 5; j++)
        {
            if (D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(ID) != NULL)
            {

                counter++;

                if (counter == 1)
                {
                    cout << "The name of student is : " << D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(ID)->sName << endl;
                    cout << "The contact no. of student is : " << D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(ID)->contact_no << endl;
                    cout << "The email ID of student is : " << D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(ID)->email << endl;
                    cout << "The Whatsapp no. of stdudent is : " << D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(ID)->Whatsapp_no << endl;
                    cout << "The skype ID of student is: " << D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(ID)->skypeID << endl;
                    cout << "The program of student enrolled is : " << D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(ID)->program << endl;
                }
            }
        }
        if (counter > 0)
        {
            cout << "The student appeared for Company "<<D.hashRtYear(year)->company[i].cName << endl;
            cout << "He cleared till Round " << counter << endl;
        }
        // D.hashRtYear(year)->company[i].rptr[j]->accesshashStdId(ID)==;
    }
}

void student_company_application(DataBase s, int year, string company);
int students_in_company(DataBase d, string company_name);
int students_in_comp_year(DataBase d, int y, string company_name);
int students_in_comp_branch_yearly(DataBase d, int y, string company_name, int branch_code);
void students_in_comp_program_yearly(DataBase d, int y, string company_name);
void display(vector<Student *> v);
void infile(vector<Student *> v, ofstream &f);
int students_branch_yearly(DataBase d, int y, int branch_code);
void students_in_comp_program_yearly(DataBase d, int y, string company_name);
void studet_year_company_passpercentage(DataBase d,int year, string company);

// int main()
// {
//     DataBase database;

//     set_data("Year.txt", &database);

//     cout << average_salary_year_branch(&database, 2019, 01) << endl;
//     cout << average_salary_year_branch(&database, 2019, 0144) << endl;
//     cout << average_salary_year_branch(&database, 2019, 03) << endl;
//     // int year;
//     // string company;
//     // int x;
//     // x=students_in_comp_year(database,2019,"Google");
//     // cout<<x;
//     // cout << database.no_of_years()<<endl;
//     // // cout<<database.year[1].accessHashCompName("Bell")->Final.numS;
//     // // cout<<"Hi";
//     // cout << database.year[0].yr<<endl;
//     // cout << database.year[1].yr<<endl;

//     // string st="2019";
//     // int int_year=0;//string year to int year
//     //     for(int j=0; j<4; j++){//first 4 chars from filename
//     //         int temp;
//     //         temp=(st[j]-'0')* pow(10,3-j);
//     //         int_year= int_year+temp;
//     //     }
//     // cout<<int_year<<endl;
//     // database
    int branch_code;
//     // // int Prog;
    // cout << "Enter 0 for B.Tech and 1 for M.Tech" << endl;
    // cin >> Prog;
    // cout << "Enter Branchcode for respective branches: " << endl
    //      << "Enter " << endl
    //      << "01 for B.Tech ICT" << endl
    //      << "0144 for B.Tech ICT-CS" << endl
    //      << "03 for B.Tech MNC" << endl
    //      << "04 for B.Tech EVD" << endl
    //      << "11 for M.Tech ICT" << endl
    //      << "12 for MSc IT" << endl
    //      << "14 for MDes" << endl
    //      << "18 for MSc DS" << endl;
//     // // cin >> branch_code;
//     // // cout << students_in_comp_branch_yearly(database, 2019, "Google", branch_code) << endl;
//     // // cout << students_branch_yearly(database, 2019, branch_code);

//     // cout<<"Enter company and year to get number of students who applied to a specific company"<<endl;\
//     // cin>>year;
//     // cin>>company;
//     //  student_company_application(database, year, company);
//     // // int year2;
//     // // string company2;
//     // // cout<<"Enter the name of the company and year to get the number of studets who are placed according to the program"<<endl;
//     // // cin>>year2;
//     // // cin>>company2;
//     Student_Complete_Information(201601044, database);
//     // // students_in_comp_program_yearly(database, year2, company2);
//     // cout<< students_in_company(database,"Sprinkler");
//     // cout<<students_in_comp_year(database,2020,"Bell");
//     // cout<<students_branch_yearly(database,2020,01);
//     cout<<"Enter year and company name to get the pass percentage"<<endl;
//     int year3;
//     string company3;
//     cin>>year3;
//     cin>>company3;
//     studet_year_company_passpercentage(database, year3,company3);
//     return 0;
// }

void student_company_application(DataBase s, int year, string company)
{
    if (s.hashRtYear(year)->accessHashCompName(company) == NULL)
    {
        cout << "Company did not came for placement" << endl;
    }
    else
    {
        int x = s.hashRtYear(year)->accessHashCompName(company)->R1.numS;
        cout << x << " Student applied for the company" << endl;
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
void studet_year_company_passpercentage(DataBase d,int year, string company)
{
    cout<<"Press 1 to get total percentage of students placed"<<endl;
    cout<<"Press 2 to get pass percetage of students from round to another round"<<endl;
    int choice;
    cin>>choice;
    float percentage;
    switch (choice)
    {
    case 1:
    {
        int numR1=d.hashRtYear(year)->accessHashCompName(company)->R1.numS;
        int numR5=d.hashRtYear(year)->accessHashCompName(company)->Final.numS;
        percentage=(numR5)*100.0/numR1;
        cout<<fixed << setprecision(2)<<percentage << "%" "students were placed"<<endl;
        break;
    }
    case 2:
    {
        int numRInitial;
        int numRAnother;
        cout<<"Enter initial round number"<<endl;
        cout<<"Enter another round number"<<endl;
        cin>> numRInitial;
        cin>> numRAnother;
        int numRIni=d.hashRtYear(year)->accessHashCompName(company)->rptr[numRInitial-1]->numS;
        int numRAno=d.hashRtYear(year)->accessHashCompName(company)->rptr[numRAnother-1]->numS;
        percentage=(numRAno)*100.0/numRIni;
        cout<< fixed << setprecision(2)<<percentage << " %" " students were placed from Round"<<numRInitial<<" to Round "<<numRAnother<<endl;
        break;
    }
    default:
    {
        cout<<"You have entered invalid case"<<endl;
        break;
    }
    }
}
int students_in_comp_year(DataBase d, int y, string company_name)
{ // Number of students placed in a particular company in a given year
    if (d.hashRtYear(y)->accessHashCompName(company_name) != NULL)
    {
        return d.hashRtYear(y)->accessHashCompName(company_name)->Final.numS;
    }
    else
    {
        cout << "The company did not visit the campus for placement that year" << endl;
        return 0;
    }
}

int students_in_comp_branch_yearly(DataBase d, int y, string company_name, int branch_code)
{
    if (d.hashRtYear(y)->accessHashCompName(company_name) == NULL)
    {
        cout << "The company did not visit the campus for placement that year" << endl;
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
        cout << "The company did not visit the campus for placement that year" << endl;
    }
    else
    {
        int Btech_result, Mtech_result, Msc_result, Mdes_result;
        Btech_result = d.hashRtYear(y)->accessHashCompName(company_name)->BIct.size() + d.hashRtYear(y)->accessHashCompName(company_name)->BIctCs.size() + d.hashRtYear(y)->accessHashCompName(company_name)->BMnc.size() + d.hashRtYear(y)->accessHashCompName(company_name)->BEvd.size();
        Mtech_result = d.hashRtYear(y)->accessHashCompName(company_name)->MIct.size();
        Msc_result = d.hashRtYear(y)->accessHashCompName(company_name)->MScIt.size() + d.hashRtYear(y)->accessHashCompName(company_name)->MScDS.size();
        Mdes_result = d.hashRtYear(y)->accessHashCompName(company_name)->MDes.size();
        cout << "Number of students place in " << company_name << "for Btech Program: " << Btech_result << endl;
        cout << "Number of students place in " << company_name << "for Mtech Program: " << Mtech_result << endl;
        cout << "Number of students place in " << company_name << "for MSc Program: " << Msc_result << endl;
        cout << "Number of students place in " << company_name << "for Mdes Program: " << Mdes_result << endl;
    }
}

void display(vector<Student *> v)
{
    cout << "Listing the Students " << endl;
    for (int i = 0; i < v.size(); i++)
    {
        cout << i + 1 << ") " << v[i]->sName << endl;
    }
}

void infile(vector<Student *> v, ofstream &f)
{

    for (int i = 0; i < v.size(); i++)
    {
        f << v[i]->getID() << ", " << v[i]->sName << ", " << v[i]->intDate << ", " << v[i]->contact_no << ", " << v[i]->email << ", " << endl;
    }
}

int students_branch_yearly(DataBase d, int y, int branch_code)
{
    int result = 0;
    switch (branch_code)
    {
    case (1):
    {
        ofstream fp;
        fp.open("Students_BTech_ICT_yearly.csv");
        fp << "Listing B.Tech ICT Students who are placed in year " << y << ",,,," << endl;
        fp << "ID, Name, Date, Contact No., Email ID " << endl;

        for (int i = 0; i < d.hashRtYear(y)->No_of_Comp; i++)
        {
            result = result + d.hashRtYear(y)->company[i].BIct.size();
            infile(d.hashRtYear(y)->company[i].BIct, fp);
        }
        fp.close();
        cout<<"Open Students_BTech_ICT_yearly.csv to get data of all required students."<<endl;
        break;
    }
    case (0144):
    {
        ofstream fp;
        fp.open("Sudents_BTech_ICT-CS_yearly.csv");
        fp << "Listing B.Tech ICT-CS Students who are placed in year " << y << ",,,," << endl;
        fp << "ID, Name, Date, Contact No., Email ID " << endl;

        for (int i = 0; i < d.hashRtYear(y)->No_of_Comp; i++)
        {
            result = result + d.hashRtYear(y)->company[i].BIctCs.size();
            infile(d.hashRtYear(y)->company[i].BIctCs, fp);
        }
        fp.close();
        cout<<"Open Students_BTech_ICT-CS_yearly.csv to get data of all required students."<<endl;
        break;
    }
    case (03):
    {
        ofstream fp;
        fp.open("Students_BTech_MNC_yearly.csv");
        fp << "Listing B.Tech MNC Students who are placed in year " << y << ",,,," << endl;
        fp << "ID, Name, Date, Contact No., Email ID " << endl;

        for (int i = 0; i < d.hashRtYear(y)->No_of_Comp; i++)
        {
            result = result + d.hashRtYear(y)->company[i].BMnc.size();
            infile(d.hashRtYear(y)->company[i].BMnc, fp);
        }
        fp.close();
        cout<<"Open Students_BTech_MNC_yearly.csv to get data of all required students."<<endl;
        break;
    }

    case (04):
    {
        ofstream fp;
        fp.open("Students_BTech_EVD_yearly.csv");
        fp << "Listing B.Tech EVD Students who are placed in year " << y << ",,,," << endl;
        fp << "ID, Name, Date, Contact No., Email ID " << endl;

        for (int i = 0; i < d.hashRtYear(y)->No_of_Comp; i++)
        {
            result = result + d.hashRtYear(y)->company[i].BEvd.size();
            infile(d.hashRtYear(y)->company[i].BEvd, fp);
        }
        fp.close();
        cout<<"Open Students_BTech_EVD_yearly.csv to get data of all required students."<<endl;
        break;
    }
    case (11):
    {
        ofstream fp;
        fp.open("Students_MTech_ICT_yearly.csv");
        fp << "Listing M.Tech ICT Students who are placed in year " << y << ",,,," << endl;
        fp << "ID, Name, Date, Contact No., Email ID " << endl;

        for (int i = 0; i < d.hashRtYear(y)->No_of_Comp; i++)
        {
            result = result + d.hashRtYear(y)->company[i].MIct.size();
            infile(d.hashRtYear(y)->company[i].MIct, fp);
        }
        fp.close();
        cout<<"Open Students_MTech_ICT_yearly.csv to get data of all required students."<<endl;
        break;
    }
    case (12):
    {
        ofstream fp;
        fp.open("Students_MSC_IT_yearly.csv");
        fp << "Listing MSc IT Students who are placed in year " << y << ",,,," << endl;
        fp << "ID, Name, Date, Contact No., Email ID " << endl;

        for (int i = 0; i < d.hashRtYear(y)->No_of_Comp; i++)
        {
            result = result + d.hashRtYear(y)->company[i].MScIt.size();
            infile(d.hashRtYear(y)->company[i].MScIt, fp);
        }
        fp.close();
        cout<<"Open Students_MSC_IT_yearly.csv to get data of all required students."<<endl;
        break;
    }
    case (14):
    {
        ofstream fp;
        fp.open("Students_MDes_yearly.csv");
        fp << "Listing MDes Students who are placed in year " << y << ",,,," << endl;
        fp << "ID, Name, Date, Contact No., Email ID " << endl;

        for (int i = 0; i < d.hashRtYear(y)->No_of_Comp; i++)
        {
            result = result + d.hashRtYear(y)->company[i].MDes.size();
            infile(d.hashRtYear(y)->company[i].MDes, fp);
        }
        fp.close();
        cout<<"Open Students_MDes_yearly.csv to get data of all required students."<<endl;
        break;
    }
    case (18):
    {
        ofstream fp;
        fp.open("Students_MScDs_yearly.csv");
        fp << "Listing MSc DS Students who are placed in year " << y << ",,,," << endl;
        fp << "ID, Name, Date, Contact No., Email ID " << endl;

        for (int i = 0; i < d.hashRtYear(y)->No_of_Comp; i++)
        {
            result = result + d.hashRtYear(y)->company[i].MScDS.size();
            infile(d.hashRtYear(y)->company[i].MScDS, fp);
        }
        fp.close();
        cout<<"Open Students_MScDs_yearly.csv to get data of all required students."<<endl;
        break;
    }
    default:
        cout<<"Enter valid branchcode."<<endl;
        break;
    }

    return result;
}