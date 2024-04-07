#include <iostream>
using namespace std;
#include "DataStructure.cpp"
int main()
{
    DataBase database;
    string inputyear;
    cout << "Enter the name of year file: ";
    cin >> inputyear;
    set_data(inputyear, &database);

    cout << endl
         << "Welcome to our placement cell manager program." << endl;

    int num;

label:
    cout << "If you want student centric data: press 1" << endl;
    cout << "If you want company centric data: press 2" << endl;
    cout << "If you want package related details: press 3" << endl;
    cout << "To exit enter 0" << endl;

    cout << "ENTER : ";
    cin >> num;
    cout << endl;
    int choice;
    int branchCode;
    switch (num)
    {
    case 1:
    {
    label1:
        cout << "Press 1 for complete details of student" << endl
             << "Press 2 to get students placed in companies branchwise in a year." << endl
             << "Press 0 to go back to main menu." << endl
             << "ENTER: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter Student ID: ";
            int id;
            cin >> id;
            Student_Complete_Information(id, database);
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
                 << "Enter Branchcode ";
            cin >> branchCode;
            num = students_branch_yearly(database, year, branchCode);
            cout << "Total " << num << " number of students are placed in the year " << year << " in required branch." << endl
                 << endl;
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
        cout << "Press 1 to get the number of students who applied in a company in a particular year" << endl
             << "Press 2 to get the number of students placed in a particular company in all years." << endl
             << "Press 3 to get number of students in a particular company in given year." << endl // nested
             << "Press 4 to get pass percentage of students of a given company of given year." << endl
             << "Press 5 to get in which round highest number of students were dropped in a given company in a given year." << endl
             << "Press 0 to exit." << endl
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
            cout << "Enter the name of company (Make sure that the first letter is capital): ";
            cin >> company;
            student_company_application(database, year, company);
            cout << endl
                 << endl;
            goto label2;
            break;
        }
        case 2:
        {
            cout << "Enter the name of company (Make sure that the first letter is capital): ";
            cin >> company;

            cout << "Number of students placed in " << company << ": " << students_in_company(database, company) << endl;
            goto label2;
        }
        case 3:
        {
        sublabel:
            cout << "Enter 1 to get students of a given company of a given year Branch wise." << endl
                 << "Enter 2 to get students of a given company of a given year Programme wise." << endl
                 << "Enter 3 to get total students placed in a given comapany in a given year." << endl
                 << "Enter 0 to get to submenu." << endl
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
                goto sublabel;
                break;
            }
            case 2:
            {
                cout << "Enter the year: ";
                cin >> year;
                cout << "Enter the name of company (Make sure that the first letter is capital): ";
                cin >> company;
                cout << endl;
                students_in_comp_program_yearly(database, year, company);
                goto sublabel;
                break;
            }
            case 3:
            {
                cout << "Enter the year: ";
                cin >> year;
                cout << "Enter the name of company (Make sure that the first letter is capital): ";
                cin >> company;
                cout << students_in_comp_year(database, year, company) << " students are there in " << year << " in " << company << endl
                     << endl;
                goto sublabel;
                break;
            }
            case (0):
                goto label2;
            }
        }
        case 4:
        { // 4 to get pass percentage of students of a given company of given year.
            // int year;
            // string company;
            cout << "Enter the year: ";
            cin >> year;
            cout << "Enter the name of company (Make sure that the first letter is capital): ";
            cin >> company;
            cout << endl;
            student_year_company_passpercentage(database, year, company);
            goto label2;
        }
        case 5:
        { // to get in which round highest number of students were dropped in a given company in a given year.
            // int year;
            // string company;
            cout << "Enter the year: ";
            cin >> year;
            cout << "Enter the name of company (Make sure that the first letter is capital): ";
            cin >> company;
            student__round_removedhighest(database, year, company);
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
        cout << "Press 1 to get highest package of any year." << endl
             << "Press 2 to get average package of any year." << endl
             << "Press 3 to get lowest package of any year" << endl
             << "Press 4 to get highest package of a particualar branch in any year" << endl
             << "Press 5 to get average package of a particualar branch in any year" << endl
             << "Press 0 to go to main menu."
             << "ENTER: ";
        cin >> choice;
        int yr;
        switch (choice)
        {
        case 1:
            cout << "Enter the year of which you want highest package: ";
            cin >> yr;
            cout << "Highest package of " << yr << ": " << highest_salary_year(&database, yr) << endl;
            goto label3;

        case 2:
            cout << "Enter the year of which you want average package: ";
            cin >> yr;
            cout << "Average package of " << yr << ": " << average_salary_year(&database, yr) << endl;
            goto label3;

        case 3:
            cout << "Enter the year of which you want lowest package: ";
            cin >> yr;
            cout << "Lowest package of " << yr << ": " << lowest_salary_year(&database, yr) << endl;
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

            // cout << "Highest package of " << yr << " of the required branch: " << highest_salary_year_branch(&database, yr, branchCode) << endl;
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
            goto label3;

        case 0:
            goto label;
        }
    }
    }

        return 0;
    }