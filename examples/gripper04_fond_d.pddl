(define (domain FOND_gripper04_5_10_model_cnf_3_0)
    (:requirements :non-deterministic)
    (:types counter bit)
    (:constants nballs_0 nballs_1 - counter b0 b1 b2 b3 - bit)
    (:predicates
        (zero ?c - counter)
        (q ?c - counter)
        (bitvalue ?b - bit)
        (holding_0)
        (holding_1)
        (room_0)
    )

    (:action Set_nballs_0_b0
        :precondition (and (not (q nballs_0)) (not (q nballs_1)) (bitvalue b0))
        :effect (and (q nballs_0) (not (bitvalue b0)))
    )
    (:action Set_nballs_0_b1
        :precondition (and (not (q nballs_0)) (not (q nballs_1)) (bitvalue b1) (not (bitvalue b0)))
        :effect (and (q nballs_0) (not (bitvalue b1)) (bitvalue b0))
    )
    (:action Set_nballs_0_b2
        :precondition (and (not (q nballs_0)) (not (q nballs_1)) (bitvalue b2) (not (bitvalue b1)) (not (bitvalue b0)))
        :effect (and (q nballs_0) (not (bitvalue b2)) (bitvalue b1) (bitvalue b0))
    )
    (:action Set_nballs_0_b3
        :precondition (and (not (q nballs_0)) (not (q nballs_1)) (bitvalue b3) (not (bitvalue b2)) (not (bitvalue b1)) (not (bitvalue b0)))
        :effect (and (q nballs_0) (not (bitvalue b3)) (bitvalue b2) (bitvalue b1) (bitvalue b0))
    )
    (:action Set_nballs_1_b0
        :precondition (and (not (q nballs_0)) (not (q nballs_1)) (bitvalue b0))
        :effect (and (q nballs_1) (not (bitvalue b0)))
    )
    (:action Set_nballs_1_b1
        :precondition (and (not (q nballs_0)) (not (q nballs_1)) (bitvalue b1) (not (bitvalue b0)))
        :effect (and (q nballs_1) (not (bitvalue b1)) (bitvalue b0))
    )
    (:action Set_nballs_1_b2
        :precondition (and (not (q nballs_0)) (not (q nballs_1)) (bitvalue b2) (not (bitvalue b1)) (not (bitvalue b0)))
        :effect (and (q nballs_1) (not (bitvalue b2)) (bitvalue b1) (bitvalue b0))
    )
    (:action Set_nballs_1_b3
        :precondition (and (not (q nballs_0)) (not (q nballs_1)) (bitvalue b3) (not (bitvalue b2)) (not (bitvalue b1)) (not (bitvalue b0)))
        :effect (and (q nballs_1) (not (bitvalue b3)) (bitvalue b2) (bitvalue b1) (bitvalue b0))
    )
    (:action Unset_nballs_0
        :precondition (and (q nballs_0))
        :effect (and (not (q nballs_0)))
    )
    (:action Unset_nballs_1
        :precondition (and (q nballs_1))
        :effect (and (not (q nballs_1)))
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
        :precondition (and (holding_0) (not (room_0)) (not (q nballs_1)))
        :effect (and (not (zero nballs_1)) (not (holding_0)) (not (room_0)))
    )
    (:action decoded-1
        :precondition (and (holding_0) (room_0) (not (q nballs_0)))
        :effect (and (not (zero nballs_0)) (not (holding_0)))
    )
    (:action decoded-3
        :precondition (and (not (zero nballs_0)) (not (holding_0)) (room_0) (q nballs_0))
        :effect (and (oneof (zero nballs_0) (not (zero nballs_0))) (holding_0))
    )
    (:action decoded-5
        :precondition (and (not (zero nballs_1)) (not (holding_0)) (not (room_0)) (q nballs_1))
        :effect (and (oneof (zero nballs_1) (not (zero nballs_1))) (holding_0) (not (room_0)))
    )
    (:action decoded-7
        :precondition (and (holding_1) (not (room_0)) (not (q nballs_1)))
        :effect (and (not (zero nballs_1)) (not (holding_1)) (not (room_0)))
    )
    (:action decoded-0
        :precondition (and (holding_1) (room_0) (not (q nballs_0)))
        :effect (and (not (zero nballs_0)) (not (holding_1)))
    )
    (:action decoded-2
        :precondition (and (not (zero nballs_0)) (not (holding_1)) (room_0) (q nballs_0))
        :effect (and (oneof (zero nballs_0) (not (zero nballs_0))) (holding_1))
    )
    (:action decoded-6
        :precondition (and (not (zero nballs_1)) (not (holding_1)) (not (room_0)) (q nballs_1))
        :effect (and (oneof (zero nballs_1) (not (zero nballs_1))) (holding_1) (not (room_0)))
    )
)

