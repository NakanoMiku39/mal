#include "types.hpp"

void pr_str(MalListType* m) {
  for(auto &i: m->MalList) {
    i->dump();
  }
}
