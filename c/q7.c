/**
 * @file q7.c
 * @author ztnel (christian911@sympatico.ca)
 * @brief Array reversal (highest memory efficiency)
 * @version 0.1
 * @date 2024-01
 *
 * @copyright Copyright © 2024 Christian Sargusingh
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int num, *arr, i;
  scanf("%d", &num);
  arr = (int *)malloc(num * sizeof(int));
  if (arr == NULL) {
    return 1;
  }
  for (i = 0; i < num; i++) {
    scanf("%d", arr + i);
  }

  int *start = arr;
  int *end = arr + (num - 1);
  int temp;
  while (start < end) {
    temp = *start;
    *start = *end;
    *end = temp;
    end--;
    start++;
  }

  for (i = 0; i < num; i++) printf("%d ", *(arr + i));
  free(arr);
  return 0;
}