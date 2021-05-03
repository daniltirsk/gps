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

    vector<double> triangulate(Circle* c2, Circle* c3){
        vector<double> points,pair1,pair2,pair3,intersection;
        bool found = false;

        pair1 = this->circleIntersection(c2);
        pair2 = this->circleIntersection(c3);
        pair3 = c2->circleIntersection(c3);

        for (int i = 0 ; i<pair1.size();i+=2){
            for (int j = 0 ; j<pair2.size();j+=2){
                if(pair1[i] == pair2[j] && pair1[i+1] == pair2[j+1]){
                    for (int k = 0 ; k<pair3.size();k+=2){
                        if(pair1[i] == pair3[k] && pair1[i+1] == pair3[k+1]){
                            intersection.push_back(pair1[i]);
                            intersection.push_back(pair1[i+1]);
                            return intersection;
                        }
                    }
                }
            }
        }

        return intersection;
    }

    vector<double> circleIntersection(Circle* c2){
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
    Circle a = Circle(20,20,10);
    Circle b = Circle(10,10,10);
    Circle c = Circle(10,30,10);

    vector<double> intersects;
    intersects = a.triangulate(&b,&c);
    for(int i=0; i<intersects.size();i+=2) cout<<"x: "<<intersects[i]<<" y: "<< intersects[i+1]<<endl;
    return 0;
}
