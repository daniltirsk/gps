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

vector<bool> generateCA(int PRN){
    vector<bool> CA;
    vector<bool> g1_codes;
    vector<bool> g2_codes;
    vector<bool> ca_code;
    bool caBit;

    PRN--;

    for (int i=0;i<10;i++){
        g1_codes.push_back(1);
        g2_codes.push_back(1);
    }
    for(int i=0; i<1023;i++){
        caBit = getBitG1(g1_codes) ^ getBitG2(g2_codes,PRN);
        CA.push_back(caBit);
    }

    return CA;
}

int correlate(vector<bool> input, vector<bool> CA){
    int sum = 0;
    int shift = 0;
    while(sum/1023!=1){
        sum = 0;
        if(shift > input.size() - CA.size()) return 0;
        for(int i = 0; i < 1023; i++){
            sum += (1 - 2*CA[i])*(1 - 2*input[i+shift]);
        }
        //cout<<sum<<endl;
        shift++;
    }
    return shift - CA.size()-128 - 1;

}


int main(){
    int N = 0;
    char bit;
    //read file with signal
    vector<bool> signal;
    ifstream inp;
    inp.open("signal.txt",ios::in);
    if (inp.is_open()){
        inp >> N;
        inp.get(bit);
        while (inp.get(bit)) {
            signal.push_back(bit == '1');
        }
        inp.close();
    }
    // find PRN
    int PRN=0;
    vector<bool> code;
    int correlation=0;
    for(int i=1;i<33;i++){
        code = generateCA(i);
        correlation = correlate(signal,code);
        if(correlation) PRN = i;
    }
    cout<<PRN;
}

