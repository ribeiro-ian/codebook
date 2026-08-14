// O(√n)

// divide array em √n
// blocos de tamanho √n

#include <bits/stdc++.h>
using namespace std;
int n, m = sqrt(n) + 1;
vector<int> a(n), b(m, 0);

// build
for (int i = 0; i < n; ++i)
    b[i / m] += a[i]; // qlqr operacao

// queries
int query(int l, int r) {
    int ans = 0;
    for (int i = l; r <= n;) {
        // completamente coberto
        if (i % m == 0 && i + m - 1 <= r) {
            ans += b[i / m];
            i += m; // prox bloco
        }
        else {
            ans += a[i++];
        }
    }
    return ans;
}

// ordena primeiro pelo id do bloco
bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first / m != b.first / m)
        return a.first < b.first;
    return a.second < b.second;
}
