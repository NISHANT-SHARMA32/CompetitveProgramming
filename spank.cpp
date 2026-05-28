// Author: Nishant Sharma
// Created: 2026-05-28 12:00:18
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
        static int t;
};

int Temp::t = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    Temp* o1 = new Temp();
    o1->t += 1;

    Temp* o2 = new Temp();

    cout << o1->t << " " << o2->t << endl;

}