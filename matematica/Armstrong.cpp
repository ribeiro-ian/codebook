// Numero n de D digitos onde soma dos digitos^D == n
vector<long long> armstrong; // fica ordenado

// O(C(D+9,9)) 
void generate(int MAXD = 18) {
    for (int D = 1; D <= MAXD; D++) {
        long long pw[10];
        for (int d = 0; d <= 9; d++) {
            pw[d] = 1;
            for (int i = 0; i < D; i++) pw[d] *= d;
        }

        vector<int> cnt(10, 0);
        auto rec = [&](int idx, int rem) {
            if (idx == 9) {
                cnt[9] = rem;
                long long sum = 0;
                for (int d = 0; d <= 9; d++) sum += (long long)cnt[d] * pw[d];

                string s = to_string(sum);
                if ((int)s.size() != D) return;

                int check[10] = {0};
                for (char c : s) check[c - '0']++;
                for (int d = 0; d <= 9; d++)
                    if (check[d] != cnt[d]) return;

                armstrong.push_back(sum);
                return;
            }
            for (int take = 0; take <= rem; take++) {
                cnt[idx] = take;
                rec(idx + 1, rem - take);
            }
        };
        rec(0, D);
    }
    sort(armstrong.begin(), armstrong.end());
}

// O(1)
bool is_armstrong(long long n) {
    return binary_search(armstrong.begin(), armstrong.end(), n);
}
// no main:
// generate();  // chamar 1 vez, cobre ate 18 digitos (long long)
