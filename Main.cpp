#include <iostream>
using namespace std;
#include"DataStructure.cpp"
int main(){
    DataBase database;
    set_data("Year.txt",&database);

    cout <<"Welcome to our placement cell manager program." << endl;

    int num;

    label:

    cout <<"If you want student centric data:: press 1"<<endl;
    cout <<"If you want company centric data:: press 2"<<endl;
    cout <<"If you want package related details:: press 3"<<endl;
    cout << "To exit enter 0" << endl;

    cout <<"ENTER :: ";
    cin >>num;
    switch (num)
    {
    case 1:{
        cout <<"Press 1 for complete details of student"<<endl
             <<"Press 2 to get students placed in companies branchwise in a year."<<endl
             <<"Press 0 to go back to main menu." << endl <<"ENTER: ";
             int choice;
             cin>>choice;
        if(choice ==1){
            cout<<"Enter Student ID: ";
            int id;
            cin>>id;
            Student_Complete_Information(id,database);
        }
    }break;
    case 2:{


    }break;
    case 3:{
        int choice;

        label3:
        cout <<"Press 1 to get highest package of any year."<<endl
             <<"Press 2 to get average package of any year."<<endl
             <<"Prsee 3 to get lowest package of any year"<<endl
             <<"Prsee 4 to get highest package of a particualar branch in any year"<<endl
             <<"Prsee 5 to get average package of a particualar branch in any year"<<endl
             <<"Press 0 to go to main menu." <<"ENTER: ";
        cin >>choice;

        switch(choice)
        {
            int yr;
            int branchCode;

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

            cout << endl << "Branch Codes for every branch are as: " << endl
                 << "01 for B.Tech ICT" << endl
                 << "0144 for B.Tech ICT-CS" << endl
                 << "03 for B.Tech MNC" << endl
                 << "04 for B.Tech EVD" << endl
                 << "11 for M.Tech ICT" << endl
                 << "12 for MSc IT" << endl
                 << "14 for MDes" << endl
                 << "18 for MSc DS" << endl
                 <<endl<<"Enter Branchcode: " ;
            cin>>branchCode;

            // cout << "Highest package of " << yr << " of the required branch: " << highest_salary_year_branch(&database, yr, branchCode) << endl;
            goto label3;

            case 5:
            cout << "Enter the year: ";
            cin >> yr;

            cout << endl << "Branch Codes for every branch are as: " << endl
                 << "01 for B.Tech ICT" << endl
                 << "0144 for B.Tech ICT-CS" << endl
                 << "03 for B.Tech MNC" << endl
                 << "04 for B.Tech EVD" << endl
                 << "11 for M.Tech ICT" << endl
                 << "12 for MSc IT" << endl
                 << "14 for MDes" << endl
                 << "18 for MSc DS" << endl
                 <<endl<<"Enter Branchcode: " ;
            cin>>branchCode;

            cout << "Average package of " << yr << " of the required branch: " << average_salary_year_branch(&database, yr, branchCode) << endl;
            goto label3;

            case 0:
            goto label;
        }

    }break;

    case 0:{


    }break;
    
    default:
        break;
    }
    


    return 0;
}