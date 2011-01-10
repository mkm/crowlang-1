#include "tuple.h"
#include <stdlib.h>
#include <stdio.h>

Tuple tuple(int length) {
  Tuple t = malloc((length + 2) * sizeof(int));
  t[0] = TUPLE_MAGIC;
  t[1] = length;
  int i;
  for (i = 0; i < length; i++) {
    t[i + 2] = 0;
  }
  return t;
}

int isValidTuple(Tuple t) {
  return t[0] == TUPLE_MAGIC;
}

void assertValidTuple(Tuple t) {
  if (!isValidTuple(t)) {
    printf("Invalid tuple\n");
    exit(1);
  }
}

int isValidIndex(Tuple t, int i) {
  return 0 <= i && i < t[1];
}

void assertValidIndex(Tuple t, int i) {
  if (!isValidIndex(t, i)) {
    printf("Invalid index in tuple\n");
    exit(1);
  }
}

int getFieldV(Tuple t, int i) {
  assertValidTuple(t);
  assertValidIndex(t, i);
  return t[i + 2];
}

Tuple getFieldT(Tuple t, int i) {
  return (Tuple)getFieldV(t, i);
}

void setFieldV(Tuple t, int i, int v) {
  assertValidTuple(t);
  assertValidIndex(t, i);
  t[i + 2] = v;
}

void setFieldT(Tuple t, int i, Tuple v) {
  setFieldV(t, i, (int)v);
}

Tuple __crow_tuple(int length) {
  return tuple(length);
}

Tuple __crow_tuple1(int a) {
  Tuple t = tuple(1);
  setFieldV(t, 0, a);
  return t;
}

Tuple __crow_tuple2(int a, int b) {
  Tuple t = tuple(2);
  setFieldV(t, 0, a);
  setFieldV(t, 1, b);
  return t;
}

Tuple __crow_tuple3(int a, int b, int c) {
  Tuple t = tuple(3);
  setFieldV(t, 0, a);
  setFieldV(t, 1, b);
  setFieldV(t, 2, c);
  return t;
}

int __crow_get(Tuple t, int i) {
  return getFieldV(t, i);
}

int __crow_set(Tuple t, int i, int v) {
  setFieldV(t, i, v);
  return 0;
}
