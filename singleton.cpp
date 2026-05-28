// Author: Nishant Sharma
// Created: 2026-05-13 12:58:34
#include <iostream>
#include <thread>
#include <mutex>
#include<mutex>
using namespace std;

#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

class Singleton{
    private:
        static Singleton* instance;
        static mutex mtx;

        Singleton(){
            cout << "constructor is called" << endl;
        }
    public:
        static Singleton* getInstance(){
            lock_guard<mutex> mt(mtx);
            if(instance == nullptr) instance = new Singleton();
            return instance;
        }
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    Singleton* t1 = Singleton::getInstance();
    Singleton* t2 = Singleton::getInstance();

    cout << (t1 == t2) << endl;

}