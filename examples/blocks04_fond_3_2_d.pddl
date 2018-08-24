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

    (:action Push_nabove_A_d0_b0
        :precondition (and (stack-depth d0) (bitvalue d0 b0))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nabove_A) (stack-idx nabove_A d1) (not (bitvalue d0 b0)) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nabove_A_d0_b1
        :precondition (and (stack-depth d0) (bitvalue d0 b1) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nabove_A) (stack-idx nabove_A d1) (not (bitvalue d0 b1)) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nabove_A_d0_b2
        :precondition (and (stack-depth d0) (bitvalue d0 b2) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nabove_A) (stack-idx nabove_A d1) (not (bitvalue d0 b2)) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nabove_A_d0_b3
        :precondition (and (stack-depth d0) (bitvalue d0 b3) (not (bitvalue d0 b2)) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nabove_A) (stack-idx nabove_A d1) (not (bitvalue d0 b3)) (bitvalue d0 b2) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nother_A_d0_b0
        :precondition (and (stack-depth d0) (not (in-stack nother_A)) (bitvalue d0 b0))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nother_A) (stack-idx nother_A d1) (not (bitvalue d0 b0)) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nother_A_d0_b1
        :precondition (and (stack-depth d0) (not (in-stack nother_A)) (bitvalue d0 b1) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nother_A) (stack-idx nother_A d1) (not (bitvalue d0 b1)) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nother_A_d0_b2
        :precondition (and (stack-depth d0) (not (in-stack nother_A)) (bitvalue d0 b2) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nother_A) (stack-idx nother_A d1) (not (bitvalue d0 b2)) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nother_A_d0_b3
        :precondition (and (stack-depth d0) (not (in-stack nother_A)) (bitvalue d0 b3) (not (bitvalue d0 b2)) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nother_A) (stack-idx nother_A d1) (not (bitvalue d0 b3)) (bitvalue d0 b2) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nabove_A_d1_b0
        :precondition (and (stack-depth d1) (bitvalue d1 b0))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nabove_A) (stack-idx nabove_A d2) (not (bitvalue d1 b0)) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nabove_A_d1_b1
        :precondition (and (stack-depth d1) (bitvalue d1 b1) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nabove_A) (stack-idx nabove_A d2) (not (bitvalue d1 b1)) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nabove_A_d1_b2
        :precondition (and (stack-depth d1) (bitvalue d1 b2) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nabove_A) (stack-idx nabove_A d2) (not (bitvalue d1 b2)) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nabove_A_d1_b3
        :precondition (and (stack-depth d1) (bitvalue d1 b3) (not (bitvalue d1 b2)) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nabove_A) (stack-idx nabove_A d2) (not (bitvalue d1 b3)) (bitvalue d1 b2) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nother_A_d1_b0
        :precondition (and (stack-depth d1) (not (in-stack nother_A)) (bitvalue d1 b0))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nother_A) (stack-idx nother_A d2) (not (bitvalue d1 b0)) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nother_A_d1_b1
        :precondition (and (stack-depth d1) (not (in-stack nother_A)) (bitvalue d1 b1) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nother_A) (stack-idx nother_A d2) (not (bitvalue d1 b1)) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nother_A_d1_b2
        :precondition (and (stack-depth d1) (not (in-stack nother_A)) (bitvalue d1 b2) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nother_A) (stack-idx nother_A d2) (not (bitvalue d1 b2)) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nother_A_d1_b3
        :precondition (and (stack-depth d1) (not (in-stack nother_A)) (bitvalue d1 b3) (not (bitvalue d1 b2)) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nother_A) (stack-idx nother_A d2) (not (bitvalue d1 b3)) (bitvalue d1 b2) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Pop_nabove_A_d1
        :precondition (and (stack-depth d1) (in-stack nabove_A) (stack-idx nabove_A d1))
        :effect (and (stack-depth d0) (not (stack-depth d1)) (not (in-stack nabove_A)) (not (stack-idx nabove_A d1)))
    )
    (:action Pop_nother_A_d1
        :precondition (and (stack-depth d1) (in-stack nother_A) (stack-idx nother_A d1))
        :effect (and (stack-depth d0) (not (stack-depth d1)) (not (in-stack nother_A)) (not (stack-idx nother_A d1)))
    )
    (:action Pop_nabove_A_d2
        :precondition (and (stack-depth d2) (in-stack nabove_A) (stack-idx nabove_A d2))
        :effect (and (stack-depth d1) (not (stack-depth d2)) (not (in-stack nabove_A)) (not (stack-idx nabove_A d2)))
    )
    (:action Pop_nother_A_d2
        :precondition (and (stack-depth d2) (in-stack nother_A) (stack-idx nother_A d2))
        :effect (and (stack-depth d1) (not (stack-depth d2)) (not (in-stack nother_A)) (not (stack-idx nother_A d2)))
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
    (:action Pick-other_d1
        :precondition (and (not (zero nother_A)) (not (hold_A)) (not (hold-other_A)) (in-stack nother_A) (stack-idx nother_A d1))
        :effect (and (oneof (zero nother_A) (not (zero nother_A))) (hold-other_A) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Put-x-on-table
        :precondition (and (hold_A))
        :effect (and (not (hold_A)))
    )
    (:action Put-x-above-some_d1
        :precondition (and (not (zero nother_A)) (hold_A) (in-stack nother_A) (stack-idx nother_A d1))
        :effect (and (oneof (zero nother_A) (not (zero nother_A))) (not (hold_A)) (some-below_A) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
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

