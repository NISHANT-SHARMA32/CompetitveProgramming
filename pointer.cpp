// Author: Nishant Sharma
// Created: 2026-02-07 15:28:56
#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

void func(string &s, int i, int j){
    if(i == j) return;
    swap(s[i],s[j]);
    func(s, i + 1, j - 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int *ptr = new int;
    delete ptr;
    cout << *ptr;

    //cout << *ptr;
    return 0;
}