#ifndef PROBLEM_H
#define PROBLEM_H

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
    std::vector<const Feature*> features_;
    std::vector<const Action*> actions_;
    std::map<std::string, const Feature*> feature_map_;

    // temporal vars used in translation
    mutable std::vector<const Feature*> numeric_features_;
    mutable std::vector<const Feature*> boolean_features_;
    mutable std::map<std::string, const Feature*> enablers_;
    mutable std::map<std::string, int> variable_;

    // translation without loop nesting
    mutable std::vector<const Feature*> bit_features_;
    mutable std::vector<const Feature*> q_features_;

    // translation with loop nesting
    mutable std::vector<const Feature*> d_features_;
    mutable std::vector<const Feature*> in_features_;
    mutable std::vector<const Feature*> idx_features_;
    mutable std::vector<const Feature*> ctr_features_;

    // methods for qnp2fond translation
    void create_set_actions(Problem *fond, int d, int loop_nesting) const;
    void create_unset_actions(Problem *fond, int d, int loop_nesting) const;

    void create_push_actions(Problem *fond, int d, int loop_nesting) const;
    void create_pop_actions(Problem *fond, int d, int loop_nesting) const;

    Action* clone_qnp_action(const Problem *fond, const Action *action, const std::string &name) const;
    void translate_qnp_action(Problem *fond, const Action *action, int d, int loop_nesting) const;
    void translate_qnp_actions(Problem *fond, int d, int loop_nesting) const;

    Problem* create_fond(int d, int loop_nesting) const;
    void translate(Problem *fond, int d, int loop_nesting) const;

  public:
    Problem(const std::string &name) : name_(name) { }
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
    void add_action(const Action *action) {
        assert(action != nullptr);
        actions_.push_back(action);
    }

    Problem* translate(int d, int loop_nesting = 0) const;

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
    void PDDL_dump(std::ostream &os) const {
        os << "(define (domain " << PDDL_name(name_) << ")" << std::endl
           << "    (:requirements :non-deterministic)" << std::endl
           << "    (:types counter)" << std::endl
           << "    (:constants";

        for( size_t i = 0; i < features_.size(); ++i ) {
            if( features_[i]->numeric() )
                os << " " << PDDL_name(features_[i]->name());
        }
        os << " - counter)" << std::endl;

        os << "    (:predicates" << std::endl
           << "        (zero ?c - counter)" << std::endl
           << "        (q ?c - counter)" << std::endl;

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
};

inline void Problem::create_set_actions(Problem *fond, int d, int loop_nesting) const {
    for( size_t i = 0; i < numeric_features_.size(); ++i ) {
        for( int t = 0; t <= d; ++t ) {
            std::string name = std::string("Set(") + numeric_features_[i]->name() + "," + std::to_string(t) + ")";
            Action *a = new Action(name);
            for( size_t j = 0; j < numeric_features_.size(); ++j )
                a->add_precondition(fond->q_features_[j], false);
            a->add_precondition(fond->bit_features_[t], true);
            for( int j = t - 1; j >= 0; --j )
                a->add_precondition(fond->bit_features_[j], false);
            a->add_effect(fond->q_features_[i], true);
            a->add_effect(fond->bit_features_[t], false);
            for( int j = t - 1; j >= 0; --j )
                a->add_effect(fond->bit_features_[j], true);
            fond->add_action(a);
        }
    }
}

inline void Problem::create_unset_actions(Problem *fond, int d, int loop_nesting) const {
    for( size_t i = 0; i < numeric_features_.size(); ++i ) {
        std::string name = std::string("Unset(") + numeric_features_[i]->name() + ")";
        Action *a = new Action(name);
        a->add_precondition(fond->q_features_[i], true);
        a->add_effect(fond->q_features_[i], false);
        fond->add_action(a);
    }
}

