#ifndef PROBLEM_H
#define PROBLEM_H

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

#include "basic.h"
#include "action.h"
#include "feature.h"
#include "problem.h"

namespace Reductions {

// forward ref
namespace Translations {
  class Translation;
};

struct Predicate {
    const std::string name_;
    std::vector<std::pair<std::string, std::string> > args_;
    Predicate(const std::string &name) : name_(name) { }
    Predicate(const std::string &name, const std::vector<std::pair<std::string, std::string> > args) : name_(name), args_(args) { }
    std::string str() const {
        std::stringstream ss;
        ss << "(" << name_;
        for( size_t i = 0; i < args_.size(); ++i )
            ss << " " << args_.at(i).first << " - " << args_.at(i).second;
        ss << ")";
        return ss.str();
    }
};

// abstract class, instantiated as a QNP or FOND
class Problem {
  protected:
    const std::string name_;

    // types, constants, and predicates
    std::vector<std::string> types_;
    std::vector<std::pair<std::string, std::vector<std::string> > > constants_;
    std::vector<const Predicate*> predicates_;

    // features, either boolean or numeric
    std::vector<const Feature*> features_;
    std::vector<const Feature*> numeric_features_;
    std::vector<const Feature*> boolean_features_;
    std::map<std::string, const Feature*> feature_map_;

    // standard elements
    std::vector<std::pair<const Feature*, bool> > init_;
    std::vector<std::pair<const Feature*, bool> > goal_;
    std::vector<const Action*> actions_;

    // meta info
    std::set<const Feature*> incremented_features_;
    std::set<const Feature*> decremented_features_;

  public:
    Problem(const std::string &name) : name_(name) { }
    virtual ~Problem() {
        for( size_t i = 0; i < actions_.size(); ++i )
            delete actions_[i];
        for( size_t i = 0; i < features_.size(); ++i )
            delete features_[i];
    }

    const std::string& name() const { return name_; }
    const std::set<const Feature*>& incremented_features() const { return incremented_features_; }
    const std::set<const Feature*>& decremented_features() const { return decremented_features_; }

    // types
    int num_types() const {
        return types_.size();
    }
    const std::string& type(int i) const {
        return types_.at(i);
    }
    void add_type(const std::string &name) {
        types_.push_back(name);
    }

    // constants
    int num_constants() const {
        return constants_.size();
    }
    const std::pair<std::string, std::vector<std::string> >& constant(int i) const {
        return constants_.at(i);
    }
    void add_constants(const std::string &type, const std::vector<std::string> &items) {
        constants_.emplace_back(type, items);
    }

    // predicates
    int num_predicates() const {
        return predicates_.size();
    }
    const Predicate& predicate(int i) const {
        return *predicates_.at(i);
    }
    void add_predicate(const std::string &name) {
        predicates_.push_back(new Predicate(name));
    }
    void add_predicate(const std::string &name, const std::vector<std::pair<std::string, std::string> > &args) {
        predicates_.push_back(new Predicate(name, args));
    }

    // features
    int num_features() const {
        return features_.size();
    }
    const Feature& feature(int i) const {
        return *features_.at(i);
    }
    const Feature* feature(const std::string &name) const {
        std::map<std::string, const Feature*>::const_iterator it = feature_map_.find(name);
        return it == feature_map_.end() ? nullptr : it->second;
    }
    const std::map<std::string, const Feature*>& feature_map() const {
        return feature_map_;
    }
    void add_feature(const Feature *feature) {
        assert(feature != nullptr);
        assert(feature_map_.find(feature->name()) == feature_map_.end());
        features_.push_back(feature);
        if( feature->is_numeric() )
            numeric_features_.push_back(feature);
        else
            boolean_features_.push_back(feature);
        feature_map_.insert(std::make_pair(feature->name(), features_.back()));
    }

    bool is_numeric_feature(const Feature *f) const {
        for( size_t i = 0; i < numeric_features_.size(); ++i ) {
            if( numeric_features_[i] == f )
                return true;
        }
        return false;
    }
    bool is_boolean_feature(const Feature *f) const {
        for( size_t i = 0; i < boolean_features_.size(); ++i ) {
            if( boolean_features_[i] == f )
                return true;
        }
        return false;
    }
    bool is_feature(const Feature *f) const {
        return is_numeric_feature(f) || is_boolean_feature(f);
    }

    // numerical and boolean features
    int num_numeric_features() const {
        return numeric_features_.size();
    }
    const Feature& numeric_feature(int i) const {
        return *numeric_features_.at(i);
    }
    int num_boolean_features() const {
        return boolean_features_.size();
    }
    const Feature& boolean_feature(int i) const {
        return *boolean_features_.at(i);
    }

    // init
    int num_inits() const {
        return init_.size();
    }
    std::pair<const Feature*, bool> init(int i) const {
        return init_.at(i);
    }
    void add_init(const Feature *feature, bool value) {
        init_.emplace_back(feature, value);
    }

    // goal
    int num_goals() const {
        return goal_.size();
    }
    std::pair<const Feature*, bool> goal(int i) const {
        return goal_.at(i);
    }
    void add_goal(const Feature *feature, bool value) {
        goal_.emplace_back(feature, value);
    }

