#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <cassert>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "qnp.h"
#include "fond.h"
#include "utils.h"

namespace Reductions {

namespace Translations {

struct Statistics {
    int num_actions_;
    int num_features_;
    float time_in_seconds_;
    Statistics() : num_actions_(0), num_features_(0), time_in_seconds_(0) { }
};

class Translation {
  protected:
    const std::string name_;
    mutable Statistics stats_;

    void copy_features(const QNP &qnp, FOND &fond, std::map<const Feature*, const Feature*> &feature_map, bool keep_types = false) const {
        for( size_t i = 0; i < qnp.num_features(); ++i ) {
            const Feature &feature = qnp.feature(i);
            bool type = keep_types && feature.is_numeric();
            const Feature *new_feature = new Feature(feature.name(), type);
            fond.add_feature(new_feature);
            assert(feature_map.count(&feature) == 0);
            feature_map.emplace(&feature, new_feature);
        }
    }
    void copy_init_and_goal(const QNP &qnp, FOND &fond, const std::map<const Feature*, const Feature*> &feature_map) const {
        for( size_t i = 0; i < qnp.num_inits(); ++i ) {
            std::pair<const Feature*, bool> p = qnp.init(i);
            assert(p.first != nullptr);
            assert(feature_map.count(p.first) > 0);
            const Feature *feature = feature_map.at(p.first);
            assert(feature != nullptr);
            fond.add_init(feature, p.second);
        }

        for( size_t i = 0; i < qnp.num_goals(); ++i ) {
            std::pair<const Feature*, bool> p = qnp.goal(i);
            assert(p.first != nullptr);
            assert(feature_map.count(p.first) > 0);
            const Feature *feature = feature_map.at(p.first);
            assert(feature != nullptr);
            fond.add_goal(feature, p.second);
        }
    }

  public:
    Translation(const std::string &name) : name_(name) { }
    virtual ~Translation() { }

    Statistics stats() const { return stats_; }

    FOND* operator()(const QNP &qnp) const {
        return translate(qnp);
    }

    virtual FOND* translate(const QNP &qnp) const = 0;

    FOND* direct_translation(const QNP &qnp) const {
        FOND *fond = new FOND(std::string("FOND_direct_") + name_);

        // all features in direct translation are boolean
        std::map<const Feature*, const Feature*> feature_map;
        copy_features(qnp, *fond, feature_map, true);

        // copy initial and goal situations
        copy_init_and_goal(qnp, *fond, feature_map);

        // copy actions
        for( size_t i = 0; i < qnp.num_actions(); ++i ) {
            const Action &action = qnp.action(i);
            Action *new_action = action.direct_translation(feature_map);
            fond->add_action(new_action);
        }

        return fond;
    }
};

class Direct : public Translation {
  public:
    Direct() : Translation("direct") { }
    virtual ~Direct() { }

    FOND* translate(const QNP &qnp) const override {
        float start_time = Utils::read_time_in_seconds();
        FOND *fond = direct_translation(qnp);
        float end_time = Utils::read_time_in_seconds();

        stats_.num_actions_ = fond->num_actions();
        stats_.num_features_ = fond->num_features();
        stats_.time_in_seconds_ = end_time - start_time;
        return fond;
    }
};

class Full : public Translation {
  protected:
    const int num_bits_per_counter_;
    const int max_stack_depth_;

    // maps features in QNP into (new) features in FOND
    mutable std::map<const Feature*, const Feature*> feature_map_;

    // features added to handle the stack
    mutable std::map<const Feature*, const Feature*> stack_in_features_;
    mutable std::map<int, const Feature*> stack_depth_features_;
    mutable std::map<std::pair<const Feature*, int>, const Feature*> stack_index_features_;

