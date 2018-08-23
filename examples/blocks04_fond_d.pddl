(define (domain FOND_blocks-clear-x_3_0)
    (:requirements :non-deterministic)
    (:types counter bit)
    (:constants nabove_A nother_A - counter b0 b1 b2 b3 - bit)
    (:predicates
        (zero ?c - counter)
        (q ?c - counter)
        (bitvalue ?b - bit)
        (hold_A)
        (hold-other_A)
        (some-below_A)
    )

    (:action Set_nabove_A_b0
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bitvalue b0))
        :effect (and (q nabove_A) (not (bitvalue b0)))
    )
    (:action Set_nabove_A_b1
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bitvalue b1) (not (bitvalue b0)))
        :effect (and (q nabove_A) (not (bitvalue b1)) (bitvalue b0))
    )
    (:action Set_nabove_A_b2
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bitvalue b2) (not (bitvalue b1)) (not (bitvalue b0)))
        :effect (and (q nabove_A) (not (bitvalue b2)) (bitvalue b1) (bitvalue b0))
    )
    (:action Set_nabove_A_b3
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bitvalue b3) (not (bitvalue b2)) (not (bitvalue b1)) (not (bitvalue b0)))
        :effect (and (q nabove_A) (not (bitvalue b3)) (bitvalue b2) (bitvalue b1) (bitvalue b0))
    )
    (:action Set_nother_A_b0
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bitvalue b0))
        :effect (and (q nother_A) (not (bitvalue b0)))
    )
    (:action Set_nother_A_b1
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bitvalue b1) (not (bitvalue b0)))
        :effect (and (q nother_A) (not (bitvalue b1)) (bitvalue b0))
    )
    (:action Set_nother_A_b2
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bitvalue b2) (not (bitvalue b1)) (not (bitvalue b0)))
        :effect (and (q nother_A) (not (bitvalue b2)) (bitvalue b1) (bitvalue b0))
    )
    (:action Set_nother_A_b3
        :precondition (and (not (q nabove_A)) (not (q nother_A)) (bitvalue b3) (not (bitvalue b2)) (not (bitvalue b1)) (not (bitvalue b0)))
        :effect (and (q nother_A) (not (bitvalue b3)) (bitvalue b2) (bitvalue b1) (bitvalue b0))
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

