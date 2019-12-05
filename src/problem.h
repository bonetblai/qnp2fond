#ifndef PROBLEM_H
#define PROBLEM_H

#include <cassert>
#include <iostream>
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

// abstract class, instantiated as a QNP or FOND
class Problem {
  protected:
    const std::string name_;

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
    bool meta_info_increments_;

  public:
    Problem(const std::string &name)
      : name_(name),
        meta_info_increments_(false) {
    }
    virtual ~Problem() {
        for( size_t i = 0; i < actions_.size(); ++i )
            delete actions_[i];
        for( size_t i = 0; i < features_.size(); ++i )
            delete features_[i];
    }

    const std::string& name() const { return name_; }
    bool meta_info_increments() const { return meta_info_increments_; }

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
        p.meta_info_increments_ = false;
        for( int i = 0; i < num_actions; ++i ) {
            Action *action = Action::read(is, p.feature_map());
            p.add_action(action);
            p.meta_info_increments_ = p.meta_info_increments_ || !action->increments().empty();
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
    virtual void PDDL_dump_domain(std::ostream &os, int num_bits_per_counter, int max_stack_depth) const {
        os << "(define (domain " << PDDL_name(name_) << ")" << std::endl
           << "    (:requirements :non-deterministic)" << std::endl
           << "    (:types variable depth bit)" << std::endl;

        // constants
        os << "    (:constants";
        for( size_t i = 0; i < features_.size(); ++i ) {
            if( features_[i]->is_numeric() )
                os << " " << PDDL_name(features_[i]->name());
        }
        os << " - variable";

        for( int d = 0; d <= max_stack_depth; ++d )
            os << " d" << d;
        os << " - depth";

        for( int b = 0; b < num_bits_per_counter; ++b )
            os << " b" << b;
        os << " - bit)" << std::endl;

        // predicates
        os << "    (:predicates" << std::endl
           << "        (zero ?X - variable)" << std::endl
           << "        (stack-depth ?d - depth)" << std::endl
           << "        (stack-index ?X - variable ?d - depth)" << std::endl
           << "        (stack-in ?X - variable)" << std::endl
           << "        (counter ?d - depth ?b - bit)" << std::endl;

        for( size_t i = 0; i < boolean_features_.size(); ++i ) {
            const Feature *feature = boolean_features_.at(i);
            os << "        " << feature->PDDL_name() << std::endl;
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

