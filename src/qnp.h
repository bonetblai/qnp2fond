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

    bool check(std::ostream &os) const {
        for( size_t i = 0; i < num_actions(); ++i ) {
            if( !action(i).check(os) )
                return false;
        }

        for( size_t i = 0; i < init_.size(); ++i ) {
            const Feature *f = init_[i].first;
            if( !is_feature(f) ) {
                os << "error: inexistent feature " << f->name() << " in init" << std::endl;
                return false;
            }
        }

        for( size_t i = 0; i < goal_.size(); ++i ) {
            const Feature *f = goal_[i].first;
            if( !is_feature(f) ) {
                os << "error: inexistent feature " << f->name() << " in goal" << std::endl;
                return false;
            }
        }

        return true;
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