inline void Problem::create_push_actions(Problem *fond, int d, int loop_nesting) const {
    for( int i = 0; i < loop_nesting; ++i ) {
        for( size_t j = 0; j < numeric_features_.size(); ++j ) {
            for( int k = 0; k <= d; ++k ) {
                std::string name = std::string("Push(") + numeric_features_[j]->name() + ",d" + std::to_string(i) + "," + std::to_string(k) + ")";
                Action *a = new Action(name);

                // preconditions: (and (di) (not (in X)) (c i t) (not (c i t-1)) ... (not (c i 0)))
                a->add_precondition(fond->d_features_[i], true);
                if( i > 0 ) a->add_precondition(fond->in_features_[j], false);
                a->add_precondition(fond->ctr_features_[i * (d + 1) + k], true);
                for( int t = k - 1; t >= 0; --t )
                    a->add_precondition(fond->ctr_features_[i * (d + 1) + t], false);

                // effects: (and (not (di)) (di+1) (in X) (idx X i+1) (not (c i t)) (c i t-1) ... (c i 0) (reset i+1))
                a->add_effect(fond->d_features_[i], false);
                a->add_effect(fond->d_features_[i+1], true);
                a->add_effect(fond->in_features_[j], true);
                a->add_effect(fond->idx_features_[i * numeric_features_.size() + j], true);
                a->add_effect(fond->ctr_features_[i * (d + 1) + k], false);
                for( int t = k - 1; t >= 0; --t )
                    a->add_effect(fond->ctr_features_[i * (d + 1) + t], true);
                for( int t = 0; t <= d; ++t )
                    a->add_effect(fond->ctr_features_[(i + 1) * (d + 1) + t], true);

                fond->add_action(a);
            }
        }
    }
}

