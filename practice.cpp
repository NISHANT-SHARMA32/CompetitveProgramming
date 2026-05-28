// Author: Nishant Sharma
// Created: 2026-05-13 12:58:34
#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

class Temp{
    public:
        Temp(){cout << "constructor called" << endl;}
        ~Temp(){cout << "destructor called" << endl;}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    Temp* t = new Temp();
    delete t;

}