// Author: Nishant Sharma
// Created: 2026-05-13 10:22:55
#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

class burger{
    public:
        virtual void prepare() = 0;
        ~burger(){}
};

class basicBurger : public burger{
    public:
        void prepare() override{
            cout << "basic burger" << endl;
        }
};

class stdBurger : public burger{
    public:
        void prepare() override{
            cout << "std burger" << endl;
        }
};
class premiumBurger : public burger{
    public:
        void prepare() override{
            cout << "premium burger" << endl;
        }
};

class basicWheatBurger : public burger{
    public:
        void prepare() override{
            cout << "basic Wheat burger" << endl;
        }
};
class stdWheatBurger : public burger{
    public:
        void prepare() override{
            cout << "standard wheat burger" << endl;
        }
};

class premiumWheatBurger : public burger{
    public:
        void prepare() override{
            cout << "premium wheat burger" << endl;
        }
};

class garlicBread{
    public:
        
}

class BurgerFactory{
    public:
        virtual burger* CreateBurger(string type) = 0;
        virtual
};

class singhBurger : public BurgerFactory{
    public:
        burger* CreateBurger(string type){
            if(type == "simple") return new basicBurger();
            else if(type == "std") return new stdBurger();
            else if(type == "premium") return new premiumBurger();
        }
};

class kingBurger : public BurgerFactory{
    public:
        burger* CreateBurger(string type){
            if(type == "simple") return new basicWheatBurger();
            else if(type == "std") return new stdWheatBurger();
            else if(type == "premium") return new premiumWheatBurger();
        }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);


    BurgerFactory* model = new singhBurger();
    burger* maker = model->CreateBurger("premium");
    maker->prepare();

    return 0;
}