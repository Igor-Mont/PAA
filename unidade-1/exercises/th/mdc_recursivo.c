#include <stdlib.h>
#include <stdio.h>

int mdc (int m, int n) {
  if (n == 0) return m;
  int r = m % n;

  return mdc(n, m % n);
}

int main() {
  int m, n;
  scanf("%d", &m);
  scanf("%d", &n);

  int result = mdc(m, n);
  printf("M.D.C. (%d, %d) eh: %d", m, n, result);

  return 0;
}