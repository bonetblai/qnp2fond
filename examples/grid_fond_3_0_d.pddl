(define (domain FOND_grid_3_0)
    (:requirements :non-deterministic)
    (:types counter bit)
    (:constants delta_X delta_Y - counter b0 b1 b2 b3 - bit)
    (:predicates
        (zero ?c - counter)
        (q ?c - counter)
        (bitvalue ?b - bit)
    )

    (:action Set_delta_X_b0
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bitvalue b0))
        :effect (and (q delta_X) (not (bitvalue b0)))
    )
    (:action Set_delta_X_b1
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bitvalue b1) (not (bitvalue b0)))
        :effect (and (q delta_X) (not (bitvalue b1)) (bitvalue b0))
    )
    (:action Set_delta_X_b2
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bitvalue b2) (not (bitvalue b1)) (not (bitvalue b0)))
        :effect (and (q delta_X) (not (bitvalue b2)) (bitvalue b1) (bitvalue b0))
    )
    (:action Set_delta_X_b3
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bitvalue b3) (not (bitvalue b2)) (not (bitvalue b1)) (not (bitvalue b0)))
        :effect (and (q delta_X) (not (bitvalue b3)) (bitvalue b2) (bitvalue b1) (bitvalue b0))
    )
    (:action Set_delta_Y_b0
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bitvalue b0))
        :effect (and (q delta_Y) (not (bitvalue b0)))
    )
    (:action Set_delta_Y_b1
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bitvalue b1) (not (bitvalue b0)))
        :effect (and (q delta_Y) (not (bitvalue b1)) (bitvalue b0))
    )
    (:action Set_delta_Y_b2
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bitvalue b2) (not (bitvalue b1)) (not (bitvalue b0)))
        :effect (and (q delta_Y) (not (bitvalue b2)) (bitvalue b1) (bitvalue b0))
    )
    (:action Set_delta_Y_b3
        :precondition (and (not (q delta_X)) (not (q delta_Y)) (bitvalue b3) (not (bitvalue b2)) (not (bitvalue b1)) (not (bitvalue b0)))
        :effect (and (q delta_Y) (not (bitvalue b3)) (bitvalue b2) (bitvalue b1) (bitvalue b0))
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