inline void Problem::create_pop_actions(Problem *fond, int d, int loop_nesting) const {
    for( int i = 1; i <= loop_nesting; ++i ) {
        for( size_t j = 0; j < numeric_features_.size(); ++j ) {
            std::string name = std::string("Pop(") + numeric_features_[j]->name() + "," + std::to_string(i) + ")";
            Action *a = new Action(name);

            // preconditions
            a->add_precondition(fond->d_features_[i], true);
            a->add_precondition(fond->in_features_[j], true);
            a->add_precondition(fond->idx_features_[(i - 1) * numeric_features_.size() + j], true);

            // effects
            a->add_effect(fond->d_features_[i-1], true);
            a->add_effect(fond->d_features_[i], false);
            a->add_effect(fond->in_features_[j], false);
            a->add_effect(fond->idx_features_[(i - 1) * numeric_features_.size() + j], false);

            fond->add_action(a);
        }
    }
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

inline void Problem::translate_qnp_action(Problem *fond, const Action *action, int d, int loop_nesting) const {
    std::vector<const Feature*> features_increased;
    std::vector<const Feature*> features_decreased;
    for( size_t j = 0; j < action->num_effects(); ++j ) {
        const Feature *feature = action->effect(j).first;
        if( feature->numeric() && action->effect(j).second )
            features_increased.push_back(feature);
        else if( feature->numeric() )
            features_decreased.push_back(feature);
    }

    if( features_decreased.empty() ) {
        Action *a = clone_qnp_action(fond, action, action->name());

        // extra preconditions
        for( size_t k = 0; k < features_increased.size(); ++k ) {
            assert(fond->enablers_.find(features_increased[k]->name()) != fond->enablers_.end());
            a->add_precondition(fond->enablers_[features_increased[k]->name()], false);
        }

        fond->add_action(a);
    } else {
        for( size_t j = 0; j < features_decreased.size(); ++j ) {
            if( loop_nesting == 0 ) {
                std::string name = action->name();
                if( features_decreased.size() > 1 )
                    name += std::string("_") + std::to_string(j);
                Action *a = clone_qnp_action(fond, action, name);

                // extra preconditions
                assert(fond->enablers_.find(features_decreased[j]->name()) != fond->enablers_.end());
                a->add_precondition(fond->enablers_[features_decreased[j]->name()], true);
                for( size_t k = 0; k < features_increased.size(); ++k ) {
                    assert(fond->enablers_.find(features_increased[k]->name()) != fond->enablers_.end());
                    a->add_precondition(fond->enablers_[features_increased[k]->name()], false);
                }
                fond->add_action(a);
            } else {
                for( int i = 1; i < loop_nesting; ++i ) {
                    std::string name = action->name();
                    if( features_decreased.size() > 1 )
                        name += std::string("_") + std::to_string(j);
                    name += std::string("_") + std::to_string(i);
                    Action *a = clone_qnp_action(fond, action, name);

                    // extra preconditions
                    assert(fond->enablers_.find(features_decreased[j]->name()) != fond->enablers_.end());
                    a->add_precondition(fond->enablers_[features_decreased[j]->name()], true);
                    for( size_t k = 0; k < features_increased.size(); ++k ) {
                        assert(fond->enablers_.find(features_increased[k]->name()) != fond->enablers_.end());
                        a->add_precondition(fond->enablers_[features_increased[k]->name()], false);
                    }
                    assert(fond->variable_.find(features_decreased[j]->name()) != fond->variable_.end());
                    int var = fond->variable_[features_decreased[j]->name()];
                    a->add_precondition(fond->idx_features_[(i - 1) * numeric_features_.size() + var], true);

                    // extra effects: reset counters when loop_nesting is activated
                    for( int t = i; t <= loop_nesting; ++t ) {
                        // reset ctr(t)
                        for( int k = 0; k <= d; ++k )
                            a->add_effect(fond->ctr_features_[t * (d + 1) + k], true);
                    }

                    fond->add_action(a);
                }
            }
        }
    }
}

inline void Problem::translate_qnp_actions(Problem *fond, int d, int loop_nesting) const {
    for( size_t i = 0; i < actions_.size(); ++i ) {
        const Action *action = actions_[i];
        translate_qnp_action(fond, action, d, loop_nesting);
    }
}

inline void Problem::translate(Problem *fond, int d, int loop_nesting) const {
    if( loop_nesting == 0 ) {
        create_set_actions(fond, d, loop_nesting);
        create_unset_actions(fond, d, loop_nesting);
    } else {
        create_push_actions(fond, d, loop_nesting);
        create_pop_actions(fond, d, loop_nesting);
    }
    translate_qnp_actions(fond, d, loop_nesting);
}

inline Problem* Problem::create_fond(int d, int loop_nesting) const {
    Problem *fond = new Problem(std::string("FOND_") + name_ + "_" + std::to_string(d) + "_" + std::to_string(loop_nesting));

    // clone features
    for( size_t i = 0; i < numeric_features_.size(); ++i )
        fond->add_feature(new Feature(numeric_features_[i]->name(), true));
    for( size_t i = 0; i < boolean_features_.size(); ++i )
        fond->add_feature(new Feature(boolean_features_[i]->name(), false));

    // create additional features (fluents)
    if( loop_nesting == 0 ) {
        fond->bit_features_.clear();
        for( int i = 0; i <= d; ++i ) {
            const Feature *feature = new Feature(std::string("bit(") + std::to_string(i) + ")", false);
            fond->bit_features_.push_back(feature);
            fond->add_feature(feature);
        }

        fond->enablers_.clear();
        fond->q_features_.clear();
        for( size_t i = 0; i < numeric_features_.size(); ++i ) {
            const Feature *feature = new Feature(PDDL_q(numeric_features_[i]->name()), false, true);
            fond->q_features_.push_back(feature);
            fond->add_feature(feature);
            fond->enablers_.insert(std::make_pair(numeric_features_[i]->name(), feature));
        }
    } else {
        fond->d_features_.clear();
        for( int i = 0; i <= loop_nesting; ++i ) {
            const Feature *feature = new Feature(std::string("d(") + std::to_string(i) + ")", false);
            fond->d_features_.push_back(feature);
            fond->add_feature(feature);
        }

        fond->in_features_.clear();
        for( size_t i = 0; i < numeric_features_.size(); ++i ) {
            const Feature *feature = new Feature(std::string("in(") + numeric_features_[i]->name() + ")", false);
            fond->in_features_.push_back(feature);
            fond->add_feature(feature);
            fond->enablers_.insert(std::make_pair(numeric_features_[i]->name(), feature));
            fond->variable_.insert(std::make_pair(numeric_features_[i]->name(), i));
        }

        fond->idx_features_.clear();
        for( int i = 1; i <= loop_nesting; ++i ) {
            for( size_t j = 0; j < numeric_features_.size(); ++j ) {
                const Feature *feature = new Feature(std::string("idx(") + numeric_features_[j]->name() + "," + std::to_string(i) + ")", false);
                fond->idx_features_.push_back(feature);
                fond->add_feature(feature);
            }
        }

        fond->ctr_features_.clear();
        for( int i = 0; i <= loop_nesting; ++i ) {
            for( int k = 0; k <= d; ++k ) {
                const Feature *feature = new Feature(std::string("ctr(") + std::to_string(i) + "," + std::to_string(k) + ")", false);
                fond->ctr_features_.push_back(feature);
                fond->add_feature(feature);
            }
        }
    }

    return fond;
}

inline Problem* Problem::translate(int d, int loop_nesting) const {
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
    Problem *fond = create_fond(d, loop_nesting);
    translate(fond, d, loop_nesting);
    return fond;
}

}; // namespace QNP

inline std::ostream& operator<<(std::ostream &os, const QNP::Problem &qnp) {
    qnp.dump(os);
    return os;
}

#endif

