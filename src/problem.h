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

namespace QNP {

class Problem {
  protected:
    const std::string name_;
    const int num_bits_per_counter_;
    const int loop_nesting_;
    std::vector<const Feature*> features_;
    std::vector<std::pair<const Feature*, bool> > init_;
    std::vector<std::pair<const Feature*, bool> > goal_;
    std::vector<const Action*> actions_;
    std::map<std::string, const Feature*> feature_map_;

    // temporal vars used in translation
    mutable std::vector<const Feature*> numeric_features_;
    mutable std::vector<const Feature*> boolean_features_;
    mutable std::map<std::string, const Feature*> enablers_;
    mutable std::map<std::string, int> variable_;

    mutable std::vector<const Feature*> bitvalue_features_;

    // translation without loop nesting
    mutable std::vector<const Feature*> q_features_;

    // translation with loop nesting
    mutable std::vector<const Feature*> stack_depth_features_;
    mutable std::vector<const Feature*> stack_in_features_;
    mutable std::vector<const Feature*> stack_idx_features_;

    // methods for qnp2fond translation
    void create_set_actions(Problem *fond) const;
    void create_unset_actions(Problem *fond) const;

    void create_push_actions(Problem *fond) const;
    void create_pop_actions(Problem *fond) const;

    Action* clone_qnp_action(const Problem *fond, const Action *action, const std::string &name) const;
    void translate_qnp_action(Problem *fond, const Action *action) const;
    void translate_qnp_actions(Problem *fond) const;

    Problem* create_fond(int num_bits_per_counter, int loop_nesting) const;
    void translate(Problem *fond) const;

  public:
    Problem(const std::string &name, int num_bits_per_counter = 0, int loop_nesting = 0)
      : name_(name), num_bits_per_counter_(num_bits_per_counter), loop_nesting_(loop_nesting) {
    }
    ~Problem() {
        for( size_t i = 0; i < actions_.size(); ++i )
            delete actions_[i];
        for( size_t i = 0; i < features_.size(); ++i )
            delete features_[i];
    }

    const std::string& name() const { return name_; }
    const Feature& feature(int i) const {
        return *features_[i];
    }
    const Action& action(int i) const {
        return *actions_[i];
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
        feature_map_.insert(std::make_pair(feature->name(), features_.back()));
    }
    void add_init(const Feature *feature, bool value) {
        init_.push_back(std::make_pair(feature, value));
    }
    void add_goal(const Feature *feature, bool value) {
        goal_.push_back(std::make_pair(feature, value));
    }
    void add_action(const Action *action) {
        assert(action != nullptr);
        actions_.push_back(action);
    }

    Problem* translate(int num_bits_per_counter, int loop_nesting = 0) const;

    static Problem* read(std::istream &is) {
        std::string name;
        is >> name;
        Problem *qnp = new Problem(name);

        int num_features;
        is >> num_features;
        for( int i = 0; i < num_features; ++i ) {
            Feature *feature = Feature::read(is);
            qnp->add_feature(feature);
        }

        int num_init;
        is >> num_init;
        for( int i = 0; i < num_init; ++i ) {
            std::string name;
            bool value;
            is >> name >> value;
            std::map<std::string, const Feature*>::const_iterator it = qnp->feature_map().find(name);
            if( it == qnp->feature_map().end() )
                std::cout << "error: inexistent feature '" << name << "'" << std::endl;
            else
                qnp->add_init(it->second, value);
        }

        int num_goal;
        is >> num_goal;
        for( int i = 0; i < num_goal; ++i ) {
            std::string name;
            bool value;
            is >> name >> value;
            std::map<std::string, const Feature*>::const_iterator it = qnp->feature_map().find(name);
            if( it == qnp->feature_map().end() )
                std::cout << "error: inexistent feature '" << name << "'" << std::endl;
            else
                qnp->add_goal(it->second, value);
        }

        int num_actions;
        is >> num_actions;
        for( int i = 0; i < num_actions; ++i ) {
            Action *action = Action::read(is, qnp->feature_map());
            qnp->add_action(action);
        }

        return qnp;
    }

