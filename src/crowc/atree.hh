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
  template<class T>
  ATree* add(std::vector<T>);
  void write(std::ostream*);
  void write(std::ostream*, int);
};

template<class T>
ATree* ATree::add(std::vector<T> items) {
  typename std::vector<T>::const_iterator i, n;
  for (i = items.begin(), n = items.end(); i != n; i++) {
    add((*i)->atree());
  }
  return this;
}

#endif

