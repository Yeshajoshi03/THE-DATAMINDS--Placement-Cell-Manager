#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#include <vector>
#include <cmath>
// int vectorToInt(const std::vector<int>& vec) {
//     int result = 0;
//     for (size_t i = 0; i < vec.size(); ++i) {
//         result += vec[i] * pow(10, vec.size() - 1 - i); // This will place digits in correct positions
//     }
//     return result;
// }
// int main(){
//     string ID;
//     cout << "Enter : "<<endl;
//     cin>>ID;
//     vector<int> year(4,4);
//     year.at(0)=2;
//     year.at(1)=0;
//     if(ID.at(2)==0){
//         if(ID.at(3)==8 || ID.at(3)==9 ||ID.at(3)==10 ){
//             year.at(2)=1;
//             year.at(3)=(ID.at(3)+4)%10;
//         }
//         else{
//             year.at(2)=0;
//             year.at(3)=(ID.at(3)+4);
//         }
//     }
//     if(ID.at(2)==1){
//         if(ID.at(3)==8 || ID.at(3)==9 ||ID.at(3)==10 ){
//             year.at(2)=2;
//             year.at(3)=(ID.at(3)+4)%10;     
//         }
//         else{
//             year.at(2)=1;
//             year.at(3)=(ID.at(3)+4);
//         }
//     }
//     if(ID.at(2)==2){
//         if(ID.at(3)==8 || ID.at(3)==9 ||ID.at(3)==10 ){
//             year.at(2)=3;
//             year.at(3)=(ID.at(3)+4)%10;
//         }
//         else{
//             year.at(2)=2;
//             year.at(3)=(ID.at(3)+4);
//         }
//     }
//     int Year;
//     Year=vectorToInt(year);
//     cout << Year;
//     return 0;
// }
int main(){
    string str;
    cout << "Enter : " ;
    cin >> str;
    int year=0;
    for(int i=0;i<4;i++){
        year=year+((int)(str[i])-48)*(pow(10,3-i));
    }
    year+=4;
    cout << year;
    return 0;
}
