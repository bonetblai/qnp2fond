(define (problem FOND_grid_3_2_p)
    (:domain FOND_grid_3_2)
    (:init (stack-depth d0) (bitvalue d0 b0) (bitvalue d0 b1) (bitvalue d0 b2) (bitvalue d0 b3))
    (:goal (and (zero delta_X) (zero delta_Y) (stack-depth d0)))
)

