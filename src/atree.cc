#include "atree.hh"

using namespace std;

ATree::ATree(string label) :
  _label(label)
{}

ATree* ATree::add(ATree* child) {
  _children.push_back(child);
  return this;
}

void ATree::write(ostream* os) {
  write(os, 0);
}

void ATree::write(ostream* os, int depth) {
  string indent;
  for (int i = 0; i < depth; i++) {
    indent += " ";
  }
  (*os) << indent << _label << endl;
  vector<ATree*>::const_iterator i, n;
  for (i = _children.begin(), n = _children.end(); i != n; i++) {
    (*i)->write(os, depth + 2);
  }
}

