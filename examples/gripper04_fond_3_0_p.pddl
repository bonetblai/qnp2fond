(define (problem p1)
    (:domain FOND_gripper04_5_10_model_cnf_3_0)
    (:init (bitvalue b0) (bitvalue b1) (bitvalue b2) (bitvalue b3)
           (zero nballs_0) (not (zero nballs_1))
           (room_0) (not (holding_0)) (not (holding_1))
    )
    (:goal (and (room_0) (zero nballs_1) (not (holding_0)) (not (holding_1))))
)

