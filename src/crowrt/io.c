#include "tuple.h"
#include <unistd.h>

int __crow_stdin() {
  return STDIN_FILENO;
}

int __crow_stdout() {
  return STDOUT_FILENO;
}

int __crow_stderr() {
  return STDERR_FILENO;
}

Tuple __crow_readFile(int fd) {
  char c;
  if (read(fd, &c, 1)) {
    Tuple t = tuple(2);
    setFieldV(t, 0, c);
    setFieldT(t, 1, __crow_readFile(fd));
    return t;
  } else {
    return 0;
  }
}

int __crow_writeFile(int fd, Tuple t) {
  if (t) {
    char c = getFieldV(t, 0);
    write(fd, &c, 1);
    return __crow_writeFile(fd, getFieldT(t, 1));
  } else {
    return 0;
  }
}
