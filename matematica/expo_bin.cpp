// a^b O(logN)
int bin_pow(int a, int b, const int MOD = 1e9 + 7) {
  a %= MOD;
  int res = 1;

  while (b) {
    if (b % 2) res = res * a % MOD;
    a = a * a % MOD;
    b /= 2;
  }
  return res;
}

int inverso(int a, int MOD) {
  bin_pow(a, MOD - 2); // MOD deve ser primo
}
