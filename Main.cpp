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
    switch (num)
    {
    case 1:
    {
    label1:
        cout << "Press 1 to get the complete details of student" << endl
             << "Press 2 to get the students placed in companies branchwise in a year." << endl
             << "Press 0 to go back to main menu." << endl;
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
            cout <<endl <<"Branch Codes for every branch are as: " << endl
                 << "01 for B.Tech ICT" << endl
                 << "0144 for B.Tech ICT-CS" << endl
                 << "03 for B.Tech MNC" << endl
                 << "04 for B.Tech EVD" << endl
                 << "11 for M.Tech ICT" << endl
                 << "12 for MSc IT" << endl
                 << "14 for MDes" << endl
                 << "18 for MSc DS" << endl
                 <<endl<<"Enter Branchcode " ;
                 cin>>branchCode;
            num = students_branch_yearly(database, year, branchCode);
            cout<<endl<<"Total "<<num<<" number of students are placed in the year "<<year<<" in required branch."<<endl;
            goto label1;
        }else{
            goto label;
        }
            
    break;
    }
    
    case 2:
    {label2:
        cout<<"Press 1 to get the number of students who applied in a company in a particular year"<<endl
            <<"Press 2 to get the number of students in a particular company in all years."<<endl;

        break;
    }
    
    case 3:
    {
        int temp;
        cout << "For highest package related information::press 1" << endl;
        cout << "For lowest package related information::press 2" << endl;
        cout << "For average package related information:: press 3" << endl;
        cin >> temp;
        if (temp == 1)
        {
        }
        else if (temp == 2)
        {
        }
        else if (temp == 3)
        {
        }
    }
    break;

    case 4:
    {
    }
    break;

    default:
        break;
    }

    return 0;
}