    void dump(std::ostream &os) const {
        os << name_ << std::endl << features_.size();
        for( size_t i = 0; i < features_.size(); ++i ) {
            os << " " << features_[i]->name() << " " << features_[i]->numeric();
        }
        os << std::endl << actions_.size() << std::endl;
        for( size_t i = 0; i < actions_.size(); ++i ) {
            os << *actions_[i];
        }
    }
    void PDDL_dump_domain(std::ostream &os) const {
        os << "(define (domain " << PDDL_name(name_) << ")" << std::endl
           << "    (:requirements :non-deterministic)" << std::endl
           << "    (:types counter";

        if( loop_nesting_ > 0 ) os << " depth";
        os << " bit)" << std::endl;

        os << "    (:constants";
        for( size_t i = 0; i < features_.size(); ++i ) {
            if( features_[i]->numeric() )
                os << " " << PDDL_name(features_[i]->name());
        }
        os << " - counter";

        if( loop_nesting_ > 0 ) {
            for( int d = 0; d <= loop_nesting_; ++d )
                os << " d" << d;
            os << " - depth";
        }

        for( int b = 0; b <= num_bits_per_counter_; ++b )
            os << " b" << b;
        os << " - bit)" << std::endl;

        os << "    (:predicates" << std::endl
           << "        (zero ?c - counter)" << std::endl;

        if( loop_nesting_ == 0 ) {
             os << "        (q ?c - counter)" << std::endl
                << "        (bitvalue ?b - bit)" << std::endl;
        } else {
             os << "        (stack-depth ?d - depth)" << std::endl
                << "        (stack-idx ?c - counter ?d - depth)" << std::endl
                << "        (in-stack ?c - counter)" << std::endl
                << "        (bitvalue ?d - depth ?b - bit)" << std::endl;
        }

        for( size_t i = 0; i < features_.size(); ++i ) {
            if( !features_[i]->numeric() && (features_[i]->PDDL_name().substr(0, 3) != "(q ") )
                os << "        " << features_[i]->PDDL_name() << std::endl;
        }
        os << "    )" << std::endl;

        if( !actions_.empty() ) os << std::endl;
        for( size_t i = 0; i < actions_.size(); ++i )
            actions_[i]->PDDL_dump(os);
        os << ")" << std::endl << std::endl;
    }
    void PDDL_dump_problem(std::ostream &os) const {
        os << "(define (problem " << PDDL_name(name_) << "_p)" << std::endl
           << "    (:domain " << PDDL_name(name_) << ")" << std::endl;

        // initial situation
        os << "    (:init";
        for( size_t i = 0; i < init_.size(); ++i ) {
            const Feature *feature = init_[i].first;
            int value = init_[i].second;
            if( feature->numeric() && (value == 0) ) {
                os << " (zero " << PDDL_name(feature->name()) << ")";
            } else if( !feature->numeric() && (value > 0) ) {
                os << " " << feature->PDDL_name();
            }
        }
        if( loop_nesting_ == 0 ) {
            for( int b = 0; b <= num_bits_per_counter_; ++b )
                os << " (bitvalue b" << b << ")";
        } else {
            os << " (stack-depth d0)";
            for( int b = 0; b <= num_bits_per_counter_; ++b )
                os << " (bitvalue d0 b" << b << ")";
        }
        os << ")" << std::endl;

        // goal situation
        os << "    (:goal";
        if( (goal_.size() > 1) || (loop_nesting_ > 0) ) os << " (and";
        for( size_t i = 0; i < goal_.size(); ++i ) {
            const Feature *feature = goal_[i].first;
            int value = goal_[i].second;
            if( feature->numeric() && (value == 0) ) {
                os << " (zero " << PDDL_name(feature->name()) << ")";
            } else if( feature->numeric() && (value > 0) ) {
                os << " (not (zero " << PDDL_name(feature->name()) << "))";
            } else if( !feature->numeric() && (value == 0) ) {
                os << " (not " << feature->PDDL_name() << ")";
            } else {
                os << " " << feature->PDDL_name();
            }
        }
        if( loop_nesting_ > 0 ) os << " (stack-depth d0)";
        if( (goal_.size() > 1) || (loop_nesting_ > 0) ) os << ")";
        os << ")" << std::endl;
       
        os  << ")" << std::endl << std::endl;
    }
};

inline void Problem::create_set_actions(Problem *fond) const {
    for( size_t i = 0; i < numeric_features_.size(); ++i ) {
        for( int b = 0; b <= fond->num_bits_per_counter_; ++b ) {
            std::string name = std::string("Set(") + numeric_features_[i]->name() + ",b" + std::to_string(b) + ")";
            Action *a = new Action(name);
            for( size_t j = 0; j < numeric_features_.size(); ++j )
                a->add_precondition(fond->q_features_[j], false);
            a->add_precondition(fond->bitvalue_features_[b], true);
            for( int t = b - 1; t >= 0; --t )
                a->add_precondition(fond->bitvalue_features_[t], false);
            a->add_effect(fond->q_features_[i], true);
            a->add_effect(fond->bitvalue_features_[b], false);
            for( int t = b - 1; t >= 0; --t )
                a->add_effect(fond->bitvalue_features_[t], true);
            fond->add_action(a);
        }
    }
}

inline void Problem::create_unset_actions(Problem *fond) const {
    for( size_t i = 0; i < numeric_features_.size(); ++i ) {
        std::string name = std::string("Unset(") + numeric_features_[i]->name() + ")";
        Action *a = new Action(name);
        a->add_precondition(fond->q_features_[i], true);
        a->add_effect(fond->q_features_[i], false);
        fond->add_action(a);
    }
}

inline void Problem::create_push_actions(Problem *fond) const {
#if 0
    for( int d = 0; d < fond->loop_nesting_; ++d ) {
        for( size_t i = 0; i < numeric_features_.size(); ++i ) {
            for( int b = 0; b <= fond->num_bits_per_counter_; ++b ) {
                std::string name = std::string("Push(") + numeric_features_[i]->name() + ",d" + std::to_string(d) + ",b" + std::to_string(b) + ")";
                Action *a = new Action(name);

                // preconditions: (and (di) (not (in X)) (c i t) (not (c i t-1)) ... (not (c i 0)))
                a->add_precondition(fond->stack_depth_features_[d], true);
                if( d > 0 ) a->add_precondition(fond->stack_in_features_[i], false);
                a->add_precondition(fond->bitvalue_features_[d * (1 + fond->num_bits_per_counter_) + b], true);
                for( int t = b - 1; t >= 0; --t )
                    a->add_precondition(fond->bitvalue_features_[d * (1 + fond->num_bits_per_counter_) + t], false);

                // effects: (and (not (di)) (di+1) (in X) (idx X i+1) (not (c i t)) (c i t-1) ... (c i 0) (reset i+1))
                a->add_effect(fond->stack_depth_features_[d], false);
                a->add_effect(fond->stack_depth_features_[d+1], true);
                a->add_effect(fond->stack_in_features_[i], true);
                a->add_effect(fond->stack_idx_features_[d * numeric_features_.size() + i], true);
                a->add_effect(fond->bitvalue_features_[d * (1 + fond->num_bits_per_counter_) + b], false);
                for( int t = b - 1; t >= 0; --t )
                    a->add_effect(fond->bitvalue_features_[d * (1 + fond->num_bits_per_counter_) + t], true);
                for( int t = 0; t <= fond->num_bits_per_counter_; ++t )
                    a->add_effect(fond->bitvalue_features_[(d + 1) * (1 + fond->num_bits_per_counter_) + t], true);

                fond->add_action(a);
            }
        }
    }
#else
    for( int d = 0; d < fond->loop_nesting_; ++d ) {
        for( int b = 0; b <= fond->num_bits_per_counter_; ++b ) {
            Action *a = new PushAction(d, b, fond->num_bits_per_counter_);
            fond->add_action(a);
        }
    }
#endif
}

inline void Problem::create_pop_actions(Problem *fond) const {
#if 0
    for( int d = 1; d <= fond->loop_nesting_; ++d ) {
        for( size_t i = 0; i < numeric_features_.size(); ++i ) {
            std::string name = std::string("Pop(") + numeric_features_[i]->name() + ",d" + std::to_string(d) + ")";
            Action *a = new Action(name);

            // preconditions
            a->add_precondition(fond->stack_depth_features_[d], true);
            a->add_precondition(fond->stack_in_features_[i], true);
            a->add_precondition(fond->stack_idx_features_[(d - 1) * numeric_features_.size() + i], true);

            // effects
            a->add_effect(fond->stack_depth_features_[d-1], true);
            a->add_effect(fond->stack_depth_features_[d], false);
            a->add_effect(fond->stack_in_features_[i], false);
            a->add_effect(fond->stack_idx_features_[(d - 1) * numeric_features_.size() + i], false);

            fond->add_action(a);
        }
    }
#else
    for( int d = 1; d <= fond->loop_nesting_; ++d ) {
        Action *a = new PopAction(d);
        fond->add_action(a);
    }
#endif
}

inline Action* Problem::clone_qnp_action(const Problem *fond, const Action *action, const std::string &name) const {
    Action *a = new Action(name);

    // preconditions
    for( size_t k = 0; k < action->num_preconditions(); ++k ) {
        const Feature *feature = action->precondition(k).first;
        bool value = action->precondition(k).second;
        a->add_precondition(fond->feature(feature->name()), value);
    }

    // effects
    for( size_t k = 0; k < action->num_effects(); ++k ) {
        const Feature *feature = action->effect(k).first;
        bool value = action->effect(k).second;
        a->add_effect(fond->feature(feature->name()), value);
    }

    return a;
}

inline void Problem::translate_qnp_action(Problem *fond, const Action *action) const {
    std::vector<const Feature*> features_increased;
    std::vector<const Feature*> features_decreased;
    for( size_t i = 0; i < action->num_effects(); ++i ) {
        const Feature *feature = action->effect(i).first;
        if( feature->numeric() && action->effect(i).second )
            features_increased.push_back(feature);
        else if( feature->numeric() )
            features_decreased.push_back(feature);
    }

    if( features_decreased.empty() ) {
        Action *a = clone_qnp_action(fond, action, action->name());

        // extra preconditions
        for( size_t i = 0; i < features_increased.size(); ++i ) {
            assert(fond->enablers_.find(features_increased[i]->name()) != fond->enablers_.end());
            a->add_precondition(fond->enablers_[features_increased[i]->name()], false);
        }

        fond->add_action(a);
    } else {
        for( size_t i = 0; i < features_decreased.size(); ++i ) {
            if( fond->loop_nesting_ == 0 ) {
                std::string name = action->name();
                if( features_decreased.size() > 1 )
                    name += std::string("_") + std::to_string(i);
                Action *a = clone_qnp_action(fond, action, name);

                // extra preconditions
                assert(fond->enablers_.find(features_decreased[i]->name()) != fond->enablers_.end());
                a->add_precondition(fond->enablers_[features_decreased[i]->name()], true);
                for( size_t j = 0; j < features_increased.size(); ++j ) {
                    assert(fond->enablers_.find(features_increased[j]->name()) != fond->enablers_.end());
                    a->add_precondition(fond->enablers_[features_increased[j]->name()], false);
                }
                fond->add_action(a);
            } else {
                for( int d = 1; d <= fond->loop_nesting_; ++d ) {
                    std::string name = action->name();
                    if( features_decreased.size() > 1 )
                        name += std::string("_") + std::to_string(i);
                    name += std::string("_d") + std::to_string(d);
                    Action *a = clone_qnp_action(fond, action, name);

                    // extra preconditions
                    assert(fond->enablers_.find(features_decreased[i]->name()) != fond->enablers_.end());
                    a->add_precondition(fond->enablers_[features_decreased[i]->name()], true);
                    for( size_t j = 0; j < features_increased.size(); ++j ) {
                        assert(fond->enablers_.find(features_increased[j]->name()) != fond->enablers_.end());
                        a->add_precondition(fond->enablers_[features_increased[j]->name()], false);
                    }
                    assert(fond->variable_.find(features_decreased[i]->name()) != fond->variable_.end());
                    int j = fond->variable_[features_decreased[i]->name()];
                    a->add_precondition(fond->stack_idx_features_[(d - 1) * numeric_features_.size() + j], true);

                    // extra effects: reset counters when loop_nesting is activated
                    for( int t = d; t <= fond->loop_nesting_; ++t ) {
                        // reset ctr(t)
                        for( int b = 0; b <= fond->num_bits_per_counter_; ++b )
                            a->add_effect(fond->bitvalue_features_[t * (1 + fond->num_bits_per_counter_) + b], true);
                    }

                    fond->add_action(a);
                }
            }
        }
    }
}

inline void Problem::translate_qnp_actions(Problem *fond) const {
    for( size_t i = 0; i < actions_.size(); ++i ) {
        const Action *action = actions_[i];
        translate_qnp_action(fond, action);
    }
}

inline void Problem::translate(Problem *fond) const {
    if( fond->loop_nesting_ == 0 ) {
        create_set_actions(fond);
        create_unset_actions(fond);
    } else {
        create_push_actions(fond);
        create_pop_actions(fond);
    }
    translate_qnp_actions(fond);
}

inline Problem* Problem::create_fond(int num_bits_per_counter, int loop_nesting) const {
    Problem *fond = new Problem(std::string("FOND_") + name_ + "_" + std::to_string(num_bits_per_counter) + "_" + std::to_string(loop_nesting),
                                num_bits_per_counter,
                                loop_nesting);

    // clone features
    for( size_t i = 0; i < numeric_features_.size(); ++i )
        fond->add_feature(new Feature(numeric_features_[i]->name(), true));
    for( size_t i = 0; i < boolean_features_.size(); ++i )
        fond->add_feature(new Feature(boolean_features_[i]->name(), false));

    // create additional features (fluents)
    if( loop_nesting == 0 ) {
        fond->bitvalue_features_.clear();
        for( int b = 0; b <= fond->num_bits_per_counter_; ++b ) {
            const Feature *feature = new Feature(std::string("(bitvalue b") + std::to_string(b) + ")", false, true);
            fond->bitvalue_features_.push_back(feature);
            //fond->add_feature(feature);
        }

        fond->enablers_.clear();
        fond->q_features_.clear();
        for( size_t i = 0; i < numeric_features_.size(); ++i ) {
            const Feature *feature = new Feature(std::string("(q ") + PDDL_name(numeric_features_[i]->name()) + ")", false, true);
            fond->q_features_.push_back(feature);
            //fond->add_feature(feature);
            fond->enablers_.insert(std::make_pair(numeric_features_[i]->name(), feature));
        }
    } else {
        fond->stack_depth_features_.clear();
        for( int d = 0; d <= loop_nesting; ++d ) {
            const Feature *feature = new Feature(std::string("(stack-depth d") + std::to_string(d) + ")", false, true);
            fond->stack_depth_features_.push_back(feature);
            //fond->add_feature(feature);
        }

        fond->stack_in_features_.clear();
        for( size_t i = 0; i < numeric_features_.size(); ++i ) {
            const Feature *feature = new Feature(std::string("(in-stack ") + PDDL_name(numeric_features_[i]->name()) + ")", false, true);
            fond->stack_in_features_.push_back(feature);
            //fond->add_feature(feature);
            fond->enablers_.insert(std::make_pair(numeric_features_[i]->name(), feature));
            fond->variable_.insert(std::make_pair(numeric_features_[i]->name(), i));
        }

        fond->stack_idx_features_.clear();
        for( int d = 1; d <= loop_nesting; ++d ) {
            for( size_t i = 0; i < numeric_features_.size(); ++i ) {
                const Feature *feature = new Feature(std::string("(stack-idx ") + PDDL_name(numeric_features_[i]->name()) + " d" + std::to_string(d) + ")", false, true);
                fond->stack_idx_features_.push_back(feature);
                //fond->add_feature(feature);
            }
        }

        fond->bitvalue_features_.clear();
        for( int d = 0; d <= loop_nesting; ++d ) {
            for( int b = 0; b <= fond->num_bits_per_counter_; ++b ) {
                const Feature *feature = new Feature(std::string("(bitvalue d") + std::to_string(d) + " b" + std::to_string(b) + ")", false, true);
                fond->bitvalue_features_.push_back(feature);
                //fond->add_feature(feature);
            }
        }
    }

    // copy initial and goal situations
    for( size_t i = 0; i < init_.size(); ++i ) {
        const Feature *feature = fond->feature(init_[i].first->name());
        int value = init_[i].second;
        assert(feature != nullptr);
        fond->add_init(feature, value);
    }

    for( size_t i = 0; i < goal_.size(); ++i ) {
        const Feature *feature = fond->feature(goal_[i].first->name());
        int value = goal_[i].second;
        assert(feature != nullptr);
        fond->add_goal(feature, value);
    }

    return fond;
}

inline Problem* Problem::translate(int num_bits_per_counter, int loop_nesting) const {
    // separate features
    numeric_features_.clear();
    boolean_features_.clear();
    for( size_t i = 0; i < features_.size(); ++i ) {
        if( features_[i]->numeric() )
            numeric_features_.push_back(features_[i]);
        else
            boolean_features_.push_back(features_[i]);
    }

    // create FOND and finish translation
    Problem *fond = create_fond(num_bits_per_counter, loop_nesting);
    translate(fond);
    return fond;
}

}; // namespace QNP

inline std::ostream& operator<<(std::ostream &os, const QNP::Problem &qnp) {
    qnp.dump(os);
    return os;
}

#endif

