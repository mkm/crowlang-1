#include "tuple.h"
#include "string.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int __crow_stdin() {
  return STDIN_FILENO;
}

int __crow_stdout() {
  return STDOUT_FILENO;
}

int __crow_stderr() {
  return STDERR_FILENO;
}

int __crow_openFile(Tuple t) {
  char* s = listToString(t);
  int fd = open(s, O_RDWR | O_CREAT);
  if (fd == -1) {
    printf("Could not open file\n");
    exit(2);
  }
  return fd;
}

int __crow_closeFile(int fd) {
  close(fd);
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
