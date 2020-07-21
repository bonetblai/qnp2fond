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
    std::vector<int> extra_;
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

    void add_base(const QNP &qnp, FOND *fond) const {
        // types
        fond->add_type("variable");

        // constants
        std::vector<std::string> variables;
        for( int i = 0; i < qnp.num_numeric_features(); ++i ) {
            const Feature *feature = &qnp.numeric_feature(i);
            variables.push_back(PDDL_name(feature->name()));
        }
        fond->add_constants("variable", variables);

        // predicates
        fond->add_predicate("zero", { { "?X", "variable" } });
    }

    FOND* direct_translation(const QNP &qnp) const {
        FOND *fond = new FOND(std::string("FOND_direct_") + name_);
	add_base(qnp, fond);

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

class Complete : public Translation {
  protected:
    const int num_bits_per_counter_;
    const int max_stack_depth_;
    const bool disable_optimizations_;

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
    mutable std::vector<const Action*> push_actions_;
    mutable std::vector<const Action*> pop_actions_;
    mutable std::vector<const Action*> move_actions_;
    void create_push_actions(const QNP &qnp, FOND &fond) const {
        for( int d = 0; d < max_stack_depth_; ++d ) {
            for( int bit = 0; bit < num_bits_per_counter_; ++bit ) {
                Action *a = new Push(d, bit, num_bits_per_counter_);
                fond.add_action(a);
                push_actions_.push_back(a);
            }
        }
    }
    void create_pop_actions(const QNP &qnp, FOND &fond) const {
        for( int d = 1; d <= max_stack_depth_; ++d ) {
            Action *a = new Pop(d);
            fond.add_action(a);
            pop_actions_.push_back(a);
        }
    }
    void create_move_actions(const QNP &qnp, FOND &fond) const {
        for( int bit = 0; bit < num_bits_per_counter_; ++bit ) {
            Action *a = new Move(bit, num_bits_per_counter_);
            fond.add_action(a);
            move_actions_.push_back(a);
        }
    }

    // create base FOND problem (i.e. FOND problem without actions)
    FOND* create_base(const QNP &qnp) const {
        std::string name = std::string("FOND_full_") +
          name_ +
          "_" + std::to_string(num_bits_per_counter_) +
          "_" + std::to_string(max_stack_depth_);
        FOND *fond = new FOND(name);

        // types
        fond->add_type("variable");
        fond->add_type("depth");
        fond->add_type("bit");

        // constants
        std::vector<std::string> variables;
        for( int i = 0; i < qnp.num_numeric_features(); ++i ) {
            const Feature *feature = &qnp.numeric_feature(i);
            variables.push_back(PDDL_name(feature->name()));
        }
        fond->add_constants("variable", variables);

        std::vector<std::string> depths;
        for( int d = 0; d <= max_stack_depth_; ++d )
            depths.push_back(std::string("d") + std::to_string(d));
        fond->add_constants("depth", depths);

        std::vector<std::string> bits;
        for( int b = 0; b < num_bits_per_counter_; ++b )
            bits.push_back(std::string("b") + std::to_string(b));
        fond->add_constants("bit", bits);

        // predicates
        fond->add_predicate("zero", { { "?X", "variable" } });
        fond->add_predicate("stack-depth", { { "?d", "depth" } });
        fond->add_predicate("stack-index", { { "?X", "variable" }, { "?d", "depth" } });
        fond->add_predicate("stack-in", { { "?X", "variable" } });
        fond->add_predicate("counter", { { "?d", "depth" }, { "?b", "bit" } });
        for( int i = 0; i < qnp.num_boolean_features(); ++i ) {
            const Feature *feature = &qnp.boolean_feature(i);
            fond->add_predicate(PDDL_name(feature->name()));
        }

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
    void translate_qnp_action(const QNP &qnp, const Action &action, FOND &fond) const {
        // checks whether there is some decremented variable that is incremented by other action
        bool dec_var_that_is_incremented_by_other_action = false;
        for( std::set<const Feature*>::const_iterator it = action.decrements().begin(); !dec_var_that_is_incremented_by_other_action && (it != action.decrements().end()); ++it ) {
            const Feature *X = *it;
            assert((X != nullptr) && X->is_numeric());
            dec_var_that_is_incremented_by_other_action = qnp.incremented_features().find(X) != qnp.incremented_features().end();
        }

        if( action.decrements().empty() || (!disable_optimizations_ && !dec_var_that_is_incremented_by_other_action) ) {
            Action *clone = action.direct_translation(feature_map_);

            // extra preconditions: -in(Y) for each incremented variable Y
            for( std::set<const Feature*>::const_iterator it = action.increments().begin(); it != action.increments().end(); ++it ) {
                const Feature *Y = *it;
                assert((Y != nullptr) && Y->is_numeric());
                const Feature *in_Y = in(Y);
                assert(in_Y != nullptr);
                clone->add_precondition(in_Y, false);
            }

	    // extra effects: if some var is decrementad, such var isn't incremented by any action, reset all stack counters
	    if( !action.decrements().empty() ) {
                for( int dp = 0; dp <= max_stack_depth_; ++dp ) {
                    // reset c(dp)
                    for( int bit = 0; bit < num_bits_per_counter_; ++bit ) {
                        const Feature *counter_bit = counter(dp, bit);
                        clone->add_effect(counter_bit, false);
                    }
		}
            }

            fond.add_action(clone);
        } else {
            // generate a(X,d) actions, where X is decremented variable and d is stack depth
            int i = 0;
            for( std::set<const Feature*>::const_iterator it = action.decrements().begin(); it != action.decrements().end(); ++it, ++i ) {
                const Feature *X = *it;
                assert((X != nullptr) && X->is_numeric());

                for( int d = 1; d <= max_stack_depth_; ++d ) {
                    std::string name = action.name() +
                      "_f" + std::to_string(i) +
                      "_d" + std::to_string(d);
                    Action *clone = action.direct_translation(name, feature_map_);

                    // extra precondition: index(X,d) = var X is at depth d in stack
                    const Feature *index_X_at_d = index(X, d);
                    assert(index_X_at_d != nullptr);
                    clone->add_precondition(index_X_at_d, true);

                    // extra preconditions: -in(Y) for each incremented variable Y
                    for( std::set<const Feature*>::const_iterator jt = action.increments().begin(); jt != action.increments().end(); ++jt ) {
                        const Feature *Y = *jt;
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

                    fond.add_action(clone);
                }
            }
        }
    }

    void translate_qnp_actions(const QNP &qnp, FOND &fond) const {
        for( size_t i = 0; i < qnp.num_actions(); ++i )
            translate_qnp_action(qnp, qnp.action(i), fond);
    }
    void add_translation_actions(const QNP &qnp, FOND &fond) const {
        create_push_actions(qnp, fond);
        create_pop_actions(qnp, fond);
        create_move_actions(qnp, fond);
        translate_qnp_actions(qnp, fond);
    }

    FOND* complete_translation(const QNP &qnp) const {
        float start_time = Utils::read_time_in_seconds();
        FOND *fond = create_base(qnp);
        add_translation_actions(qnp, *fond);
        float end_time = Utils::read_time_in_seconds();

        stats_.num_actions_ = fond->num_actions();
        stats_.num_features_ = fond->num_features();
        stats_.time_in_seconds_ = end_time - start_time;
        stats_.extra_ = { num_stack_features(), num_counter_features(), int(push_actions_.size()), int(pop_actions_.size()), int(move_actions_.size()) };
        return fond;
    }

  public:
    Complete(int num_bits_per_counter, int max_stack_depth, bool disable_optimizations)
      : Translation("complete"),
        num_bits_per_counter_(num_bits_per_counter),
        max_stack_depth_(max_stack_depth),
        disable_optimizations_(disable_optimizations) {
    }
    virtual ~Complete() { }

    FOND* translate(const QNP &qnp) const override {
        return complete_translation(qnp);
    }

    int num_stack_features() const {
        return stack_in_features_.size() + stack_depth_features_.size() + stack_index_features_.size();
    }
    int num_counter_features() const {
        return counter_features_.size();
    }
};

}; // namespace Translations
}; // namespace Reductions

#endif

