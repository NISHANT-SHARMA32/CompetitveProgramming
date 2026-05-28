// Author: Nishant Sharma
// Created: 2026-05-06 21:44:39
#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};


class Talkable{
    public:
        virtual void talk() = 0;  
        ~Talkable() {}      
};

class normalTalk : public Talkable{
    public:
        void talk() override{
            cout << "Normally Talking" << endl;
        }
};

class NoTalk : public Talkable{
    public:
        void talk() override{
            cout << "NO Talking" << endl;
        }
};

class Walkable{
    public:
        virtual void Walk() = 0;        
};

class normalWalk : public Walkable{
    public:
        void Walk() override{
            cout << "Normally Walking" << endl;
        }
};

class NoWalk : public Walkable{
    public:
        void Walk() override{
            cout << "NO Walking" << endl;
        }
};

class Flyable{
    public:
        virtual void fly() = 0;        
};

class normalFly : public Flyable{
    public:
        void fly() override{
            cout << "Normally fly" << endl;
        }
};

class NoFly : public Flyable{
    public:
        void fly() override{
            cout << "NO fly" << endl;
        }
};

class Robot{
    private:    
        Talkable* talkablerobot;
        Walkable* walkablerobot;
        Flyable* flyablerobot;
    
    public:
        Robot(Talkable* t, Walkable* w, Flyable* f){
            this->talkablerobot  = t;
            this->walkablerobot = w;
            this->flyablerobot = f;
        }

        void talk(){
            talkablerobot->talk();
        }

        void walk(){
            walkablerobot->Walk();
        }

        void fly(){
            flyablerobot->fly();
        }

        virtual void projection() = 0;
};

class CompanionRobot : public Robot {
public:
    CompanionRobot(Walkable* w, Talkable* t, Flyable* f)
        : Robot(t, w, f) {}

    void projection() override {
        cout << "Displaying friendly companion features..." << endl;
    }
};


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);


    Robot *robot1 = new CompanionRobot(new normalWalk(), new normalTalk(), new NoFly());
    robot1->walk();
    robot1->talk();
    robot1->fly();
    robot1->projection();

}