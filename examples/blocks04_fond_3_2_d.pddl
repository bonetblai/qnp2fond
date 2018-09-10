(define (domain FOND_blocks-clear-x_3_2)
    (:requirements :non-deterministic)
    (:types counter depth bit)
    (:constants nabove_A nother_A - counter d0 d1 d2 - depth b0 b1 b2 b3 - bit)
    (:predicates
        (zero ?c - counter)
        (stack-depth ?d - depth)
        (stack-idx ?c - counter ?d - depth)
        (in-stack ?c - counter)
        (bitvalue ?d - depth ?b - bit)
        (hold_A)
        (hold-other_A)
        (some-below_A)
    )

    (:action PUSH_d0_b0
        :parameters (?c - counter)
        :precondition (and (stack-depth d0) (bitvalue d0 b0))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack ?c) (stack-idx ?c d1) (not (bitvalue d0 b0)) (bitvalue d1 b3) (bitvalue d1 b2) (bitvalue d1 b1) (bitvalue d1 b0))
    )
    (:action PUSH_d0_b1
        :parameters (?c - counter)
        :precondition (and (stack-depth d0) (bitvalue d0 b1) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack ?c) (stack-idx ?c d1) (not (bitvalue d0 b1)) (bitvalue d0 b0) (bitvalue d1 b3) (bitvalue d1 b2) (bitvalue d1 b1) (bitvalue d1 b0))
    )
    (:action PUSH_d0_b2
        :parameters (?c - counter)
        :precondition (and (stack-depth d0) (bitvalue d0 b2) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack ?c) (stack-idx ?c d1) (not (bitvalue d0 b2)) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b3) (bitvalue d1 b2) (bitvalue d1 b1) (bitvalue d1 b0))
    )
    (:action PUSH_d0_b3
        :parameters (?c - counter)
        :precondition (and (stack-depth d0) (bitvalue d0 b3) (not (bitvalue d0 b2)) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack ?c) (stack-idx ?c d1) (not (bitvalue d0 b3)) (bitvalue d0 b2) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b3) (bitvalue d1 b2) (bitvalue d1 b1) (bitvalue d1 b0))
    )
    (:action PUSH_d1_b0
        :parameters (?c - counter)
        :precondition (and (stack-depth d1) (not (in-stack ?c)) (bitvalue d1 b0))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack ?c) (stack-idx ?c d2) (not (bitvalue d1 b0)) (bitvalue d2 b3) (bitvalue d2 b2) (bitvalue d2 b1) (bitvalue d2 b0))
    )
    (:action PUSH_d1_b1
        :parameters (?c - counter)
        :precondition (and (stack-depth d1) (not (in-stack ?c)) (bitvalue d1 b1) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack ?c) (stack-idx ?c d2) (not (bitvalue d1 b1)) (bitvalue d1 b0) (bitvalue d2 b3) (bitvalue d2 b2) (bitvalue d2 b1) (bitvalue d2 b0))
    )
    (:action PUSH_d1_b2
        :parameters (?c - counter)
        :precondition (and (stack-depth d1) (not (in-stack ?c)) (bitvalue d1 b2) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack ?c) (stack-idx ?c d2) (not (bitvalue d1 b2)) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b3) (bitvalue d2 b2) (bitvalue d2 b1) (bitvalue d2 b0))
    )
    (:action PUSH_d1_b3
        :parameters (?c - counter)
        :precondition (and (stack-depth d1) (not (in-stack ?c)) (bitvalue d1 b3) (not (bitvalue d1 b2)) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack ?c) (stack-idx ?c d2) (not (bitvalue d1 b3)) (bitvalue d1 b2) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b3) (bitvalue d2 b2) (bitvalue d2 b1) (bitvalue d2 b0))
    )
    (:action POP_d1
        :parameters (?c - counter)
        :precondition (and (stack-depth d1) (in-stack ?c) (stack-idx ?c d1))
        :effect (and (not (stack-depth d1)) (stack-depth d0) (not (in-stack ?c)) (not (stack-idx ?c d1)))
    )
    (:action POP_d2
        :parameters (?c - counter)
        :precondition (and (stack-depth d2) (in-stack ?c) (stack-idx ?c d2))
        :effect (and (not (stack-depth d2)) (stack-depth d1) (not (in-stack ?c)) (not (stack-idx ?c d2)))
    )
    (:action Pick-x-some-below
        :precondition (and (zero nabove_A) (not (hold_A)) (not (hold-other_A)) (some-below_A) (not (in-stack nother_A)))
        :effect (and (not (zero nother_A)) (hold_A) (not (some-below_A)))
    )
    (:action Pick-x-none-below
        :precondition (and (zero nabove_A) (not (hold_A)) (not (hold-other_A)) (not (some-below_A)))
        :effect (and (hold_A))
    )
    (:action Pick-above-x_d1
        :precondition (and (not (zero nabove_A)) (not (hold_A)) (not (hold-other_A)) (in-stack nabove_A) (stack-idx nabove_A d1))
        :effect (and (oneof (zero nabove_A) (not (zero nabove_A))) (hold-other_A) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Pick-above-x_d2
        :precondition (and (not (zero nabove_A)) (not (hold_A)) (not (hold-other_A)) (in-stack nabove_A) (stack-idx nabove_A d2))
        :effect (and (oneof (zero nabove_A) (not (zero nabove_A))) (hold-other_A) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Pick-other_d1
        :precondition (and (not (zero nother_A)) (not (hold_A)) (not (hold-other_A)) (in-stack nother_A) (stack-idx nother_A d1))
        :effect (and (oneof (zero nother_A) (not (zero nother_A))) (hold-other_A) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Pick-other_d2
        :precondition (and (not (zero nother_A)) (not (hold_A)) (not (hold-other_A)) (in-stack nother_A) (stack-idx nother_A d2))
        :effect (and (oneof (zero nother_A) (not (zero nother_A))) (hold-other_A) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Put-x-on-table
        :precondition (and (hold_A))
        :effect (and (not (hold_A)))
    )
    (:action Put-x-above-some_d1
        :precondition (and (not (zero nother_A)) (hold_A) (in-stack nother_A) (stack-idx nother_A d1))
        :effect (and (oneof (zero nother_A) (not (zero nother_A))) (not (hold_A)) (some-below_A) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Put-x-above-some_d2
        :precondition (and (not (zero nother_A)) (hold_A) (in-stack nother_A) (stack-idx nother_A d2))
        :effect (and (oneof (zero nother_A) (not (zero nother_A))) (not (hold_A)) (some-below_A) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Put-aside
        :precondition (and (hold-other_A) (not (in-stack nother_A)))
        :effect (and (not (zero nother_A)) (not (hold-other_A)))
    )
    (:action Put-above-x
        :precondition (and (hold-other_A) (not (in-stack nabove_A)))
        :effect (and (not (zero nabove_A)) (not (hold-other_A)))
    )
)

