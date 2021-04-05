#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// coords - x,y,distance

class Circle{
public:
    double x;
    double y;
    double r;

    vector<double> triangulate(Circle* c2){
        vector<double> intersections;

        double d=sqrt((c2->x-this->x)*(c2->x-this->x) + (c2->y-this->y)*(c2->y-this->y));
        // non intersecting
        if (d > this->r + c2->r){
            return intersections;
        }
        // One circle within other
        if (d < abs(this->r-c2->r)){
            return intersections;
        }
        // coincident circles
        if (d == 0 && this->r == c2->r){
            return intersections;
        }
        else
        {
            double a=(this->r*this->r-c2->r*c2->r+d*d)/(2*d);
            double h=sqrt(this->r*this->r-a*a);
            double x2=this->x+a*(c2->x-this->x)/d;
            double y2=this->y+a*(c2->y-this->y)/d;
            double x3=x2+h*(c2->y-this->y)/d;
            double y3=y2-h*(c2->x-this->x)/d;
            double x4=x2-h*(c2->y-this->y)/d;
            double y4=y2+h*(c2->x-this->x)/d;

            if(x3 == x4 && y3 == y4){
                intersections.push_back(x3);
                intersections.push_back(y3);
                return intersections;
            } else {
                intersections.push_back(x3);
                intersections.push_back(y3);
                intersections.push_back(x4);
                intersections.push_back(y4);
                return intersections;
            }
        }
    }

    Circle(int x, int y, int r){
        this->x = x;
        this->y = y;
        this->r = r;
    }
};


int main(){
    Circle a = Circle(15,15,10);
    Circle b = Circle(10,10,10);

    vector<double> intersects;
    intersects = a.triangulate(&b);
    for(int i=0; i<intersects.size();i+=2) cout<<"x: "<<intersects[i]<<" y: "<< intersects[i+1]<<endl;
    return 0;
}
