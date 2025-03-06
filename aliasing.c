
void do_arithmetic(int *i, float *f) {
  *i += 1;
  *f += 0.5;
  *i += 1;
}

int main(void) {
  int i = 0;
  int f = 1;
  do_arithmetic(&i, &f);
}
