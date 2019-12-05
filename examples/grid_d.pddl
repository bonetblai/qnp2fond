(define (domain FOND_direct_direct)
    (:requirements :non-deterministic)
    (:types variable depth bit)
    (:constants delta_X delta_Y - variable d0 d1 d2 d3 - depth b0 b1 b2 - bit)
    (:predicates
        (zero ?X - variable)
        (stack-depth ?d - depth)
        (stack-index ?X - variable ?d - depth)
        (stack-in ?X - variable)
        (counter ?d - depth ?b - bit)
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

