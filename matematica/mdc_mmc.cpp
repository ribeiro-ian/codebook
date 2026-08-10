// O(logN); n = min(a,b)
// existe a função gdc()
int mdc(int a, int b) {
  if (b == 0) return a;
  return mdc(b, a % b);
}

// existe a função lcm()
int mmc(int a, int b) {
  return (a * b) / mdc(a, b);
}
