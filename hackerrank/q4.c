#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *s;
  s = malloc(1024 * sizeof(char));
  scanf("%[^\n]", s);
  s = realloc(s, strlen(s) + 1);
  // NOTE: we do not need to iterate through to the null character
  for (int i = 0; i <= strlen(s); i++) {
    // NOTE: watchout! " " is not the same as ' '. " " represents a string
    // literal and ' ' represents a character literal
    s[i] = (s[i] == ' ') ? '\n' : s[i];
  }
  printf("%s", s);
  return 0;
}