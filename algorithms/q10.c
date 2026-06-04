#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


void calculate_the_maximum(int n, int k) {
  int max_xor = 0;
  int max_or = 0;
  int max_and = 0;
  for (int i = 1; i < n; i++) {
    for (int j = i+1; j <= n; j++) {
      int tmp = i | j;
      if (tmp > max_or && tmp < k) {
        max_or = tmp;
      }
      tmp = i ^ j;
      if (tmp > max_xor && tmp < k) {
        max_xor = tmp;
      }
      tmp = i & j;
      if (tmp > max_and && tmp < k) {
        max_and = tmp;
      }
    }
  }
  printf("%d\n%d\n%d", max_and, max_or, max_xor);
}

int main() {
    int n, k;
  
    scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);
    return 0;
}
