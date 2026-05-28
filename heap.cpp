/*
Author: Nishant Sharma
Created: 2025-07-20 17:16:17
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

class heap{
    private:
        vector<int> arr;
        int size;
    public: 
        heap(int n){
            arr.resize(n);
            size = 0;
            arr[0] = -1;   
        }

        void insert(int val){
            size += 1;
            int index = size;

            arr[index] = val;

            while(index > 1){
                int parent = index / 2;

                if(arr[parent] < arr[index]){
                    swap(arr[parent], arr[index]);
                    index = parent;
                } 
                else return;
            }
        }

        void deletion(){
            arr[1] = arr[size];
            size -= 1;

            int index = 1;

            while(index <= size){
                int left = 2 * index, right = 2 * index + 1, largest = index;

                if(left <= size and arr[left] > arr[largest]){
                    largest = left;
                }
                if(right <= size and arr[right] > arr[largest]){
                    largest = right;
                }
                
                if(largest != index){
                    swap(arr[largest],arr[index]);
                    index = largest;
                }
                else return;
            }
        }

        void print(){
            for(int i = 1; i <= size; ++i){
                cout << arr[i] << " ";
            } cout << endl;
        }
};

void heapify(int n, vector<int> &arr, int i){
    int left = 2 * i, right = 2 * i + 1, largest = i;

    if(left <= n and arr[left] > arr[largest]){
        largest = left;
    }
    if(right <= n and arr[right] > arr[largest]){
        largest = right;
    }
    
    if(largest != i){
        swap(arr[largest],arr[i]);
        heapify(n,arr,largest);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<int> arr = {-1, 1, 4, 54, 45, 32, 2, 23, 44343};  // 1-based indexing

    int n = arr.size() - 1;  // actual number of elements

    for(int i = n / 2; i >= 1; i--) {
        heapify(n, arr, i);
    }

    debug(arr);
}