    const Feature* in(const Feature *Y) const {
        assert(stack_in_features_.count(Y) > 0);
        return stack_in_features_.at(Y);
    }
    const Feature* depth(int d) const {
        assert(stack_depth_features_.count(d) > 0);
        return stack_depth_features_.at(d);
    }
    const Feature* index(const Feature *X, int d) const {
        assert(stack_index_features_.count({ X, d }) > 0);
        return stack_index_features_.at({ X, d });
    }

    // features added to handle counters
    mutable std::map<std::pair<int, int>, const Feature*> counter_features_;

    const Feature* counter(int depth, int bit) const {
        assert(counter_features_.count({ depth, bit }) > 0);
        return counter_features_.at({ depth, bit });
    }
    const Feature* top_counter(int bit) const {
        assert(counter_features_.count({ -1, bit }) > 0);
        return counter_features_.at({ -1, bit });
    }

    // methods for translation
    void create_push_actions(const QNP &qnp, FOND &fond) const {
        for( int d = 0; d < max_stack_depth_; ++d ) {
            for( int bit = 0; bit < num_bits_per_counter_; ++bit ) {
                Action *a = new Push(d, bit, num_bits_per_counter_);
                fond.add_action(a);
            }
        }
    }
    void create_pop_actions(const QNP &qnp, FOND &fond) const {
        for( int d = 1; d <= max_stack_depth_; ++d ) {
            Action *a = new Pop(d);
            fond.add_action(a);
        }
    }
    void create_move_actions(const QNP &qnp, FOND &fond) const {
        for( int bit = 0; bit < num_bits_per_counter_; ++bit ) {
            Action *a = new Move(bit, num_bits_per_counter_);
            fond.add_action(a);
        }
    }

    // create base FOND problem (i.e. FOND problem without actions)
    FOND* create_base(const QNP &qnp) const {
        std::string name = std::string("FOND_full_") +
          name_ +
          "_" + std::to_string(num_bits_per_counter_) +
          "_" + std::to_string(max_stack_depth_);
        FOND *fond = new FOND(name);

        // all features in translation are boolean
        copy_features(qnp, *fond, feature_map_, true);

        // additional features for handling the stack
        // - in(Y)
        // - depth(d)
        // - index(X,d)
        for( int i = 0; i < qnp.num_numeric_features(); ++i ) {
            const Feature *Y = &qnp.numeric_feature(i);
            std::string name = std::string("(stack-in ") + PDDL_name(Y->name()) + ")";
            const Feature *in_Y = new Feature(name, false, true);
            stack_in_features_.emplace(Y, in_Y);
            fond->add_feature(in_Y);
        }

        for( int d = 0; d <= max_stack_depth_; ++d ) {
            std::string name = std::string("(stack-depth d") + std::to_string(d) + ")";
            const Feature *stack_depth = new Feature(name, false, true);
            stack_depth_features_.emplace(d, stack_depth);
            fond->add_feature(stack_depth);
        }

        for( int i = 0; i < qnp.num_numeric_features(); ++i ) {
            const Feature *X = &qnp.numeric_feature(i);
            for( int d = 1; d <= max_stack_depth_; ++d ) {
                std::string name = std::string("(stack-index ") + PDDL_name(X->name()) + " d" + std::to_string(d) + ")";
                const Feature *index_X_at_d = new Feature(name, false, true);
                stack_index_features_.emplace(std::make_pair(X, d), index_X_at_d);
                fond->add_feature(index_X_at_d);
            }
        }

        // additional features for handling counters
        for( int d = 0; d <= max_stack_depth_; ++d ) {
            for( int bit = 0; bit < num_bits_per_counter_; ++bit ) {
                std::string name = std::string("(counter d") + std::to_string(d) + " b" + std::to_string(bit) + ")";
                const Feature *counter_bit = new Feature(name, false, true);
                counter_features_.emplace(std::make_pair(d, bit), counter_bit);
                fond->add_feature(counter_bit);
            }
        }

        for( int bit = 0; bit < num_bits_per_counter_; ++bit ) {
            std::string name = std::string("(top-counter b") + std::to_string(bit) + ")";
            const Feature *counter_bit = new Feature(name, false, true);
            counter_features_.emplace(std::make_pair(-1, bit), counter_bit);
            fond->add_feature(counter_bit);
        }

        // copy initial and goal situations
        copy_init_and_goal(qnp, *fond, feature_map_);

        return fond;
    }

