#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

class SGTree {
private:
    vector<int> seg;

public:
    SGTree(int n) {
        seg.resize(4 * n);
    }

    void build(int idx, int low, int high, vector<int>& arr, int orr) {
        if (low == high) {
            seg[idx] = arr[low];
            return;
        }

        int mid = (low + high) >> 1;
        build(2 * idx + 1, low, mid, arr, !orr);
        build(2 * idx + 2, mid + 1, high, arr, !orr);

        if (orr)
            seg[idx] = seg[2 * idx + 1] | seg[2 * idx + 2];
        else
            seg[idx] = seg[2 * idx + 1] ^ seg[2 * idx + 2];
    }

    void update(int idx, int low, int high, int pos, int val, vector<int>& arr, int orr) {
        if (low == high) {
            arr[pos] = val;
            seg[idx] = val;
            return;
        }

        int mid = (low + high) >> 1;
        if (pos <= mid)
            update(2 * idx + 1, low, mid, pos, val, arr, !orr);
        else
            update(2 * idx + 2, mid + 1, high, pos, val, arr, !orr);

        if (orr)
            seg[idx] = seg[2 * idx + 1] | seg[2 * idx + 2];
        else
            seg[idx] = seg[2 * idx + 1] ^ seg[2 * idx + 2];
    }

    int root() {
        return seg[0];
    }
};

void solve() {
    int n, m; cin >> n >> m;
    int size = (1 << n);
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) cin >> arr[i];

    SGTree sg(4*size);
    sg.build(0, 0, size - 1, arr, (n % 2 == 0));

    while (m--) {
        int p, b;
        cin >> p >> b;
        --p;
        sg.update(0, 0, size - 1, p, b, arr, (n % 2 == 0));
        cout << sg.root() << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
