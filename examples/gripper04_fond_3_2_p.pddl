(define (problem p1)
    (:domain FOND_gripper04_5_10_model_cnf_3_2)
    (:init (stack-depth d0) (bitvalue d0 b0) (bitvalue d0 b1) (bitvalue d0 b2) (bitvalue d0 b3)
           (zero nballs_0) (not (zero nballs_1))
           (room_0) (not (holding_0)) (not (holding_1))
    )
    (:goal (and (room_0) (zero nballs_1) (not (holding_0)) (not (holding_1))))
)

