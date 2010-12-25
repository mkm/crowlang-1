#ifndef _TUPLE_H_
#define _TUPLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TUPLE_MAGIC 0x4E78F2A6
  
  typedef int* Tuple;
  
  Tuple tuple(int);
  int isValidTuple(Tuple);
  void assertValidTuplr(Tuple);
  int isValidIndex(Tuple, int);
  void assertValidIndex(Tuple, int);
  int getFieldV(Tuple, int);
  Tuple getFieldT(Tuple, int);
  void setFieldV(Tuple, int, int);
  void setFieldT(Tuple, int, Tuple);

#ifdef __cplusplus
}
#endif

#endif
