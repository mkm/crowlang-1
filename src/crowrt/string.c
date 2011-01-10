#include "string.h"

size_t listLength(Tuple t) {
  if (t) {
    return 1 + listLength(getFieldT(t, 1));
  } else {
    return 0;
  }
}

char* listToString(Tuple t) {
  size_t len = listLength(t);
  char* s = malloc(len + 1);
  char* p = s;
  while (t) {
    *p = getFieldV(t, 0);
    p++;
    t = getFieldT(t, 1);
  }
  *p = 0;
  return s;
}

Tuple stringToList(const char* s) {
  if (*s) {
    Tuple t = tuple(2);
    setFieldV(t, 0, *s);
    setFieldT(t, 1, stringToList(s + 1));
    return t;
  } else {
    return 0;
  }
}

