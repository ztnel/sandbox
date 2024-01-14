
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIST_LEN (int)10

// REVIEW: These string to integer tricks are awesome remember these!
static inline int is_digit(char c) { return (c >= '0' && c <= '9') ? 1 : 0; }
static inline int char_to_digit(char c) { return (c - '0'); }

void print_array(int *arr, size_t size) {
  for (int i = 0; i <= size - 1; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main() {
  char *s;
  s = malloc(1024 * sizeof(char));
  scanf("%[^\n]%*c", s);
  // resize s to only provision memory for input string
  s = realloc(s, strlen(s) + 1);
  // NOTE: initializes all elements to 0 (zero initialization shorthand)
  int dist[DIST_LEN] = {0};
  // storing this value here to avoid calling strlen on each loop iteration
  int len = strlen(s);
  for (size_t i = 0; i <= len; i++) {
    if (is_digit(s[i])) {
      // WARNING: atoi expects a null terminated string so just passing s[i]
      // will iterate until a non digit is found.
      // A better solution does not use atoi and eliminates the need for a null
      // terminated string
      dist[char_to_digit(s[i])] += 1;
    };
  }
  print_array(dist, DIST_LEN);
  return 0;
}
