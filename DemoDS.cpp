#include <bits/stdc++.h>
using namespace std;
class DataBase;
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
    void setStudent(string n, string date, string st, string et, int i, string mail, string prog, string cont ,string whats, string altNo, string skypeid ){
        id=i;
        sName=n;
        intDate=date;
        start_time=st;
        end_time=et;
        email=mail;
        program=prog;
        contact_no=cont;
        Whatsapp_no=whats;
        alt_no=altNo; 
        skypeID=skypeid;
    }
    friend class Round; 
};

class Round
{
    private:
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
    Student* hashStudentId(int id){
        int i=0;
        while(1){
            int h;
            h = (id%23 + (i * id%11))% numS;//double hashing
            if(student[h].sName.empty())
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
};

class Company
{
    private:
    string cName;
    // int salery;

    Round R1;
    Round R2;
    Round R3;
    Round HR;
    Round Final;
    Round *rptr[5];

    public:
    Company()
    {
        rptr[0] = &R1;
        rptr[1] = &R2;
        rptr[2] = &R3;
        rptr[3] = &HR;
        rptr[4] = &Final;
    }
    void set_comp_name(string s){
        cName=s;
    }
    friend class Year;
    friend void set_data(string year_file, DataBase*);
};

class Year
{
    private:
    int yr;
    int No_of_Comp;
    Company * company;

    public:
    void allocateCompMemory(int noC)
    {
        company = new Company[noC];
        No_of_Comp=noC;
    }

    void setYear(int c, int r, int i, string n);

    void set_yr(int y){
        yr=y;
    }
    Company* hashCompName(string comp_name){
        int comp_code=0;//company name to company code for hashing
        for(int j=0; j<3; j++){
            int temp;
            temp=comp_name[j]* pow(10,4-(2*j));
            comp_code= comp_code+temp;
        }
        int i=0;
        while(1){

            int h;

            h = (comp_code%97 + (i * comp_code%23))% No_of_Comp;//double hashing
            if(company[h].cName.empty())
            {
                company[h].cName == comp_name;
                return &company[h];
                break;
            }
            else
            {
                i++;
            }
                
        }
    }
    
};

class DataBase
{
    private:
    Year *year;
    int No_yr;

    public:
    DataBase(){
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
    

    void setData(int y, int c, int r, int i, string n){
        year[y%No_yr].setYear(c,r,i,n);
    }

    Year * hashRtYear(int y)//ASSUMPTION: Continuous year data
    {
        return &year[y%No_yr];
    }
};

void startdata(ifstream *f)
{
    string stemp;
    getline(*f, stemp, ',');
    while(stemp != "1"){//pointing to data in csv file 
    string t;
    getline(*f, t, '\n');
    getline(*f, stemp, ',');
    }
}

int count(ifstream *f){//pass by refernce
    int c=0;
    while(f->peek() != EOF)
    {     
        string str;
        getline(*f, str, '\n');
        c++;
    }
    return c;
}

void set_data(string year_file, DataBase* All_std_data){
    
    ifstream my_yr_file;
    my_yr_file.open(year_file);
    int No_yr;
    No_yr = count(&my_yr_file);//gets the number of year

    All_std_data->allocateYearMemory(No_yr);

    my_yr_file.seekg(0 , my_yr_file.beg);
    
    for(int i=0 ; i<No_yr ; i++)
    { 
        ifstream my_comp_file;

        string yearF;
        getline(my_yr_file, yearF, '\n');

        int int_year=0;//string year to int year
        for(int j=0; j<4; j++){//first 4 chars from filename
            int temp;
            temp=(yearF[j]-'0')* pow(10,3-j);
            int_year= int_year+temp;
        }

        Year *yptr = All_std_data->hashRtYear(int_year);

        yptr->set_yr(int_year);

        my_comp_file.open(yearF);

        int No_c= count(&my_comp_file);
        No_c = No_c/5;//Gets the number of company

        yptr->allocateCompMemory(No_c);

        my_comp_file.seekg(0, my_comp_file.beg);
//ROUND

        for(int j=0 ; j<No_c ; j++){
            string comp_name;
            getline(my_comp_file, comp_name, '\n');//round1
            Company *cptr;
            cptr = yptr->hashCompName(comp_name);//points to individual company
            
            ifstream comp_round_file;
            comp_round_file.open(comp_name);//points to round1 file of a company

            startdata(&comp_round_file);//function to set pointer to start of data
            
            int No_std;//number of student in first round of a company
            No_std=count(&comp_round_file);

            cptr->rptr[0]->allocateStuMemory(No_std);//allocated student memory
            
            comp_round_file.seekg(0,comp_round_file.beg);
            startdata(&comp_round_file);
            comp_round_file.seekg(-1,comp_round_file.cur);//pointing to 1
            
            while(comp_round_file.peek() != EOF){
                int tempID=0;
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

                for(int j=0; j<9; j++)//string std_id to int std_id
                {
                    int temp;
                    temp=(tempid[j]-'0')* pow(10,8-j);
                    tempID= tempID+temp;
                }
                Student *sptr = cptr->rptr[0]->hashStudentId(tempID);
                sptr->setStudent(tempname, tempdate, tempstr, tempend, tempID, tempmail, tempPro, tempcont, tempwhats, tempalt, tempskype);
                
            }                
            
            for(int i=1; i<5 ; i++){

                getline(my_comp_file, comp_name, '\n'); 

                comp_round_file.open(comp_name);//points to round i+1 file of a company

                startdata(&comp_round_file);//function to set pointer to start of data
                
                int No_std;//number of student in first round of a company
                No_std=count(&comp_round_file);

                cptr->rptr[i]->allocateStuMemory(No_std);//allocated student memory
                
                comp_round_file.seekg(0,comp_round_file.beg);
                startdata(&comp_round_file);
                comp_round_file.seekg(-1,comp_round_file.cur);//pointing to 1
                
                while(comp_round_file.peek() != EOF){
                    int tempID=0;
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

                    for(int j=0; j<9; j++)//string std_id to int std_id
                    {
                        int temp;
                        temp=(tempid[j]-'0')* pow(10,8-j);
                        tempID= tempID+temp;
                    }
                    Student *sptr = cptr->rptr[i]->hashStudentId(tempID);
                    sptr->setStudent(tempname, tempdate, tempstr, tempend, tempID, tempmail, tempPro, tempcont, tempwhats, tempalt, tempskype);
                    
                }          
            }     
        }
    }
}

int main()
{   
    DataBase database;
    
    set_data("Year.txt", &database);


    
}
