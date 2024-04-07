#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
#include "DataStructure.cpp"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
// int String_to_int(const string &str) // String_to_int function converts a string to the integer
// {
//     int result = 0;
//     int sign = 1;
//     int i = 0;
//     while (isspace(str[i]))
//     {
//         i++;
//     }
//     if (str[i] == '-' || str[i] == '+')
//     {
//         sign = (str[i++] == '-') ? -1 : 1;
//     }

//     while (isdigit(str[i]))
//     {
//         result = result * 10 + (str[i++] - '0');
//     }
//     return sign * result;
// }
int main()
{
    DataBase database;
    string inputyear;
    cout<<CYAN<<"\t \t \t \t \t \t------------------------------------------------"<<RESET<<endl;
    cout<<CYAN<<"\t \t \t \t \t \t|   P2-THE DATAMINDS--PLACEMENT-CELL-MANAGER   |\t \t"<<RESET<<endl;
    cout<<CYAN<<"\t \t \t \t \t \t------------------------------------------------"<<RESET<<endl;
    cout<<endl<<endl<<endl;
    cout << "Enter the name of year file in which all the years are stored: ";
    cin >> inputyear;
    set_data("Year.txt", &database);

    cout << endl<< "Our placement program currently offers following data" << endl<<endl<<endl;
    int num;
label:
    cout << "If you want student centric data: "<<YELLOW<<"press 1"<<RESET << endl<<endl;
    cout << "If you want company centric data: "<<YELLOW<<"press 2"<<RESET << endl<<endl;
    cout << "If you want package related details: "<<YELLOW<<"press 3"<<RESET << endl<<endl;
    cout << "To exit enter "<<YELLOW<<"0"<<RESET << endl<< endl;

    cout << "ENTER YOUR CHOICE : ";
    cin >> num;
    cout << endl;
    int choice;
    int branchCode;
    switch (num)
    {
    case 1:
    {
    label1:
        cout << YELLOW<<"press 1 "<<RESET <<"to get complete details of student" << endl<<endl;
        cout << YELLOW<<"press 2 "<<RESET <<"to get students placed in companies branchwise in a year." << endl<<endl;
        cout << YELLOW<<"press 0 "<<RESET <<"to go back to main menu." << endl<<endl;
        cout << "ENTER YOUR CHOICE: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter Student ID: ";
            int id;
            cin >> id;
            Student_Complete_Information(id, database);
            cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
            goto label1;
        }
        else if (choice == 2)
        {
            int year, num, branchCode;
            cout << "Enter the year you want to know about: ";
            cin >> year;
            cout << endl
                 << "Branch Codes for every branch are as: " << endl
                 << "01 for B.Tech ICT" << endl
                 << "0144 for B.Tech ICT-CS" << endl
                 << "03 for B.Tech MNC" << endl
                 << "04 for B.Tech EVD" << endl
                 << "11 for M.Tech ICT" << endl
                 << "12 for MSc IT" << endl
                 << "14 for MDes" << endl
                 << "18 for MSc DS" << endl
                 << endl
                 << "Enter Branchcode: ";
            cin >> branchCode;
            num = students_branch_yearly(database, year, branchCode);
            cout << "Total " << num << " number of students are placed in the year " << year << " in required branch." << endl
                 << endl;
            cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
            goto label1;
        }
        else
        {
            goto label;
        }

        break;
    }
    case 2: // company centric
    {

    label2:
        cout <<YELLOW<<"press 1"<<RESET <<" to get the number of students who applied in a company in a particular year" << endl
             <<YELLOW<<"press 2"<<RESET <<" to get the number of students placed in a particular company in all years." << endl
             <<YELLOW<<"press 3"<<RESET << " to get number of students in a particular company in given year." << endl // nested
             <<YELLOW<<"press 4"<<RESET <<" to get pass percentage of students of a given company of given year." << endl
             <<YELLOW<<"press 5"<<RESET << " to get in which round highest number of students were dropped in a given company in a given year." << endl
             <<YELLOW<<"press 0"<<RESET << " to exit." << endl
             << endl;

        cin >> choice;
        int year;
        string company;
        switch (choice)
        {
        case 1:
        {
            cout << "Enter the year: ";
            cin >> year;
            cout<<endl;
            cout << "Enter the name of company (Make sure that the first letter is capital): ";
            cin >> company;
            cout<<endl;
            student_company_application(database, year, company);
            cout<<endl;
            cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
            cout << endl<< endl;
            goto label2;
            break;
        }
        case 2:
        {
            cout << "Enter the name of company (Make sure that the first letter is capital): ";
            cin >> company;

            cout << "Number of students placed in " << company << ": " << students_in_company(database, company) << endl;
            cout<<endl;
            cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
            goto label2;
        }
        case 3:
        {
        sublabel:
            cout << YELLOW<<"press 1 "<<RESET <<"to get students of a given company of a given year Branch wise." << endl
                 << YELLOW<<"press 2 "<<RESET <<"to get students of a given company of a given year Programme wise." << endl
                 << YELLOW<<"press 3 "<<RESET <<"to get total students placed in a given comapany in a given year." << endl
                 << YELLOW<<"press 0 "<<RESET <<"to get to submenu." << endl
                 << endl;
            int c2;
            cin >> c2;
            switch (c2)
            {
            case 1:
            {
                cout << "Enter the year: ";
                cin >> year;
                cout << "Enter the name of company (Make sure that the first letter is capital): ";
                cin >> company;
                int branchCode;
                cout << endl
                     << "Branch Codes for every branch are as: " << endl
                     << "01 for B.Tech ICT" << endl
                     << "0144 for B.Tech ICT-CS" << endl
                     << "03 for B.Tech MNC" << endl
                     << "04 for B.Tech EVD" << endl
                     << "11 for M.Tech ICT" << endl
                     << "12 for MSc IT" << endl
                     << "14 for MDes" << endl
                     << "18 for MSc DS" << endl
                     << endl
                     << "Enter Branchcode ";
                cin >> branchCode;
                cout << students_in_comp_branch_yearly(database, year, company, branchCode) << " students are placed " << endl;
                cout<<endl;
                cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
                goto sublabel;
                break;
            }
            case 2:
            {
                cout << "Enter the year: ";
                cin >> year;
                cout<<endl;
                cout << "Enter the name of company (Make sure that the first letter is capital): ";
                cin >> company;
                cout << endl;
                students_in_comp_program_yearly(database, year, company);
                cout<<endl;
                cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
                goto sublabel;
                break;
            }
            case 3:
            {
                cout << "Enter the year: ";
                cin >> year;
                cout<<endl;
                cout << "Enter the name of company (Make sure that the first letter is capital): ";
                cin >> company;
                cout<<endl;
                cout << students_in_comp_year(database, year, company) << " students are there in " << year << " in " << company << endl
                     << endl;
                cout<<endl;
                cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
                goto sublabel;
                break;
            }
            case (0):
                goto label2;
            }
        }
        case 4:
        { // 4 to get pass percentage of students of a given company of given year.
   
            cout << "Enter the year: ";
            cin >> year;
            cout << "Enter the name of company (Make sure that the first letter is capital): ";
            cin >> company;
            cout << endl;
            student_year_company_passpercentage(database, year, company);
            cout<<endl;
            cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
            goto label2;
        }
        case 5:
        { // to get in which round highest number of students were dropped in a given company in a given year.

            cout << "Enter the year: ";
            cin >> year;
            cout<<endl;
            cout << "Enter the name of company (Make sure that the first letter is capital): ";
            cin >> company;
            cout<<endl;
            student__round_removedhighest(database, year, company);
            cout<<endl;
            cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
            goto label2;
        }

        case 0:
        {
            goto label;
        }
        }
        }
    case 3:
    {

    label3:
        cout << YELLOW<<"press 1 "<<RESET <<"to get highest package of any year." << endl
             << YELLOW<<"press 2 "<<RESET <<"to get average package of any year." << endl
             << YELLOW<<"press 3 "<<RESET <<"to get lowest package of any year" << endl
             << YELLOW<<"press 4 "<<RESET <<"to get highest package of a particualar branch in any year" << endl
             << YELLOW<<"press 5 "<<RESET <<"to get average package of a particualar branch in any year" << endl
             << YELLOW<<"press 0 "<<RESET <<"to go to main menu."
             << "ENTER YOUR CHOICE ";
        cin >> choice;
        int yr;
        switch (choice)
        {
        case 1:
            cout << "Enter the year of which you want highest package: ";
            cin >> yr;
            cout<<endl;
            cout << "Highest package of " << yr << ": " << highest_salary_year(&database, yr) << endl;
            cout<<endl;
            cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
            goto label3;

        case 2:
            cout << "Enter the year of which you want average package: ";
            cin >> yr;
            cout<<endl;
            cout << "Average package of " << yr << ": " << average_salary_year(&database, yr) << endl;
            cout<<endl;
            cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
            goto label3;

        case 3:
            cout << "Enter the year of which you want lowest package: ";
            cin >> yr;
            cout<<endl;
            cout << "Lowest package of " << yr << ": " << lowest_salary_year(&database, yr) << endl;
            cout<<endl;
            cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
            goto label3;

        case 4:
            cout << "Enter the year: ";
            cin >> yr;

            cout << endl
                 << "Branch Codes for every branch are as: " << endl
                 << "01 for B.Tech ICT" << endl
                 << "0144 for B.Tech ICT-CS" << endl
                 << "03 for B.Tech MNC" << endl
                 << "04 for B.Tech EVD" << endl
                 << "11 for M.Tech ICT" << endl
                 << "12 for MSc IT" << endl
                 << "14 for MDes" << endl
                 << "18 for MSc DS" << endl
                 << endl
                 << "Enter Branchcode: ";
            cin >> branchCode;
            cout<<endl;

            cout << "Highest package of " << yr << " of the required branch: " << highest_salary_year_branch(&database, yr, branchCode) << endl;
            cout<<endl;
            cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
            goto label3;

        case 5:
            cout << "Enter the year: ";
            cin >> yr;

            cout << endl
                 << "Branch Codes for every branch are as: " << endl
                 << "01 for B.Tech ICT" << endl
                 << "0144 for B.Tech ICT-CS" << endl
                 << "03 for B.Tech MNC" << endl
                 << "04 for B.Tech EVD" << endl
                 << "11 for M.Tech ICT" << endl
                 << "12 for MSc IT" << endl
                 << "14 for MDes" << endl
                 << "18 for MSc DS" << endl
                 << endl
                 << "Enter Branchcode: ";
            cin >> branchCode;

            cout << "Average package of " << yr << " of the required branch: " << average_salary_year_branch(&database, yr, branchCode) << endl;
            cout<<endl;
            cout<<CYAN<<"------------------------------------------------------------------------------------------------------"<<RESET<<endl;
            goto label3;

        case 0:
            goto label;
        }
    }
    }

        return 0;
    }