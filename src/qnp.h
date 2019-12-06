#ifndef QNP_H
#define QNP_H

#include <cassert>
#include <iostream>
#include <string>
#include "problem.h"

namespace Reductions {

class QNP : public Problem {
  public:
    QNP(const std::string &name) : Problem(name) { }
    virtual ~QNP() { }

    static QNP* read(std::istream &is) {
        std::string name;
        is >> name;
        QNP *qnp = new QNP(name);
        Problem::read(is, *qnp);
        return qnp;
    }

    void PDDL_dump_domain(std::ostream &os) const override {
        throw std::runtime_error("error: PDDL dump for QNPs isn't supported.");
    }
    void PDDL_dump_problem(std::ostream &os) const override {
        throw std::runtime_error("error: PDDL dump for QNPs isn't supported.");
    }
};

}; // namespace Reductions

inline std::ostream& operator<<(std::ostream &os, const Reductions::QNP &qnp) {
    qnp.dump(os);
    return os;
}

#endif

