#include <stdio.h>

void update(int *a, int *b) {
  int sum = *a + *b;
  // cool hack (negative integers are 2's comp) but pointless since I can just
  // do *b - *a
  int diff = *a > *b ? *a - *b : ~(*a - *b) + 1;
  *a = sum;
  *b = diff;
}

int main() {
  int a, b;
  int *pa = &a, *pb = &b;

  scanf("%d %d", &a, &b);
  update(pa, pb);
  printf("%d\n%d", a, b);

  return 0;
}