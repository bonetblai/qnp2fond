#ifndef FEATURE_H
#define FEATURE_H

#include <iostream>
#include <string>
#include "basic.h"

namespace Reductions {

class Feature {
  protected:
    const std::string name_;
    const bool numeric_;
    const bool sanitized_;

  public:
    Feature(const std::string &name, bool numeric, bool sanitized = false)
      : name_(name), numeric_(numeric), sanitized_(sanitized) {
    }
    const std::string& name() const { return name_; }
    const std::string PDDL_name(bool neg = false) const {
        std::string name;
        if( neg ) name += "(not ";
        name += sanitized_ ? name_ : std::string("(") + Reductions::PDDL_name(name_) + ")";
        if( neg ) name += ")";
        return name;
    }
    bool is_numeric() const { return numeric_; }
    bool is_boolean() const { return !is_numeric(); }
    static Feature* read(std::istream &is) {
        std::string name;
        bool numeric;
        is >> name >> numeric;
        return new Feature(name, numeric);
    }
    void dump(std::ostream &os) const {
        os << name_;
    }
};

}; // namespace Reductions

inline std::ostream& operator<<(std::ostream &os, const Reductions::Feature &feature) {
    feature.dump(os);
    return os;
}

#endif

