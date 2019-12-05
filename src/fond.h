#ifndef FOND_H
#define FOND_H

#include <cassert>
#include <iostream>
#include <string>
#include "problem.h"

namespace Reductions {

class FOND : public Problem {
  public:
    FOND(const std::string &name) : Problem(name) { }
    virtual ~FOND() { }
};

}; // namespace Reductions

inline std::ostream& operator<<(std::ostream &os, const Reductions::FOND &fond) {
    fond.dump(os);
    return os;
}

#endif

