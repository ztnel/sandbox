#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct triangle_t
{
  int a;
  int b;
  int c;
} triangle_t;


void sort_by_area(triangle_t *tr, int n)
{
  double *arr = malloc(n * sizeof(double));
  if (arr == NULL) {
    return;
  }
  for (int i = 0; i < n; i++)
  {
    // WARNING: watchout for integer float division!
    float p = (tr[i].a + tr[i].b + tr[i].c) / 2.0f;
    arr[i] = sqrt(p * (p - (float)tr[i].a) * (p - (float)tr[i].b) * (p - (float)tr[i].c));
    printf("Triangle (%d %d %d) (%.5f) -> %.5f\n",tr[i].a, tr[i].b, tr[i].c, p, arr[i]);
  }
  // simple bubble sort
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j+1]) {
        double tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
        triangle_t temp = tr[j];
        tr[j] = tr[j + 1];
        tr[j + 1] = temp;
      }
    }
  }
  printf("Sorted Areas:\n");
  for (int i = 0; i < n; i++)
  {
    printf("[%d] %.2f\n", i, arr[i]);
  }
  free(arr);
}

int main()
{
  int n;
  scanf("%d", &n);
  triangle_t *tr = malloc(n * sizeof(triangle_t));
  for (int i = 0; i < n; i++)
  {
    scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
  }
  sort_by_area(tr, n);
  for (int i = 0; i < n; i++)
  {
    printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
  }
  free(tr);
  return 0;
}