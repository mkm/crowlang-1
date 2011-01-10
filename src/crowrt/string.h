#ifndef _STRING_H_
#define _STRING_H_

#include "tuple.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

  size_t listLength(Tuple);
  char* listToString(Tuple);
  Tuple stringToList(const char*);
  
#ifdef __cplusplus
}
#endif
  
#endif
