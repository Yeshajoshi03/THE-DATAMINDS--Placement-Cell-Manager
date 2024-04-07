#include <iostream>
using namespace std;
#include"DataStructure.cpp"
int main(){
    DataBase database;
    set_data("Year.txt",&database);

    cout <<"Welcome to our placement cell manager program." << endl;

    int num;
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
             <<"Press 0 to go back to main menu." << endl;
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
        int temp;
        cout <<"For highest package related information::press 1"<<endl;
        cout <<"For lowest package related information::press 2"<<endl;
        cout <<"For average package related information:: press 3"<<endl;
        cin >>temp;
        if(temp==1){

        }
        else if(temp==2){

        }
        else if(temp==3){
            
        }

    }break;

    case 4:{


    }break;
    
    default:
        break;
    }
    


    return 0;
}