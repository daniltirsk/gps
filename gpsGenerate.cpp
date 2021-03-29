#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int PRN_TABLE[32][2] = {
    {2,6},{3,7},{4,8},{5,9},{1,9},{2,10},{1,8},{2,9},{3,10},{2,3},{3,4},{5,6},
    {6,7},{7,8},{8,9},{9,10},{1,4},{2,5},{3,6},{4,7},{5,8},{6,9},{1,3},{4,6},
    {5,7},{6,8},{7,9},{8,10},{1,6},{2,7},{3,8},{4,9}
};

bool getBitG1(vector<bool>& arr) {
    bool bit = 0;
    bit = arr[2] ^ arr[9];
    arr.insert(arr.begin(), bit);
    arr.pop_back();
    bit = arr.back();
    return bit;
}

bool getBitG2(vector<bool>& arr, int PRN) {
    bool bit = 0;
    bit = arr[1] ^ arr[2] ^ arr[5] ^ arr[7] ^ arr[8] ^ arr[9];
    arr.insert(arr.begin(), bit);
    arr.pop_back();
    bit = arr[PRN_TABLE[PRN][0] - 1] ^ arr[PRN_TABLE[PRN][1] - 1];
    return bit;
}

vector<bool> generateCA(int PRN) {
    vector<bool> CA;
    vector<bool> g1_codes;
    vector<bool> g2_codes;
    vector<bool> ca_code;
    bool caBit;

    PRN--;

    for (int i = 0; i < 10; i++) {
        g1_codes.push_back(1);
        g2_codes.push_back(1);
    }
    for (int i = 0; i < 1023; i++) {
        caBit = getBitG1(g1_codes) ^ getBitG2(g2_codes, PRN);
        CA.push_back(caBit);
    }

    return CA;
}

vector<bool> generateSignal(int PRN, int n, int offset) {
    vector<bool> signal;
    vector<bool> CA;
    vector<bool> nav;
    for (int i = 0; i < 128; i += 2) {
        nav.push_back(1);
        nav.push_back(0);
    }

    CA = generateCA(PRN);

    for (int i = 0; i < n; i++) {
        signal.insert(signal.end(), CA.begin(), CA.end());
        signal.insert(signal.end(), nav.begin(), nav.end());
    }
    signal.erase(signal.begin(), signal.begin() + offset);
    return signal;
}

int correlate(vector<bool> input, vector<bool> CA) {
    int sum = 0;
    int shift = 0;
    while (sum / 1023 != 1) {
        sum = 0;
        if (shift > input.size() - CA.size()) return 0;
        for (int i = 0; i < 1023; i++) {
            sum += (1 - 2 * CA[i]) * (1 - 2 * input[i + shift]);
        }
        //cout<<sum<<endl;
        shift++;
    }
    return shift - CA.size() - 128 - 1;

}

int findPRN(vector<bool> input) {
    vector<bool> code;
    int correlation = 0;
    for (int i = 1; i < 33; i++) {
        code = generateCA(i);
        correlation = correlate(input, code);
        if (correlation) return i;
    }
    return 0;
}

vector<double> getSatelliteCoord(double orbitCenterX, double orbitCenterY, double r, double speed, double time) {
    vector<double> coords;
    coords.push_back(cos(time * speed * M_PI / 180) * r + orbitCenterX);
    coords.push_back(sin(time * speed * M_PI / 180) * r + orbitCenterY);
    return coords;
}

vector<double> triangulate(vector<double> coords1, vector<double> coords2) {
        vector<double> recieverCoords;
        double centerdx = coords1[0] - coords2[0];
        double centerdy = coords1[1] - coords2[1];
        double R = sqrt(centerdx * centerdx + centerdy * centerdy);
        if (!(abs(coords1[2] - coords2[2]) <= R && R <= coords1[2] - coords2[2])) {
            return recieverCoords;
        }

        double R2 = R * R;
        double R4 = R2 * R2;
        double a = (coords1[2] * coords1[2] - coords2[2] * coords2[2]) / (2 * R2);
        double r2r2 = (coords1[2] * coords1[2] - coords2[2] * coords2[2]);
        double c = sqrt(2 * (coords1[2] * coords1[2] + coords2[2] * coords2[2]) / R2 - (r2r2 * r2r2) / R4 - 1);

        double fx = (coords1[0] - coords2[0]) / 2 + a * (coords2[0] - coords1[0]);
        double gx = c * (coords2[1] - coords1[1]) / 2;
        double ix1 = fx + gx;
        double ix2 = fx - gx;

        double fy = (coords1[1] + coords2[1]) / 2 + a * (coords2[1] - coords1[1]);
        double gy = c * (coords1[0] - coords2[0]) / 2;
        double iy1 = fy + gy;
        double iy2 = fy - gy;

        recieverCoords.push_back(ix1);
        recieverCoords.push_back(iy1);
        recieverCoords.push_back(ix2);
        recieverCoords.push_back(iy2);


        return recieverCoords;
}

int main() {
    vector<bool> a;
    vector<bool> b;
    a = generateCA(2);
    b = generateSignal(2, 2, 25);

}
