#ifndef _ATREE_H_
#define _ATREE_H_

#include <string>
#include <ostream>
#include <vector>

class ATree {
private:
  std::string _label;
  std::vector<ATree*> _children;

public:
  ATree(std::string);
  ATree* add(ATree*);
  void write(std::ostream*);
  void write(std::ostream*, int);
};

#endif

