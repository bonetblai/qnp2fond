(define (domain FOND_grid_3_2)
    (:requirements :non-deterministic)
    (:types counter depth bit)
    (:constants delta_X delta_Y - counter d0 d1 d2 - depth b0 b1 b2 b3 - bit)
    (:predicates
        (zero ?c - counter)
        (stack-depth ?d - depth)
        (stack-idx ?c - counter ?d - depth)
        (in-stack ?c - counter)
        (bitvalue ?d - depth ?b - bit)
    )

    (:action Push_delta_X_d0_b0
        :precondition (and (stack-depth d0) (bitvalue d0 b0))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack delta_X) (stack-idx delta_X d1) (not (bitvalue d0 b0)) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_delta_X_d0_b1
        :precondition (and (stack-depth d0) (bitvalue d0 b1) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack delta_X) (stack-idx delta_X d1) (not (bitvalue d0 b1)) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_delta_X_d0_b2
        :precondition (and (stack-depth d0) (bitvalue d0 b2) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack delta_X) (stack-idx delta_X d1) (not (bitvalue d0 b2)) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_delta_X_d0_b3
        :precondition (and (stack-depth d0) (bitvalue d0 b3) (not (bitvalue d0 b2)) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack delta_X) (stack-idx delta_X d1) (not (bitvalue d0 b3)) (bitvalue d0 b2) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_delta_Y_d0_b0
        :precondition (and (stack-depth d0) (not (in-stack delta_Y)) (bitvalue d0 b0))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack delta_Y) (stack-idx delta_Y d1) (not (bitvalue d0 b0)) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_delta_Y_d0_b1
        :precondition (and (stack-depth d0) (not (in-stack delta_Y)) (bitvalue d0 b1) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack delta_Y) (stack-idx delta_Y d1) (not (bitvalue d0 b1)) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_delta_Y_d0_b2
        :precondition (and (stack-depth d0) (not (in-stack delta_Y)) (bitvalue d0 b2) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack delta_Y) (stack-idx delta_Y d1) (not (bitvalue d0 b2)) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_delta_Y_d0_b3
        :precondition (and (stack-depth d0) (not (in-stack delta_Y)) (bitvalue d0 b3) (not (bitvalue d0 b2)) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack delta_Y) (stack-idx delta_Y d1) (not (bitvalue d0 b3)) (bitvalue d0 b2) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_delta_X_d1_b0
        :precondition (and (stack-depth d1) (bitvalue d1 b0))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack delta_X) (stack-idx delta_X d2) (not (bitvalue d1 b0)) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_delta_X_d1_b1
        :precondition (and (stack-depth d1) (bitvalue d1 b1) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack delta_X) (stack-idx delta_X d2) (not (bitvalue d1 b1)) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_delta_X_d1_b2
        :precondition (and (stack-depth d1) (bitvalue d1 b2) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack delta_X) (stack-idx delta_X d2) (not (bitvalue d1 b2)) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_delta_X_d1_b3
        :precondition (and (stack-depth d1) (bitvalue d1 b3) (not (bitvalue d1 b2)) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack delta_X) (stack-idx delta_X d2) (not (bitvalue d1 b3)) (bitvalue d1 b2) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_delta_Y_d1_b0
        :precondition (and (stack-depth d1) (not (in-stack delta_Y)) (bitvalue d1 b0))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack delta_Y) (stack-idx delta_Y d2) (not (bitvalue d1 b0)) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_delta_Y_d1_b1
        :precondition (and (stack-depth d1) (not (in-stack delta_Y)) (bitvalue d1 b1) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack delta_Y) (stack-idx delta_Y d2) (not (bitvalue d1 b1)) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_delta_Y_d1_b2
        :precondition (and (stack-depth d1) (not (in-stack delta_Y)) (bitvalue d1 b2) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack delta_Y) (stack-idx delta_Y d2) (not (bitvalue d1 b2)) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_delta_Y_d1_b3
        :precondition (and (stack-depth d1) (not (in-stack delta_Y)) (bitvalue d1 b3) (not (bitvalue d1 b2)) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack delta_Y) (stack-idx delta_Y d2) (not (bitvalue d1 b3)) (bitvalue d1 b2) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Pop_delta_X_d1
        :precondition (and (stack-depth d1) (in-stack delta_X) (stack-idx delta_X d1))
        :effect (and (stack-depth d0) (not (stack-depth d1)) (not (in-stack delta_X)) (not (stack-idx delta_X d1)))
    )
    (:action Pop_delta_Y_d1
        :precondition (and (stack-depth d1) (in-stack delta_Y) (stack-idx delta_Y d1))
        :effect (and (stack-depth d0) (not (stack-depth d1)) (not (in-stack delta_Y)) (not (stack-idx delta_Y d1)))
    )
    (:action Pop_delta_X_d2
        :precondition (and (stack-depth d2) (in-stack delta_X) (stack-idx delta_X d2))
        :effect (and (stack-depth d1) (not (stack-depth d2)) (not (in-stack delta_X)) (not (stack-idx delta_X d2)))
    )
    (:action Pop_delta_Y_d2
        :precondition (and (stack-depth d2) (in-stack delta_Y) (stack-idx delta_Y d2))
        :effect (and (stack-depth d1) (not (stack-depth d2)) (not (in-stack delta_Y)) (not (stack-idx delta_Y d2)))
    )
    (:action Move-in-row_d1
        :precondition (and (not (zero delta_X)) (in-stack delta_X) (stack-idx delta_X d1))
        :effect (and (oneof (zero delta_X) (not (zero delta_X))) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Move-in-column_d1
        :precondition (and (not (zero delta_Y)) (in-stack delta_Y) (stack-idx delta_Y d1))
        :effect (and (oneof (zero delta_Y) (not (zero delta_Y))) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
)

