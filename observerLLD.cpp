/*
Author: Nishant Sharma
Created: 2026-05-27 16:47:05
*/
#include <bits/stdc++.h>
using namespace std;

// ========== DEBUGGER ========== //
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }
#include <queue>
#include <stack>
#include <bitset>
template<typename T> ostream& operator<<(ostream &os, queue<T> q) { os << "queue{"; string sep; while (!q.empty()) os << sep << q.front(), q.pop(), sep = ", "; return os << "}"; }
template<typename T> ostream& operator<<(ostream &os, stack<T> s) { os << "stack{"; string sep; while (!s.empty()) os << sep << s.top(), s.pop(), sep = ", "; return os << "}"; }
template<typename T> ostream& operator<<(ostream &os, priority_queue<T> pq) { os << "pq{"; string sep; vector<T> v; while (!pq.empty()) v.push_back(pq.top()), pq.pop(); reverse(v.begin(), v.end()); for (auto x : v) os << sep << x, sep = ", "; return os << "}"; }
template<size_t N> ostream& operator<<(ostream &os, bitset<N> b) { os << b.to_string(); return os; }

void debug_out() { cerr << endl; }
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) { cerr << ' ' << H; debug_out(T...); }
#define LOCAL
#ifdef LOCAL
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif
// ========== DEBUGGER END ========== //

#define endl '\n'
#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

class Isubscriber{
    public:
        virtual void update() = 0;
        virtual ~Isubscriber(){}
};

class IChannel{
    public:
        virtual void subscribe(Isubscriber* subscriber) = 0;
        virtual void Unsubscribe(Isubscriber* subscriber) = 0;
        virtual void notify() = 0;
        virtual ~IChannel(){}
};



class Channel : public IChannel{
    private:
        vector<Isubscriber*> list;
        string name;
        string latestVideo;

    public:
        Channel(const string &name){
            this->name = name;
        }

        void subscribe(Isubscriber* agent) override{
            if(find(list.begin(), list.end(), agent) == list.end()){
                list.push_back(agent);
            }
        }

        void Unsubscribe(Isubscriber* agent) override{
            auto it = find(list.begin(), list.end(), agent);
            if(it != list.end()){
                list.erase(it);
            }
        }

        
        void notify() override{
            for(auto it : list){
                it->update();
            }
        }

        void uploadVideo(const string& title) {
            latestVideo = title;
            cout << "\n[" << name << " uploaded \"" << title << "\"]\n";
            notify();
        }

        string getVideoData() {
            return "\nCheckout our new Video : " + latestVideo + "\n";
        }
};

class subscriber : public Isubscriber{
    private:
        string name;
        Channel* channel;
    public:
        subscriber(const string& name, Channel* channel){
            this->name = name;
            this->channel = channel;
        }
        
        void update() override {
            cout << "Hey " << name << "," << this->channel->getVideoData();
        }
};

void solve() {
    Channel* channel = new Channel("CoderArmy");

    subscriber* subs1 = new subscriber("Varun", channel);
    subscriber* subs2 = new subscriber("Tarun", channel);

    channel->subscribe(subs1);
    channel->subscribe(subs2);

    channel->uploadVideo("Observer Pattern Tutorial");
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        solve();
    }
}