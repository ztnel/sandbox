#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct triangle_t
{
  int a;
  int b;
  int c;
  float area;
} triangle_t;

void sort_by_area(triangle_t *tr, int n)
{
  for (int i = 0; i < n; i++)
  {
    float p = (tr[i].a + tr[i].b + tr[i].c) / 2;
    tr[i].area = (float)sqrt(p * (p - tr[i].a) * (p - tr[i].b) * (p - tr[i].c));
  }
  // simple bubble sort
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (tr[j].area > tr[j+1].area) {
        triangle_t temp = tr[j];
        tr[j] = tr[j + 1];
        tr[j + 1] = temp;
      }
    }
  }
}

int main()
{
  int n;
  scanf("%d", &n);
  triangle_t *tr = malloc(n * sizeof(triangle_t));
  for (int i = 0; i < n; i++)
  {
    scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
    tr[i].area = 0.0f;
  }
  sort_by_area(tr, n);
  for (int i = 0; i < n; i++)
  {
    printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
  }
  free(tr);
  return 0;
}