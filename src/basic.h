#ifndef BASIC_H
#define BASIC_H

#include <string>

namespace Reductions {

inline std::string PDDL_name(const std::string &name) {
    size_t n;
    std::string copy(name);
    for( size_t n = copy.find('('); n != std::string::npos; n = copy.find('(') )
        copy.replace(n, 1, "_");
    for( size_t n = copy.find(','); n != std::string::npos; n = copy.find(',') )
        copy.replace(n, 1, "_");
    for( size_t n = copy.find('.'); n != std::string::npos; n = copy.find('.') )
        copy.replace(n, 1, "_");
    for( size_t n = copy.find(')'); n != std::string::npos; n = copy.find(')') )
        copy.replace(n, 1, "");
    return copy;
}

inline std::string PDDL_zero(const std::string &name, bool neg = false) {
    std::string zero;
    if( neg ) zero += std::string("(not ");
    zero += std::string("(zero ") + PDDL_name(name) + ")";
    if( neg ) zero += std::string(")");
    return zero;
}

};

#endif

