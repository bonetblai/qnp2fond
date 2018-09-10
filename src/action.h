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
    virtual ~Action() { }

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

    virtual void dump(std::ostream &os) const {
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
    virtual void PDDL_dump(std::ostream &os) const {
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

class PushAction : public Action {
  protected:
    const int depth_;
    const int bit_;
    const int num_bits_in_counter_;

  public:
    PushAction(int depth, int bit, int num_bits_in_counter)
      : Action("Push"), depth_(depth), bit_(bit), num_bits_in_counter_(num_bits_in_counter) { }
    virtual ~PushAction() { }
    virtual void dump(std::ostream &os) const {
        assert(0);
    }
    virtual void PDDL_dump(std::ostream &os) const {
        std::string d1(std::string("d") + std::to_string(depth_));
        std::string d2(std::string("d") + std::to_string(1 + depth_));
        std::string b(std::string("b") + std::to_string(bit_));

        os << "    (:action " << (std::string("PUSH_") + d1 + "_" + b) << std::endl
           << "        :parameters (?c - counter)" << std::endl;

        os << "        :precondition (and (stack-depth " << d1 << ")";
        if( depth_ > 0 ) os << " (not (in-stack ?c))";
        os << " (bitvalue " << d1 << " " << b << ")";
        for( int i = bit_ - 1; i >= 0; --i )
            os << " (not (bitvalue " << d1 << " b" << std::to_string(i) << "))";
        os << ")" << std::endl;

        os << "        :effect (and (not (stack-depth " << d1 << ")) (stack-depth " << d2 << ") (in-stack ?c) (stack-idx ?c " << d2 << ") (not (bitvalue " << d1 << " " << b << "))";
        for( int i = bit_ - 1; i >= 0; --i )
            os << " (bitvalue " << d1 << " b" << std::to_string(i) << ")";
        for( int i = num_bits_in_counter_; i >= 0; --i )
            os << " (bitvalue " << d2 << " b" << std::to_string(i) << ")";
        os << ")" << std::endl;

        os << "    )" << std::endl;
    }
};

class PopAction : public Action {
  protected:
    const int depth_;

  public:
    PopAction(int depth) : Action("Pop"), depth_(depth) { }
    virtual ~PopAction() { }
    virtual void dump(std::ostream &os) const {
        assert(0);
    }
    virtual void PDDL_dump(std::ostream &os) const {
        assert(depth_ >= 0);
        std::string d1(std::string("d") + std::to_string(depth_));
        std::string d2(std::string("d") + std::to_string(depth_ - 1));
        os << "    (:action " << (std::string("POP_") + d1) << std::endl
           << "        :parameters (?c - counter)" << std::endl
           << "        :precondition (and (stack-depth " << d1 << ") (in-stack ?c) (stack-idx ?c " << d1 << "))" << std::endl
           << "        :effect (and (not (stack-depth " << d1 << ")) (stack-depth " << d2 << ") (not (in-stack ?c)) (not (stack-idx ?c " << d1 << ")))" << std::endl
           << "    )" << std::endl;
    }
};

}; // namespace QNP

inline std::ostream& operator<<(std::ostream &os, const QNP::Action &action) {
    action.dump(os);
    return os;
}

#endif

