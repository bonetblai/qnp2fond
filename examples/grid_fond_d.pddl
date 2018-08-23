(define (domain FOND_grid_3_0)
    (:requirements :non-deterministic)
    (:types counter)
    (:constants delta_X delta_Y - counter)
    (:predicates
        (zero ?c - counter)
        (q ?c - counter)
        (bit_0)
        (bit_1)
        (bit_2)
        (bit_3)
    )

    (:action Set_delta_X_0
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bit_0))
        :effect (and (q delta_X) (not (bit_0)))
    )
    (:action Set_delta_X_1
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bit_1) (not (bit_0)))
        :effect (and (q delta_X) (not (bit_1)) (bit_0))
    )
    (:action Set_delta_X_2
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bit_2) (not (bit_1)) (not (bit_0)))
        :effect (and (q delta_X) (not (bit_2)) (bit_1) (bit_0))
    )
    (:action Set_delta_X_3
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bit_3) (not (bit_2)) (not (bit_1)) (not (bit_0)))
        :effect (and (q delta_X) (not (bit_3)) (bit_2) (bit_1) (bit_0))
    )
    (:action Set_delta_Y_0
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bit_0))
        :effect (and (q delta_Y) (not (bit_0)))
    )
    (:action Set_delta_Y_1
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bit_1) (not (bit_0)))
        :effect (and (q delta_Y) (not (bit_1)) (bit_0))
    )
    (:action Set_delta_Y_2
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bit_2) (not (bit_1)) (not (bit_0)))
        :effect (and (q delta_Y) (not (bit_2)) (bit_1) (bit_0))
    )
    (:action Set_delta_Y_3
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bit_3) (not (bit_2)) (not (bit_1)) (not (bit_0)))
        :effect (and (q delta_Y) (not (bit_3)) (bit_2) (bit_1) (bit_0))
    )
    (:action Unset_delta_X
        :precondition (and (q delta_X))
        :effect (and (not (q delta_X)))
    )
    (:action Unset_delta_Y
        :precondition (and (q delta_Y))
        :effect (and (not (q delta_Y)))
    )
    (:action Move-in-row
        :precondition (and (not (zero delta_X)) (q delta_X))
        :effect (and (oneof (zero delta_X) (not (zero delta_X))))
    )
    (:action Move-in-column
        :precondition (and (not (zero delta_Y)) (q delta_Y))
        :effect (and (oneof (zero delta_Y) (not (zero delta_Y))))
    )
)

