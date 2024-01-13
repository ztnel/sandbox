
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int int1 = 0;
  int int2 = 0;
  float float1 = 0.0;
  float float2 = 0.0;

  scanf("%i %i", &int1, &int2);
  scanf("%f %f", &float1, &float2);

  printf("%i %i\n", int1 + int2, int1 - int2);
  printf("%.1f %.1f\n", float1 + float2, float1 - float2);

  return 0;
}
