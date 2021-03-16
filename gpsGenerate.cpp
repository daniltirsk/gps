#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;

int PRN_TABLE[32][2] = {
    {2,6},{3,7},{4,8},{5,9},{1,9},{2,10},{1,8},{2,9},{3,10},{2,3},{3,4},{5,6},
    {6,7},{7,8},{8,9},{9,10},{1,4},{2,5},{3,6},{4,7},{5,8},{6,9},{1,3},{4,6},
    {5,7},{6,8},{7,9},{8,10},{1,6},{2,7},{3,8},{4,9}
};

bool getBitG1(vector<bool>& arr){
    bool bit = 0;
    bit = arr[2] ^ arr[9];
    arr.insert(arr.begin(),bit);
    arr.pop_back();
    bit = arr.back();
    return bit;
}

bool getBitG2(vector<bool>& arr,int PRN){
    bool bit = 0;
    bit = arr[1] ^ arr[2] ^ arr[5] ^ arr[7] ^ arr[8] ^ arr[9];
    arr.insert(arr.begin(),bit);
    arr.pop_back();
    bit = arr[PRN_TABLE[PRN][0]-1] ^ arr[PRN_TABLE[PRN][1]-1];
    return bit;
}

int main(){
    vector<bool> g1_codes;
    vector<bool> g2_codes;
    vector<bool> ca_code;
    bool caBit;
    int PRN;

    cout<<"Enter PRN: "<<endl;
    cin>>PRN;
    PRN--;

    for (int i=0;i<10;i++){
        g1_codes.push_back(1);
        g2_codes.push_back(1);
    }
    for(int i=0; i<1022;i++){
        caBit = getBitG1(g1_codes) ^ getBitG2(g2_codes,PRN);
        cout<<caBit;
    }
    return 0;
}
