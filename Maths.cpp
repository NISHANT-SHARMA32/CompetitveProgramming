#include <bits/stdc++.h>
using namespace std;
 
#define endl '\n'
#define ll long long
#define ld long double 
#define Yes cout << "YES" << endl;
#define No cout << "NO" << endl;


const int MOD = 1e9 + 7;

//leaning towards the changing side that means right side so we have to take ceil  + 1 is required

//findind the last index of target
int binary(vector<int> a, int target){
  int low = 0, high = a.size() - 1;
  while(low < high){
    int mid = (low + high + 1) / 2;

    if(a[mid] <= target) low = mid;
    else high = mid - 1;
  }
  return a[low] == target ? low : -1;
}

// finding the first index of target
int binary1(vector<int> a, int target){
  int low = 0, high = a.size() - 1;
  while(low < high){
    int mid = (low + high) / 2;

    if(a[mid] >= target) high = mid;
    else low = mid - 1;
  }
  return a[low] == target ? low : -1;
}

ll binaryExponetiation(ll a, ll b){
  if(b == 0) return 1;
  ll half = binaryExponetiation(a,b/2);
  if(b&1) return a * 1ll * half * half;
  return 1ll * half * half;
}

int gcd(int a, int b){
  return b ? gcd(b,a%b) : a;
}

int lcm(int a, int b){
  return (a*b) / gcd(a,b); 
}

vector<bool> sieve(int n){
	vector<bool> prime(n,1);
	prime[0] = prime[1] = 0;
	for(int i = 2; i * i < n; ++i){
			if(prime[i]){
					for(int j = i*i; j < n; ++j) prime[j] = 0;
			}
	}
	return prime;
}

vector<int> createSPF(){
	vector<int> spf(20,-1);
	for(int i = 2; i < 20; ++i){
			if(spf[i] == -1){
				for(int j = i; j < 20; j +=i) if(spf[j] == -1) spf[j] = i;
			}
		return  spf;
	}
}	

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cout << gcd(14,21);
    return 0;
}

  
