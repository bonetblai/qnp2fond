#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "basic.h"
#include "feature.h"

namespace QNP {

class Action {
  protected:
    const std::string name_;
    std::vector<std::pair<const Feature*, bool> > preconditions_;
    std::vector<std::pair<const Feature*, bool> > effects_;

  public:
    Action(const std::string &name) : name_(name) { }

    const std::string& name() const { return name_; }
    size_t num_preconditions() const {
        return preconditions_.size();
    }
    size_t num_effects() const {
        return effects_.size();
    }
    std::pair<const Feature*, bool> precondition(int i) const {
        return preconditions_[i];
    }
    std::pair<const Feature*, bool> effect(int i) const {
        return effects_[i];
    }

    void add_precondition(const Feature *feature, bool value) {
        preconditions_.push_back(std::make_pair(feature, value));
    }
    void add_effect(const Feature *feature, bool value) {
        effects_.push_back(std::make_pair(feature, value));
    }

    static Action* read(std::istream &is, const std::map<std::string, const Feature*> &feature_map) {
        std::string name;
        is >> name;
        Action *action = new Action(name);
        int num_preconditions;
        is >> num_preconditions;
        for( int i = 0; i < num_preconditions; ++i ) {
            std::string name;
            bool value;
            is >> name >> value;
            std::map<std::string, const Feature*>::const_iterator it = feature_map.find(name);
            if( it == feature_map.end() )
                std::cout << "error: inexistent feature '" << name << "'" << std::endl;
            else
                action->add_precondition(it->second, value);
        }
        int num_effects;
        is >> num_effects;
        for( int i = 0; i < num_effects; ++i ) {
            std::string name;
            bool value;
            is >> name >> value;
            std::map<std::string, const Feature*>::const_iterator it = feature_map.find(name);
            if( it == feature_map.end() )
                std::cout << "error: inexistent feature '" << name << "'" << std::endl;
            else
                action->add_effect(it->second, value);
        }
        return action;
    }

    void dump(std::ostream &os) const {
        os << name_ << std::endl << preconditions_.size();
        for( size_t i = 0; i < preconditions_.size(); ++i ) {
            os << " " << *preconditions_[i].first << " " << preconditions_[i].second;
        }
        os << std::endl << effects_.size();
        for( size_t i = 0; i < effects_.size(); ++i ) {
            os << " " << *effects_[i].first << " " << effects_[i].second;
        }
        os << std::endl;
    }
    void PDDL_dump(std::ostream &os) const {
        os << "    (:action " << PDDL_name(name_) << std::endl
           << "        :precondition (and";

        for( size_t i = 0; i < preconditions_.size(); ++i ) {
            const Feature *feature = preconditions_[i].first;
            bool value = preconditions_[i].second;
            if( feature->numeric() && !value ) {
                os << " " << PDDL_zero(feature->name());
            } else if( feature->numeric() && value ) {
                os << " " << PDDL_zero(feature->name(), true);
            } else if( !feature->numeric() && !value ) {
                os << " " << feature->PDDL_name(true);
            } else {
                os << " " << feature->PDDL_name();
            }
        }
        os << ")" << std::endl;

        os << "        :effect (and";
        for( size_t i = 0; i < effects_.size(); ++i ) {
            const Feature *feature = effects_[i].first;
            bool value = effects_[i].second;
            if( feature->numeric() && !value ) {
                os << " (oneof " << PDDL_zero(feature->name()) << " " << PDDL_zero(feature->name(), true) << ")";
            } else if( feature->numeric() && value ) {
                os << " " << PDDL_zero(feature->name(), true);
            } else if( !feature->numeric() && !value ) {
                os << " " << feature->PDDL_name(true);
            } else {
                os << " " << feature->PDDL_name();
            }
        }
        os << ")" << std::endl << "    )" << std::endl;
    }
};

}; // namespace QNP

inline std::ostream& operator<<(std::ostream &os, const QNP::Action &action) {
    action.dump(os);
    return os;
}

#endif

