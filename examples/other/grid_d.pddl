(define (domain FOND_direct_direct)
    (:requirements :non-deterministic)
    (:types variable)
    (:constants delta_X delta_Y - variable)
    (:predicates
        (zero ?X - variable)
    )

    (:action Move-in-row
        :precondition (and (not (zero delta_X)))
        :effect (and (oneof (zero delta_X) (not (zero delta_X))))
    )
    (:action Move-in-column
        :precondition (and (not (zero delta_Y)))
        :effect (and (oneof (zero delta_Y) (not (zero delta_Y))))
    )
)

