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

int __crow_f5();
int test_f5() {
  return expect(34, __crow_f5(9));
}

int __crow_f6();
int test_f6() {
  return expect(9, __crow_f6(4, 6));
}

int __crow_add(int a, int b) {
  return a + b;
}

int __crow_sub(int a, int b) {
  return a - b;
}

int __crow_equal(int a, int b) {
  return a == b;
}

int (*funs[])() = {
  test_f1,
  test_f2,
  test_f3,
  test_f4,
  test_f5,
  test_f6,
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