    // translation for actions
    Action* translate_qnp_action(const QNP &qnp, const Action &action, FOND &fond) const {
        Action *clone = nullptr;
        if( action.decrements().empty() ) {
            clone = action.direct_translation(feature_map_);

            // extra preconditions: -in(Y) for each incremented variable Y
            for( size_t i = 0; i < action.increments().size(); ++i ) {
                const Feature *Y = action.increments().at(i);
                assert((Y != nullptr) && Y->is_numeric());
                const Feature *in_Y = in(Y);
                assert(in_Y != nullptr);
                clone->add_precondition(in_Y, false);
            }
        } else {
            // generate a(X,d) actions, where X is decremented variable and d is stack depth
            for( size_t i = 0; i < action.decrements().size(); ++i ) {
                const Feature *X = action.decrements().at(i);
                assert((X != nullptr) && X->is_numeric());

                for( int d = 1; d <= max_stack_depth_; ++d ) {
                    std::string name = action.name() +
                      "_f" + std::to_string(i) +
                      "_d" + std::to_string(d);
                    clone = action.direct_translation(name, feature_map_);

                    // extra precondition: index(X,d) = var X is at depth d in stack
                    const Feature *index_X_at_d = index(X, d);
                    assert(index_X_at_d != nullptr);
                    clone->add_precondition(index_X_at_d, true);

                    // extra preconditions: -in(Y) for each incremented variable Y
                    for( size_t i = 0; i < action.increments().size(); ++i ) {
                        const Feature *Y = action.increments().at(i);
                        assert((Y != nullptr) && Y->is_numeric());
                        const Feature *in_Y = in(Y);
                        assert(in_Y != nullptr);
                        clone->add_precondition(in_Y, false);
                    }

                    // extra effects: reset counters for depths d and beyond
                    for( int dp = d; dp <= max_stack_depth_; ++dp ) {
                        // reset c(dp)
                        for( int bit = 0; bit < num_bits_per_counter_; ++bit ) {
                            const Feature *counter_bit = counter(dp, bit);
                            clone->add_effect(counter_bit, false);
                        }
                    }
                }
            }
        }
        assert(clone != nullptr);
        return clone;
    }

    void translate_qnp_actions(const QNP &qnp, FOND &fond) const {
        for( size_t i = 0; i < qnp.num_actions(); ++i ) {
            Action *new_action = translate_qnp_action(qnp, qnp.action(i), fond);
            fond.add_action(new_action);
        }
    }
    void add_translation_actions(const QNP &qnp, FOND &fond) const {
        create_push_actions(qnp, fond);
        create_pop_actions(qnp, fond);
        create_move_actions(qnp, fond);
        translate_qnp_actions(qnp, fond);
    }

    FOND* full_translation(const QNP &qnp) const {
        float start_time = Utils::read_time_in_seconds();
        FOND *fond = create_base(qnp);
        add_translation_actions(qnp, *fond);
        float end_time = Utils::read_time_in_seconds();

        stats_.num_actions_ = fond->num_actions();
        stats_.num_features_ = fond->num_features();
        stats_.time_in_seconds_ = end_time - start_time;
        return fond;
    }

  public:
    Full(int num_bits_per_counter, int max_stack_depth)
      : Translation("full"),
        num_bits_per_counter_(num_bits_per_counter),
        max_stack_depth_(max_stack_depth) {
    }
    virtual ~Full() { }

    FOND* translate(const QNP &qnp) const override {
        return full_translation(qnp);
    }
};

}; // namespace Translations
}; // namespace Reductions

#endif