    // actions
    int num_actions() const {
        return actions_.size();
    }
    const Action& action(int i) const {
        return *actions_.at(i);
    }
    void add_action(const Action *action) {
        assert(action != nullptr);
        actions_.push_back(action);
    }

    // input
    static void read(std::istream &is, Problem &p) {
        // features
        int num_features;
        is >> num_features;
        for( int i = 0; i < num_features; ++i ) {
            Feature *feature = Feature::read(is);
            p.add_feature(feature);
        }

        // init
        int num_init;
        is >> num_init;
        for( int i = 0; i < num_init; ++i ) {
            std::string name;
            bool value;
            is >> name >> value;
            std::map<std::string, const Feature*>::const_iterator it = p.feature_map().find(name);
            if( it == p.feature_map().end() )
                std::cout << "error: inexistent feature '" << name << "'" << std::endl;
            else
                p.add_init(it->second, value);
        }

        // goal
        int num_goal;
        is >> num_goal;
        for( int i = 0; i < num_goal; ++i ) {
            std::string name;
            bool value;
            is >> name >> value;
            std::map<std::string, const Feature*>::const_iterator it = p.feature_map().find(name);
            if( it == p.feature_map().end() )
                std::cout << "error: inexistent feature '" << name << "'" << std::endl;
            else
                p.add_goal(it->second, value);
        }

        // actions
        int num_actions;
        is >> num_actions;
        for( int i = 0; i < num_actions; ++i ) {
            Action *action = Action::read(is, p.feature_map());
            p.add_action(action);
            p.incremented_features_.insert(action->increments().begin(), action->increments().end());
            p.decremented_features_.insert(action->decrements().begin(), action->decrements().end());
        }
    }

    virtual void dump(std::ostream &os) const {
        os << name_ << std::endl;

        os  << features_.size();
        for( size_t i = 0; i < features_.size(); ++i ) {
            os << " " << features_[i]->name() << " " << features_[i]->is_numeric();
        }
        os << std::endl;

        os  << init_.size();
        for( size_t i = 0; i < init_.size(); ++i ) {
        }
        os << std::endl;

        os  << goal_.size();
        for( size_t i = 0; i < goal_.size(); ++i ) {
        }
        os << std::endl;

        os << actions_.size() << std::endl;
        for( size_t i = 0; i < actions_.size(); ++i ) {
            os << *actions_[i];
        }
    }

    // PDDL output
    virtual void PDDL_dump_domain(std::ostream &os) const {
        os << "(define (domain " << PDDL_name(name_) << ")" << std::endl
           << "    (:requirements :non-deterministic)" << std::endl;

        // types
        os << "    (:types";
        for( size_t i = 0; i < types_.size(); ++i )
            os << " " << types_.at(i);
        os << ")" << std::endl;

        // constants
        os << "    (:constants";
        for( size_t i = 0; i < constants_.size(); ++i ) {
            const std::string &type = constants_.at(i).first;
            const std::vector<std::string> &items = constants_.at(i).second;
            for( size_t j = 0; j < items.size(); ++j )
                os << " " << items.at(j);
            os << " - " << type;
        }
        os << ")" << std::endl;

        // predicates
        os << "    (:predicates" << std::endl;
        for( size_t i = 0; i < predicates_.size(); ++i ) {
            const Predicate &pred = predicate(i);
            os << "        " << pred.str() << std::endl;
        }
        os << "    )" << std::endl;

        if( !actions_.empty() ) os << std::endl;
        for( size_t i = 0; i < actions_.size(); ++i )
            actions_[i]->PDDL_dump(os);
        os << ")" << std::endl << std::endl;
    }
    virtual void PDDL_dump_problem(std::ostream &os) const {
        os << "(define (problem " << PDDL_name(name_) << "_p)" << std::endl
           << "    (:domain " << PDDL_name(name_) << ")" << std::endl;

        // initial situation
        os << "    (:init (stack-depth d0)";
        for( size_t i = 0; i < init_.size(); ++i ) {
            const Feature *feature = init_[i].first;
            int value = init_[i].second;
            if( feature->is_numeric() && (value == 0) ) {
                os << " (zero " << PDDL_name(feature->name()) << ")";
            } else if( !feature->is_numeric() && (value > 0) ) {
                os << " " << feature->PDDL_name();
            }
        }
        os << ")" << std::endl;

        // goal situation
        os << "    (:goal (and";
        for( size_t i = 0; i < goal_.size(); ++i ) {
            std::pair<const Feature*, bool> p = goal_.at(i);
            if( p.first->is_numeric() && !p.second )
                os << " (zero " << PDDL_name(p.first->name()) << ")";
            else if( p.first->is_numeric() && p.second )
                os << " (not (zero " << PDDL_name(p.first->name()) << "))";
            else if( p.first->is_boolean() && !p.second )
                os << " (not " << p.first->PDDL_name() << ")";
            else
                os << " " << p.first->PDDL_name();
        }
        os << "))" << std::endl;

        os  << ")" << std::endl << std::endl;
    }
};

}; // namespace Reductions

inline std::ostream& operator<<(std::ostream &os, const Reductions::Problem &p) {
    p.dump(os);
    return os;
}

#endif

