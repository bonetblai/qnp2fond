(define (domain FOND_blocks-clear-x_3_0)
    (:requirements :non-deterministic)
    (:types counter)
    (:constants nabove_A nother_A - counter)
    (:predicates
        (zero ?c - counter)
        (q ?c - counter)
        (hold_A)
        (hold-other_A)
        (some-below_A)
        (bit_0)
        (bit_1)
        (bit_2)
        (bit_3)
    )

    (:action Set_nabove_A_0
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bit_0))
        :effect (and (q nabove_A) (not (bit_0)))
    )
    (:action Set_nabove_A_1
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bit_1) (not (bit_0)))
        :effect (and (q nabove_A) (not (bit_1)) (bit_0))
    )
    (:action Set_nabove_A_2
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bit_2) (not (bit_1)) (not (bit_0)))
        :effect (and (q nabove_A) (not (bit_2)) (bit_1) (bit_0))
    )
    (:action Set_nabove_A_3
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bit_3) (not (bit_2)) (not (bit_1)) (not (bit_0)))
        :effect (and (q nabove_A) (not (bit_3)) (bit_2) (bit_1) (bit_0))
    )
    (:action Set_nother_A_0
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bit_0))
        :effect (and (q nother_A) (not (bit_0)))
    )
    (:action Set_nother_A_1
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bit_1) (not (bit_0)))
        :effect (and (q nother_A) (not (bit_1)) (bit_0))
    )
    (:action Set_nother_A_2
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bit_2) (not (bit_1)) (not (bit_0)))
        :effect (and (q nother_A) (not (bit_2)) (bit_1) (bit_0))
    )
    (:action Set_nother_A_3
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bit_3) (not (bit_2)) (not (bit_1)) (not (bit_0)))
        :effect (and (q nother_A) (not (bit_3)) (bit_2) (bit_1) (bit_0))
    )
    (:action Unset_nabove_A
        :precondition (and (q nabove_A))
        :effect (and (not (q nabove_A)))
    )
    (:action Unset_nother_A
        :precondition (and (q nother_A))
        :effect (and (not (q nother_A)))
    )
    (:action Pick-x-some-below
        :precondition (and (zero nabove_A) (not (hold_A)) (not (hold-other_A)) (some-below_A) (not (q nother_A)))
        :effect (and (not (zero nother_A)) (hold_A) (not (some-below_A)))
    )
    (:action Pick-x-none-below
        :precondition (and (zero nabove_A) (not (hold_A)) (not (hold-other_A)) (not (some-below_A)))
        :effect (and (hold_A))
    )
    (:action Pick-above-x
        :precondition (and (not (zero nabove_A)) (not (hold_A)) (not (hold-other_A)) (q nabove_A))
        :effect (and (oneof (zero nabove_A) (not (zero nabove_A))) (hold-other_A))
    )
    (:action Pick-other
        :precondition (and (not (zero nother_A)) (not (hold_A)) (not (hold-other_A)) (q nother_A))
        :effect (and (oneof (zero nother_A) (not (zero nother_A))) (hold-other_A))
    )
    (:action Put-x-on-table
        :precondition (and (hold_A))
        :effect (and (not (hold_A)))
    )
    (:action Put-x-above-some
        :precondition (and (not (zero nother_A)) (hold_A) (q nother_A))
        :effect (and (oneof (zero nother_A) (not (zero nother_A))) (not (hold_A)) (some-below_A))
    )
    (:action Put-aside
        :precondition (and (hold-other_A) (not (q nother_A)))
        :effect (and (not (zero nother_A)) (not (hold-other_A)))
    )
    (:action Put-above-x
        :precondition (and (hold-other_A) (not (q nabove_A)))
        :effect (and (not (zero nabove_A)) (not (hold-other_A)))
    )
)

