#ifndef QNP_H
#define QNP_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

inline std::string PDDL_name(const std::string &name) {
    size_t n;
    std::string copy(name);
    for( size_t n = copy.find('('); n != std::string::npos; n = copy.find('(') )
        copy.replace(n, 1, "_");
    for( size_t n = copy.find(')'); n != std::string::npos; n = copy.find(')') )
        copy.replace(n, 1, "");
    for( size_t n = copy.find(','); n != std::string::npos; n = copy.find(',') )
        copy.replace(n, 1, "");
    //std::cout << "[" << copy << "]" << std::endl;
    return copy;
}

inline std::string PDDL_zero(const std::string &name, bool neg = false) {
    std::string zero;
    if( neg ) zero += std::string("(not ");
    zero += std::string("(zero ") + PDDL_name(name) + ")";
    if( neg ) zero += std::string(")");
    return zero;
}

inline std::string PDDL_q(const std::string &name, bool neg = false) {
    std::string q;
    if( neg ) q += std::string("(not ");
    q += std::string("(q ") + PDDL_name(name) + ")";
    if( neg ) q += std::string(")");
    return q;
}

class Feature {
  protected:
    const std::string name_;
    bool numeric_;
    bool sanitized_;

  public:
    Feature(const std::string &name, bool numeric, bool sanitized = false)
      : name_(name), numeric_(numeric), sanitized_(sanitized) {
    }
    const std::string& name() const { return name_; }
    const std::string PDDL_name(bool neg = false) const {
        std::string name;
        if( neg ) name += "(not ";
        name += sanitized_ ? name_ : std::string("(") + ::PDDL_name(name_) + ")";
        if( neg ) name += ")";
        return name;
    }
    bool numeric() const { return numeric_; }
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

inline std::ostream& operator<<(std::ostream &os, const Feature &feature) {
    feature.dump(os);
    return os;
}

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

inline std::ostream& operator<<(std::ostream &os, const Action &action) {
    action.dump(os);
    return os;
}

class QNP {
  protected:
    const std::string name_;
    std::vector<const Feature*> features_;
    std::vector<const Action*> actions_;
    std::map<std::string, const Feature*> feature_map_;

  public:
    QNP(const std::string &name) : name_(name) { }
    ~QNP() {
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

    QNP* translate(int d, int loop_nesting = 0) const {
        std::vector<const Feature*> numeric_features;
        std::vector<const Feature*> boolean_features;
        std::vector<const Feature*> q_features;
        std::vector<const Feature*> bit_features;
        for( size_t i = 0; i < features_.size(); ++i ) {
            if( features_[i]->numeric() )
                numeric_features.push_back(features_[i]);
            else
                boolean_features.push_back(features_[i]);
        }

        QNP *fond = new QNP(std::string("FOND_") + name_ + "_" + std::to_string(d));
        for( size_t i = 0; i < numeric_features.size(); ++i )
            fond->add_feature(new Feature(numeric_features[i]->name(), true));
        for( size_t i = 0; i < boolean_features.size(); ++i )
            fond->add_feature(new Feature(boolean_features[i]->name(), false));
        for( size_t i = 0; i < numeric_features.size(); ++i ) {
            //const Feature *feature = new Feature(std::string("Q(") + numeric_features[i]->name() + ")", false);
            const Feature *feature = new Feature(PDDL_q(numeric_features[i]->name()), false, true);
            q_features.push_back(feature);
            fond->add_feature(feature);
        }
        for( int i = 0; i <= d; ++i ) {
            const Feature *feature = new Feature(std::string("bit(") + std::to_string(i) + ")", false);
            bit_features.push_back(feature);
            fond->add_feature(feature);
        }

        // set actions
        for( size_t i = 0; i < numeric_features.size(); ++i ) {
            for( int t = 0; t <= d; ++t ) {
                std::string name = std::string("Set(") + numeric_features[i]->name() + "," + std::to_string(t) + ")";
                Action *action = new Action(name);
                for( size_t j = 0; j < numeric_features.size(); ++j )
                    action->add_precondition(q_features[j], false);
                action->add_precondition(bit_features[t], true);
                for( int j = t - 1; j >= 0; --j )
                    action->add_precondition(bit_features[j], false);
                action->add_effect(q_features[i], true);
                action->add_effect(bit_features[t], false);
                for( int j = t - 1; j >= 0; --j )
                    action->add_effect(bit_features[j], true);
                fond->add_action(action);
            }
        }

        // unset actions
        for( size_t i = 0; i < numeric_features.size(); ++i ) {
            std::string name = std::string("Unset(") + numeric_features[i]->name() + ")";
            Action *action = new Action(name);
            action->add_precondition(q_features[i], true);
            action->add_effect(q_features[i], false);
            fond->add_action(action);
        }

        // QNP actions
        for( size_t i = 0; i < actions_.size(); ++i ) {
            std::vector<const Feature*> features_increased;
            std::vector<const Feature*> features_decreased;
            for( size_t j = 0; j < actions_[i]->num_effects(); ++j ) {
                const Feature *feature = actions_[i]->effect(j).first;
                if( feature->numeric() && actions_[i]->effect(j).second )
                    features_increased.push_back(feature);
                else if( feature->numeric() )
                    features_decreased.push_back(feature);
            }

            if( !features_decreased.empty() ) {
                for( size_t j = 0; j < features_decreased.size(); ++j ) {
                    std::string name = actions_[i]->name();
                    if( features_decreased.size() > 1 )
                        name += std::string("_") + std::to_string(j);
                    Action *action = new Action(name);

                    // preconditions
                    for( size_t k = 0; k < actions_[i]->num_preconditions(); ++k ) {
                        const Feature *feature = actions_[i]->precondition(k).first;
                        bool value = actions_[i]->precondition(k).second;
                        action->add_precondition(fond->feature(feature->name()), value);
                    }
                    action->add_precondition(q_features[j], true);
                    for( size_t k = 0; k < features_increased.size(); ++k )
                        action->add_precondition(fond->feature(features_increased[k]->name()), false);

                    // effects
                    for( size_t k = 0; k < actions_[i]->num_effects(); ++k ) {
                        const Feature *feature = actions_[i]->effect(k).first;
                        bool value = actions_[i]->effect(k).second;
                        action->add_effect(fond->feature(feature->name()), value);
                    }
                    fond->add_action(action);
                }
            } else {
                Action *action = new Action(actions_[i]->name());

                // preconditions
                for( size_t k = 0; k < actions_[i]->num_preconditions(); ++k ) {
                    const Feature *feature = actions_[i]->precondition(k).first;
                    bool value = actions_[i]->precondition(k).second;
                    action->add_precondition(fond->feature(feature->name()), value);
                }

                // effects
                for( size_t k = 0; k < actions_[i]->num_effects(); ++k ) {
                    const Feature *feature = actions_[i]->effect(k).first;
                    bool value = actions_[i]->effect(k).second;
                    action->add_effect(fond->feature(feature->name()), value);
                }
                fond->add_action(action);
            }
        }

        return fond;
    }

    static QNP* read(std::istream &is) {
        std::string name;
        is >> name;
        QNP *qnp = new QNP(name);
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

inline std::ostream& operator<<(std::ostream &os, const QNP &qnp) {
    qnp.dump(os);
    return os;
}

#endif

