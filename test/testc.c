#include <stdio.h>

int expect(int wanted, int got) {
  if (wanted == got) {
    return 1;
  } else {
    printf("Wanted %i, got %i\n", wanted, got);
    return 0;
  }
}

int __crow_f1();
int test_f1() {
  return expect(42, __crow_f1());
}

int __crow_f2();
int test_f2() {
  return expect(3, __crow_f2());
}

int __crow_f3();
int test_f3() {
  return expect(2, __crow_f3());
}

int __crow_f4();
int test_f4() {
  return expect(8, __crow_f4());
}

int (*funs[])() = {
  test_f1,
  //test_f2,
  //test_f3,
  test_f4,
  NULL
};

int main() {
  int i;
  for (i = 0; funs[i] != NULL; i++) {
    printf("Test %i\n", i);
    if ((*funs[i])()) {
    } else {
      printf("Fail\n");
      return 1;
    }
  }
  return 0;
}
