#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include "basic.h"
#include "feature.h"

namespace Reductions {

class Action {
  protected:
    const std::string name_;
    std::vector<std::pair<const Feature*, bool> > preconditions_;
    std::vector<std::pair<const Feature*, bool> > effects_;
    std::set<const Feature*> increments_;
    std::set<const Feature*> decrements_;

  public:
    Action(const std::string &name) : name_(name) { }
    virtual ~Action() { }

    const std::string& name() const {
        return name_;
    }

    bool check(std::ostream &os) const {
        for( std::set<const Feature*>::const_iterator it = decrements_.begin(); it != decrements_.end(); ++it ) {
            if( !is_precondition(*it, true) ) {
                os << "error: bad precondition for decremented feature " << (*it)->name() << " in action " << name() << std::endl;
                return false;
            }
        }
        return true;
    }

    // preconditions
    size_t num_preconditions() const {
        return preconditions_.size();
    }
    std::pair<const Feature*, bool> precondition(int i) const {
        return preconditions_[i];
    }
    void add_precondition(const Feature *feature, bool value) {
        preconditions_.emplace_back(feature, value);
    }
    bool is_precondition(const Feature *f, bool value) const {
        for( size_t i = 0; i < preconditions_.size(); ++i ) {
            if( preconditions_[i] == std::make_pair(f, value) )
                return true;
        }
        return false;
    }

    // effects
    size_t num_effects() const {
        return effects_.size();
    }
    std::pair<const Feature*, bool> effect(int i) const {
        return effects_[i];
    }
    void add_effect(const Feature *feature, bool value) {
        effects_.emplace_back(feature, value);
        if( feature->is_numeric() && value )
            increments_.insert(feature);
        else if( feature->is_numeric() && !value )
            decrements_.insert(feature);
    }

    // incremented / decremented variables
    const std::set<const Feature*>& increments() const {
        return increments_;
    }
    const std::set<const Feature*>& decrements() const {
        return decrements_;
    }

    // translations
    Action* direct_translation(const std::string &name, const std::map<const Feature*, const Feature*> &feature_map) const {
        Action *clone = new Action(name);

        // translate preconditions
        for( size_t i = 0; i < num_preconditions(); ++i ) {
            std::pair<const Feature*, bool> p = precondition(i);
            assert(p.first != nullptr);
            assert(feature_map.count(p.first) > 0);
            const Feature *new_feature = feature_map.at(p.first);
            assert(new_feature != nullptr);
            clone->add_precondition(new_feature, p.second);
        }

        // translate effects
        for( size_t i = 0; i < num_effects(); ++i ) {
            std::pair<const Feature*, bool> p = effect(i);
            assert(p.first != nullptr);
            assert(feature_map.count(p.first) > 0);
            const Feature *new_feature = feature_map.at(p.first);
            assert(new_feature != nullptr);
            clone->add_effect(new_feature, p.second);
        }

        assert(increments_.size() == clone->increments().size());
        assert(decrements_.size() == clone->decrements().size());

        return clone;
    }
    Action* direct_translation(const std::map<const Feature*, const Feature*> &feature_map) const {
        return direct_translation(name(), feature_map);
    }

    // input
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

    // output
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
            if( feature->is_numeric() && !value ) {
                os << " " << PDDL_zero(feature->name());
            } else if( feature->is_numeric() && value ) {
                os << " " << PDDL_zero(feature->name(), true);
            } else if( feature->is_boolean() && !value ) {
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
            if( feature->is_numeric() && !value ) {
                os << " (oneof " << PDDL_zero(feature->name()) << " " << PDDL_zero(feature->name(), true) << ")";
            } else if( feature->is_numeric() && value ) {
                os << " " << PDDL_zero(feature->name(), true);
            } else if( feature->is_boolean() && !value ) {
                os << " " << feature->PDDL_name(true);
            } else {
                os << " " << feature->PDDL_name();
            }
        }
        os << ")" << std::endl << "    )" << std::endl;
    }
};

class Push : public Action {
  protected:
    const int depth_;
    const int bit_;
    const int num_bits_in_counter_;

  public:
    Push(int depth, int bit, int num_bits_in_counter)
      : Action(std::string("PUSH_at_d") + std::to_string(depth) + "_b" + std::to_string(bit)),
        depth_(depth),
        bit_(bit),
        num_bits_in_counter_(num_bits_in_counter) {
    }
    virtual ~Push() { }

    void dump(std::ostream &os) const override {
        throw std::runtime_error("error: dump() not implemented for push() actions");
    }
    void PDDL_dump(std::ostream &os) const override {
        os << "    (:action " << name_ << std::endl
           << "        :parameters (?X - variable)" << std::endl
           << "        :precondition (and (stack-depth d" << depth_ << ")";
        if( depth_ > 0 ) os << " (not (stack-in ?X))";
        for( int i = 0; i < bit_; ++i )
            os << " (counter d" << depth_ << " b" << i << ")";
        os << " (not (counter d" << depth_ << " b" << bit_ << "))"
           << ")" << std::endl;

        os << "        :effect (and (not (stack-depth d" << depth_ << ")) (stack-depth d" << 1 + depth_ << ") (stack-in ?X) (stack-index ?X d" << 1 + depth_ << ")";
        for( int i = 0; i < bit_; ++i )
            os << " (not (counter d" << depth_ << " b" << i << "))";
        os << " (counter d" << depth_ << " b" << bit_ << ")"
           << ")" << std::endl;

        os << "    )" << std::endl;
    }
};

class Pop : public Action {
  protected:
    const int depth_;

  public:
    Pop(int depth)
      : Action(std::string("POP_at_d") + std::to_string(depth)),
        depth_(depth) {
    }
    virtual ~Pop() { }

    void dump(std::ostream &os) const override {
        throw std::runtime_error("error: dump() not implemented for pop() actions");
    }
    void PDDL_dump(std::ostream &os) const override {
        assert(depth_ > 0);
        os << "    (:action " << name_ << std::endl
           << "        :parameters (?X - variable)" << std::endl
           << "        :precondition (and (stack-depth d" << depth_ << ") (stack-index ?X d" << depth_ << ") (stack-in ?X))" << std::endl
           << "        :effect (and (not (stack-depth d" << depth_ << ")) (not (stack-index ?X d" << depth_ << ")) (not (stack-in ?X)) (stack-depth d" << depth_ - 1 << "))" << std::endl
           << "    )" << std::endl;
    }
};

class Move : public Action {
  protected:
    const int bit_;
    const int num_bits_in_counter_;

  public:
    Move(int bit, int num_bits_in_counter)
      : Action(std::string("MOVE_b") + std::to_string(bit)),
        bit_(bit),
        num_bits_in_counter_(num_bits_in_counter) {
    }
    virtual ~Move() { }

    void dump(std::ostream &os) const override {
        throw std::runtime_error("error: dump() not implemented for pop() actions");
    }
    void PDDL_dump(std::ostream &os) const override {
        os << "    (:action " << name_ << std::endl
           << "        :precondition (and (stack-depth d0)";
        for( int i = 0; i < bit_; ++i )
            os << " (top-counter b" << i << ")";
        os << " (not (top-counter b" << bit_ << "))"
           << ")" << std::endl;

        os << "        :effect (and";
        for( int i = 0; i < bit_; ++i )
            os << " (not (top-counter b" << i << "))";
        os << " (top-counter " << bit_ << ")"
           << ")" << std::endl;

        os << "    )" << std::endl;
    }
};

}; // namespace Reductions

inline std::ostream& operator<<(std::ostream &os, const Reductions::Action &action) {
    action.dump(os);
    return os;
}

#endif

