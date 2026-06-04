#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int n;
  int *arr;
  int sum = 0;
  scanf("%d", &n);
  arr = malloc(n * sizeof(int));
  if (arr == NULL) {
    return 1;
  }
  for (int i = 0; i <= n - 1; i++) {
    scanf("%d", arr + i);
  }
  for (int i = 0; i <= n - 1; i++) {
    sum += arr[i];
  }
  printf("%d", sum);
  free(arr);
  return 0;
}