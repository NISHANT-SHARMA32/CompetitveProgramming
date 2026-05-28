// Author: Nishant Sharma
// Created: 2026-05-13 09:52:20
#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

class Burger{
    public:
        virtual void prepare() = 0;
        ~Burger(){};
};

class BasicBurger : public Burger{
    public:
        void prepare() override{
            cout << "Preparing Basic Burger with bun, patty and sause" << endl;
        }
};

class ClassicBurger : public Burger{
    public:
        void prepare() override{
            cout << "Preparing Classic Burger with bun, patty and chessy dip sause" << endl;
        }
};

class PremiumBurger : public Burger{
    public:
        void prepare() override{
            cout << "Preparing Premium Burger with sado bread, patty and chessy dip sause" << endl;
        }
};

class BurgerFactory{
    public:
        Burger* CreateBurger(string type){
            if(type == "simple") return new BasicBurger();
            else if(type == "classic") return new ClassicBurger();
            else if(type == "premium") return new PremiumBurger();
            else cout << "this is not a valid burger type" << endl; 
        }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string type = "premium";

    BurgerFactory* model = new BurgerFactory();
    Burger* maker = model->CreateBurger(type);
    maker->prepare();
}