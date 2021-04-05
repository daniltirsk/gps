#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<double> getSatelliteCoord(double orbitCenterX, double orbitCenterY,double r,double speed,double time){
    vector<double> coords;
    coords.push_back(cos(time*speed*M_PI/180)*r + orbitCenterX);
    coords.push_back(sin(time*speed*M_PI/180)*r + orbitCenterY);
    return coords;
}

int main(){
    vector<double> coords;
    coords = getSatelliteCoord(0,0,10,5,9);
    for(int i = 0; i<coords.size();i++) cout<<coords[i]<<endl;

    return 0;
}

