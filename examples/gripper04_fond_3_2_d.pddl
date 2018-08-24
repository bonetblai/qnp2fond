(define (domain FOND_gripper04_5_10_model_cnf_3_2)
    (:requirements :non-deterministic)
    (:types counter depth bit)
    (:constants nballs_0 nballs_1 - counter d0 d1 d2 - depth b0 b1 b2 b3 - bit)
    (:predicates
        (zero ?c - counter)
        (stack-depth ?d - depth)
        (stack-idx ?c - counter ?d - depth)
        (in-stack ?c - counter)
        (bitvalue ?d - depth ?b - bit)
        (holding_0)
        (holding_1)
        (room_0)
    )

    (:action Push_nballs_0_d0_b0
        :precondition (and (stack-depth d0) (bitvalue d0 b0))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nballs_0) (stack-idx nballs_0 d1) (not (bitvalue d0 b0)) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nballs_0_d0_b1
        :precondition (and (stack-depth d0) (bitvalue d0 b1) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nballs_0) (stack-idx nballs_0 d1) (not (bitvalue d0 b1)) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nballs_0_d0_b2
        :precondition (and (stack-depth d0) (bitvalue d0 b2) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nballs_0) (stack-idx nballs_0 d1) (not (bitvalue d0 b2)) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nballs_0_d0_b3
        :precondition (and (stack-depth d0) (bitvalue d0 b3) (not (bitvalue d0 b2)) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nballs_0) (stack-idx nballs_0 d1) (not (bitvalue d0 b3)) (bitvalue d0 b2) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nballs_1_d0_b0
        :precondition (and (stack-depth d0) (not (in-stack nballs_1)) (bitvalue d0 b0))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nballs_1) (stack-idx nballs_1 d1) (not (bitvalue d0 b0)) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nballs_1_d0_b1
        :precondition (and (stack-depth d0) (not (in-stack nballs_1)) (bitvalue d0 b1) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nballs_1) (stack-idx nballs_1 d1) (not (bitvalue d0 b1)) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nballs_1_d0_b2
        :precondition (and (stack-depth d0) (not (in-stack nballs_1)) (bitvalue d0 b2) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nballs_1) (stack-idx nballs_1 d1) (not (bitvalue d0 b2)) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nballs_1_d0_b3
        :precondition (and (stack-depth d0) (not (in-stack nballs_1)) (bitvalue d0 b3) (not (bitvalue d0 b2)) (not (bitvalue d0 b1)) (not (bitvalue d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (in-stack nballs_1) (stack-idx nballs_1 d1) (not (bitvalue d0 b3)) (bitvalue d0 b2) (bitvalue d0 b1) (bitvalue d0 b0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3))
    )
    (:action Push_nballs_0_d1_b0
        :precondition (and (stack-depth d1) (bitvalue d1 b0))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nballs_0) (stack-idx nballs_0 d2) (not (bitvalue d1 b0)) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nballs_0_d1_b1
        :precondition (and (stack-depth d1) (bitvalue d1 b1) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nballs_0) (stack-idx nballs_0 d2) (not (bitvalue d1 b1)) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nballs_0_d1_b2
        :precondition (and (stack-depth d1) (bitvalue d1 b2) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nballs_0) (stack-idx nballs_0 d2) (not (bitvalue d1 b2)) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nballs_0_d1_b3
        :precondition (and (stack-depth d1) (bitvalue d1 b3) (not (bitvalue d1 b2)) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nballs_0) (stack-idx nballs_0 d2) (not (bitvalue d1 b3)) (bitvalue d1 b2) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nballs_1_d1_b0
        :precondition (and (stack-depth d1) (not (in-stack nballs_1)) (bitvalue d1 b0))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nballs_1) (stack-idx nballs_1 d2) (not (bitvalue d1 b0)) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nballs_1_d1_b1
        :precondition (and (stack-depth d1) (not (in-stack nballs_1)) (bitvalue d1 b1) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nballs_1) (stack-idx nballs_1 d2) (not (bitvalue d1 b1)) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nballs_1_d1_b2
        :precondition (and (stack-depth d1) (not (in-stack nballs_1)) (bitvalue d1 b2) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nballs_1) (stack-idx nballs_1 d2) (not (bitvalue d1 b2)) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Push_nballs_1_d1_b3
        :precondition (and (stack-depth d1) (not (in-stack nballs_1)) (bitvalue d1 b3) (not (bitvalue d1 b2)) (not (bitvalue d1 b1)) (not (bitvalue d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (in-stack nballs_1) (stack-idx nballs_1 d2) (not (bitvalue d1 b3)) (bitvalue d1 b2) (bitvalue d1 b1) (bitvalue d1 b0) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action Pop_nballs_0_d1
        :precondition (and (stack-depth d1) (in-stack nballs_0) (stack-idx nballs_0 d1))
        :effect (and (stack-depth d0) (not (stack-depth d1)) (not (in-stack nballs_0)) (not (stack-idx nballs_0 d1)))
    )
    (:action Pop_nballs_1_d1
        :precondition (and (stack-depth d1) (in-stack nballs_1) (stack-idx nballs_1 d1))
        :effect (and (stack-depth d0) (not (stack-depth d1)) (not (in-stack nballs_1)) (not (stack-idx nballs_1 d1)))
    )
    (:action Pop_nballs_0_d2
        :precondition (and (stack-depth d2) (in-stack nballs_0) (stack-idx nballs_0 d2))
        :effect (and (stack-depth d1) (not (stack-depth d2)) (not (in-stack nballs_0)) (not (stack-idx nballs_0 d2)))
    )
    (:action Pop_nballs_1_d2
        :precondition (and (stack-depth d2) (in-stack nballs_1) (stack-idx nballs_1 d2))
        :effect (and (stack-depth d1) (not (stack-depth d2)) (not (in-stack nballs_1)) (not (stack-idx nballs_1 d2)))
    )
    (:action decoded-8
        :precondition (and (not (room_0)))
        :effect (and (room_0))
    )
    (:action decoded-9
        :precondition (and (room_0))
        :effect (and (not (room_0)))
    )
    (:action decoded-4
        :precondition (and (holding_0) (not (room_0)) (not (in-stack nballs_1)))
        :effect (and (not (zero nballs_1)) (not (holding_0)) (not (room_0)))
    )
    (:action decoded-1
        :precondition (and (holding_0) (room_0) (not (in-stack nballs_0)))
        :effect (and (not (zero nballs_0)) (not (holding_0)))
    )
    (:action decoded-3_d1
        :precondition (and (not (zero nballs_0)) (not (holding_0)) (room_0) (in-stack nballs_0) (stack-idx nballs_0 d1))
        :effect (and (oneof (zero nballs_0) (not (zero nballs_0))) (holding_0) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action decoded-5_d1
        :precondition (and (not (zero nballs_1)) (not (holding_0)) (not (room_0)) (in-stack nballs_1) (stack-idx nballs_1 d1))
        :effect (and (oneof (zero nballs_1) (not (zero nballs_1))) (holding_0) (not (room_0)) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action decoded-7
        :precondition (and (holding_1) (not (room_0)) (not (in-stack nballs_1)))
        :effect (and (not (zero nballs_1)) (not (holding_1)) (not (room_0)))
    )
    (:action decoded-0
        :precondition (and (holding_1) (room_0) (not (in-stack nballs_0)))
        :effect (and (not (zero nballs_0)) (not (holding_1)))
    )
    (:action decoded-2_d1
        :precondition (and (not (zero nballs_0)) (not (holding_1)) (room_0) (in-stack nballs_0) (stack-idx nballs_0 d1))
        :effect (and (oneof (zero nballs_0) (not (zero nballs_0))) (holding_1) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
    (:action decoded-6_d1
        :precondition (and (not (zero nballs_1)) (not (holding_1)) (not (room_0)) (in-stack nballs_1) (stack-idx nballs_1 d1))
        :effect (and (oneof (zero nballs_1) (not (zero nballs_1))) (holding_1) (not (room_0)) (bitvalue d1 b0) (bitvalue d1 b1) (bitvalue d1 b2) (bitvalue d1 b3) (bitvalue d2 b0) (bitvalue d2 b1) (bitvalue d2 b2) (bitvalue d2 b3))
    )
)

