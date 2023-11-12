#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){

    vector<string> vec = {"alah", "maxim"};
    vec.erase(vec.begin());
    vec.erase(vec.begin());
    cout << vec.size() << endl;




    return 0;
}