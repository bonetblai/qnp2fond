(define (domain FOND_full_complete_5_4)
    (:requirements :non-deterministic)
    (:types variable depth bit)
    (:constants balls-at-source carrying free-grippers - variable d0 d1 d2 d3 d4 - depth b0 b1 b2 b3 b4 - bit)
    (:predicates
        (zero ?X - variable)
        (stack-depth ?d - depth)
        (stack-index ?X - variable ?d - depth)
        (stack-in ?X - variable)
        (counter ?d - depth ?b - bit)
        (at-target)
    )

    (:action PUSH_at_d0_b0
        :parameters (?X - variable)
        :precondition (and (stack-depth d0) (not (counter d0 b0)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (stack-in ?X) (stack-index ?X d1) (counter d0 b0))
    )
    (:action PUSH_at_d0_b1
        :parameters (?X - variable)
        :precondition (and (stack-depth d0) (counter d0 b0) (not (counter d0 b1)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (stack-in ?X) (stack-index ?X d1) (not (counter d0 b0)) (counter d0 b1))
    )
    (:action PUSH_at_d0_b2
        :parameters (?X - variable)
        :precondition (and (stack-depth d0) (counter d0 b0) (counter d0 b1) (not (counter d0 b2)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (stack-in ?X) (stack-index ?X d1) (not (counter d0 b0)) (not (counter d0 b1)) (counter d0 b2))
    )
    (:action PUSH_at_d0_b3
        :parameters (?X - variable)
        :precondition (and (stack-depth d0) (counter d0 b0) (counter d0 b1) (counter d0 b2) (not (counter d0 b3)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (stack-in ?X) (stack-index ?X d1) (not (counter d0 b0)) (not (counter d0 b1)) (not (counter d0 b2)) (counter d0 b3))
    )
    (:action PUSH_at_d0_b4
        :parameters (?X - variable)
        :precondition (and (stack-depth d0) (counter d0 b0) (counter d0 b1) (counter d0 b2) (counter d0 b3) (not (counter d0 b4)))
        :effect (and (not (stack-depth d0)) (stack-depth d1) (stack-in ?X) (stack-index ?X d1) (not (counter d0 b0)) (not (counter d0 b1)) (not (counter d0 b2)) (not (counter d0 b3)) (counter d0 b4))
    )
    (:action PUSH_at_d1_b0
        :parameters (?X - variable)
        :precondition (and (stack-depth d1) (not (stack-in ?X)) (not (counter d1 b0)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (stack-in ?X) (stack-index ?X d2) (counter d1 b0))
    )
    (:action PUSH_at_d1_b1
        :parameters (?X - variable)
        :precondition (and (stack-depth d1) (not (stack-in ?X)) (counter d1 b0) (not (counter d1 b1)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (stack-in ?X) (stack-index ?X d2) (not (counter d1 b0)) (counter d1 b1))
    )
    (:action PUSH_at_d1_b2
        :parameters (?X - variable)
        :precondition (and (stack-depth d1) (not (stack-in ?X)) (counter d1 b0) (counter d1 b1) (not (counter d1 b2)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (stack-in ?X) (stack-index ?X d2) (not (counter d1 b0)) (not (counter d1 b1)) (counter d1 b2))
    )
    (:action PUSH_at_d1_b3
        :parameters (?X - variable)
        :precondition (and (stack-depth d1) (not (stack-in ?X)) (counter d1 b0) (counter d1 b1) (counter d1 b2) (not (counter d1 b3)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (stack-in ?X) (stack-index ?X d2) (not (counter d1 b0)) (not (counter d1 b1)) (not (counter d1 b2)) (counter d1 b3))
    )
    (:action PUSH_at_d1_b4
        :parameters (?X - variable)
        :precondition (and (stack-depth d1) (not (stack-in ?X)) (counter d1 b0) (counter d1 b1) (counter d1 b2) (counter d1 b3) (not (counter d1 b4)))
        :effect (and (not (stack-depth d1)) (stack-depth d2) (stack-in ?X) (stack-index ?X d2) (not (counter d1 b0)) (not (counter d1 b1)) (not (counter d1 b2)) (not (counter d1 b3)) (counter d1 b4))
    )
    (:action PUSH_at_d2_b0
        :parameters (?X - variable)
        :precondition (and (stack-depth d2) (not (stack-in ?X)) (not (counter d2 b0)))
        :effect (and (not (stack-depth d2)) (stack-depth d3) (stack-in ?X) (stack-index ?X d3) (counter d2 b0))
    )
    (:action PUSH_at_d2_b1
        :parameters (?X - variable)
        :precondition (and (stack-depth d2) (not (stack-in ?X)) (counter d2 b0) (not (counter d2 b1)))
        :effect (and (not (stack-depth d2)) (stack-depth d3) (stack-in ?X) (stack-index ?X d3) (not (counter d2 b0)) (counter d2 b1))
    )
    (:action PUSH_at_d2_b2
        :parameters (?X - variable)
        :precondition (and (stack-depth d2) (not (stack-in ?X)) (counter d2 b0) (counter d2 b1) (not (counter d2 b2)))
        :effect (and (not (stack-depth d2)) (stack-depth d3) (stack-in ?X) (stack-index ?X d3) (not (counter d2 b0)) (not (counter d2 b1)) (counter d2 b2))
    )
    (:action PUSH_at_d2_b3
        :parameters (?X - variable)
        :precondition (and (stack-depth d2) (not (stack-in ?X)) (counter d2 b0) (counter d2 b1) (counter d2 b2) (not (counter d2 b3)))
        :effect (and (not (stack-depth d2)) (stack-depth d3) (stack-in ?X) (stack-index ?X d3) (not (counter d2 b0)) (not (counter d2 b1)) (not (counter d2 b2)) (counter d2 b3))
    )
    (:action PUSH_at_d2_b4
        :parameters (?X - variable)
        :precondition (and (stack-depth d2) (not (stack-in ?X)) (counter d2 b0) (counter d2 b1) (counter d2 b2) (counter d2 b3) (not (counter d2 b4)))
        :effect (and (not (stack-depth d2)) (stack-depth d3) (stack-in ?X) (stack-index ?X d3) (not (counter d2 b0)) (not (counter d2 b1)) (not (counter d2 b2)) (not (counter d2 b3)) (counter d2 b4))
    )
    (:action PUSH_at_d3_b0
        :parameters (?X - variable)
        :precondition (and (stack-depth d3) (not (stack-in ?X)) (not (counter d3 b0)))
        :effect (and (not (stack-depth d3)) (stack-depth d4) (stack-in ?X) (stack-index ?X d4) (counter d3 b0))
    )
    (:action PUSH_at_d3_b1
        :parameters (?X - variable)
        :precondition (and (stack-depth d3) (not (stack-in ?X)) (counter d3 b0) (not (counter d3 b1)))
        :effect (and (not (stack-depth d3)) (stack-depth d4) (stack-in ?X) (stack-index ?X d4) (not (counter d3 b0)) (counter d3 b1))
    )
    (:action PUSH_at_d3_b2
        :parameters (?X - variable)
        :precondition (and (stack-depth d3) (not (stack-in ?X)) (counter d3 b0) (counter d3 b1) (not (counter d3 b2)))
        :effect (and (not (stack-depth d3)) (stack-depth d4) (stack-in ?X) (stack-index ?X d4) (not (counter d3 b0)) (not (counter d3 b1)) (counter d3 b2))
    )
    (:action PUSH_at_d3_b3
        :parameters (?X - variable)
        :precondition (and (stack-depth d3) (not (stack-in ?X)) (counter d3 b0) (counter d3 b1) (counter d3 b2) (not (counter d3 b3)))
        :effect (and (not (stack-depth d3)) (stack-depth d4) (stack-in ?X) (stack-index ?X d4) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (counter d3 b3))
    )
    (:action PUSH_at_d3_b4
        :parameters (?X - variable)
        :precondition (and (stack-depth d3) (not (stack-in ?X)) (counter d3 b0) (counter d3 b1) (counter d3 b2) (counter d3 b3) (not (counter d3 b4)))
        :effect (and (not (stack-depth d3)) (stack-depth d4) (stack-in ?X) (stack-index ?X d4) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (not (counter d3 b3)) (counter d3 b4))
    )
    (:action POP_at_d1
        :parameters (?X - variable)
        :precondition (and (stack-depth d1) (stack-index ?X d1) (stack-in ?X))
        :effect (and (not (stack-depth d1)) (not (stack-index ?X d1)) (not (stack-in ?X)) (stack-depth d0))
    )
    (:action POP_at_d2
        :parameters (?X - variable)
        :precondition (and (stack-depth d2) (stack-index ?X d2) (stack-in ?X))
        :effect (and (not (stack-depth d2)) (not (stack-index ?X d2)) (not (stack-in ?X)) (stack-depth d1))
    )
    (:action POP_at_d3
        :parameters (?X - variable)
        :precondition (and (stack-depth d3) (stack-index ?X d3) (stack-in ?X))
        :effect (and (not (stack-depth d3)) (not (stack-index ?X d3)) (not (stack-in ?X)) (stack-depth d2))
    )
    (:action POP_at_d4
        :parameters (?X - variable)
        :precondition (and (stack-depth d4) (stack-index ?X d4) (stack-in ?X))
        :effect (and (not (stack-depth d4)) (not (stack-index ?X d4)) (not (stack-in ?X)) (stack-depth d3))
    )
    (:action MOVE_b0
        :precondition (and (stack-depth d0) (not (top-counter b0)))
        :effect (and (top-counter 0))
    )
    (:action MOVE_b1
        :precondition (and (stack-depth d0) (top-counter b0) (not (top-counter b1)))
        :effect (and (not (top-counter b0)) (top-counter 1))
    )
    (:action MOVE_b2
        :precondition (and (stack-depth d0) (top-counter b0) (top-counter b1) (not (top-counter b2)))
        :effect (and (not (top-counter b0)) (not (top-counter b1)) (top-counter 2))
    )
    (:action MOVE_b3
        :precondition (and (stack-depth d0) (top-counter b0) (top-counter b1) (top-counter b2) (not (top-counter b3)))
        :effect (and (not (top-counter b0)) (not (top-counter b1)) (not (top-counter b2)) (top-counter 3))
    )
    (:action MOVE_b4
        :precondition (and (stack-depth d0) (top-counter b0) (top-counter b1) (top-counter b2) (top-counter b3) (not (top-counter b4)))
        :effect (and (not (top-counter b0)) (not (top-counter b1)) (not (top-counter b2)) (not (top-counter b3)) (top-counter 4))
    )
    (:action Drop-at-source_f0_d1
        :precondition (and (not (at-target)) (not (zero carrying)) (stack-index carrying d1) (not (stack-in balls-at-source)) (not (stack-in free-grippers)))
        :effect (and (oneof (zero carrying) (not (zero carrying))) (not (zero free-grippers)) (not (zero balls-at-source)) (not (counter d1 b0)) (not (counter d1 b1)) (not (counter d1 b2)) (not (counter d1 b3)) (not (counter d1 b4)) (not (counter d2 b0)) (not (counter d2 b1)) (not (counter d2 b2)) (not (counter d2 b3)) (not (counter d2 b4)) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (not (counter d3 b3)) (not (counter d3 b4)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Drop-at-source_f0_d2
        :precondition (and (not (at-target)) (not (zero carrying)) (stack-index carrying d2) (not (stack-in balls-at-source)) (not (stack-in free-grippers)))
        :effect (and (oneof (zero carrying) (not (zero carrying))) (not (zero free-grippers)) (not (zero balls-at-source)) (not (counter d2 b0)) (not (counter d2 b1)) (not (counter d2 b2)) (not (counter d2 b3)) (not (counter d2 b4)) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (not (counter d3 b3)) (not (counter d3 b4)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Drop-at-source_f0_d3
        :precondition (and (not (at-target)) (not (zero carrying)) (stack-index carrying d3) (not (stack-in balls-at-source)) (not (stack-in free-grippers)))
        :effect (and (oneof (zero carrying) (not (zero carrying))) (not (zero free-grippers)) (not (zero balls-at-source)) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (not (counter d3 b3)) (not (counter d3 b4)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Drop-at-source_f0_d4
        :precondition (and (not (at-target)) (not (zero carrying)) (stack-index carrying d4) (not (stack-in balls-at-source)) (not (stack-in free-grippers)))
        :effect (and (oneof (zero carrying) (not (zero carrying))) (not (zero free-grippers)) (not (zero balls-at-source)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Drop-at-target_f0_d1
        :precondition (and (at-target) (not (zero carrying)) (stack-index carrying d1) (not (stack-in free-grippers)))
        :effect (and (oneof (zero carrying) (not (zero carrying))) (not (zero free-grippers)) (not (counter d1 b0)) (not (counter d1 b1)) (not (counter d1 b2)) (not (counter d1 b3)) (not (counter d1 b4)) (not (counter d2 b0)) (not (counter d2 b1)) (not (counter d2 b2)) (not (counter d2 b3)) (not (counter d2 b4)) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (not (counter d3 b3)) (not (counter d3 b4)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Drop-at-target_f0_d2
        :precondition (and (at-target) (not (zero carrying)) (stack-index carrying d2) (not (stack-in free-grippers)))
        :effect (and (oneof (zero carrying) (not (zero carrying))) (not (zero free-grippers)) (not (counter d2 b0)) (not (counter d2 b1)) (not (counter d2 b2)) (not (counter d2 b3)) (not (counter d2 b4)) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (not (counter d3 b3)) (not (counter d3 b4)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Drop-at-target_f0_d3
        :precondition (and (at-target) (not (zero carrying)) (stack-index carrying d3) (not (stack-in free-grippers)))
        :effect (and (oneof (zero carrying) (not (zero carrying))) (not (zero free-grippers)) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (not (counter d3 b3)) (not (counter d3 b4)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Drop-at-target_f0_d4
        :precondition (and (at-target) (not (zero carrying)) (stack-index carrying d4) (not (stack-in free-grippers)))
        :effect (and (oneof (zero carrying) (not (zero carrying))) (not (zero free-grippers)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Pick-at-source_f0_d1
        :precondition (and (not (at-target)) (not (zero balls-at-source)) (not (zero free-grippers)) (stack-index balls-at-source d1) (not (stack-in carrying)))
        :effect (and (oneof (zero balls-at-source) (not (zero balls-at-source))) (oneof (zero free-grippers) (not (zero free-grippers))) (not (zero carrying)) (not (counter d1 b0)) (not (counter d1 b1)) (not (counter d1 b2)) (not (counter d1 b3)) (not (counter d1 b4)) (not (counter d2 b0)) (not (counter d2 b1)) (not (counter d2 b2)) (not (counter d2 b3)) (not (counter d2 b4)) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (not (counter d3 b3)) (not (counter d3 b4)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Pick-at-source_f0_d2
        :precondition (and (not (at-target)) (not (zero balls-at-source)) (not (zero free-grippers)) (stack-index balls-at-source d2) (not (stack-in carrying)))
        :effect (and (oneof (zero balls-at-source) (not (zero balls-at-source))) (oneof (zero free-grippers) (not (zero free-grippers))) (not (zero carrying)) (not (counter d2 b0)) (not (counter d2 b1)) (not (counter d2 b2)) (not (counter d2 b3)) (not (counter d2 b4)) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (not (counter d3 b3)) (not (counter d3 b4)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Pick-at-source_f0_d3
        :precondition (and (not (at-target)) (not (zero balls-at-source)) (not (zero free-grippers)) (stack-index balls-at-source d3) (not (stack-in carrying)))
        :effect (and (oneof (zero balls-at-source) (not (zero balls-at-source))) (oneof (zero free-grippers) (not (zero free-grippers))) (not (zero carrying)) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (not (counter d3 b3)) (not (counter d3 b4)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Pick-at-source_f0_d4
        :precondition (and (not (at-target)) (not (zero balls-at-source)) (not (zero free-grippers)) (stack-index balls-at-source d4) (not (stack-in carrying)))
        :effect (and (oneof (zero balls-at-source) (not (zero balls-at-source))) (oneof (zero free-grippers) (not (zero free-grippers))) (not (zero carrying)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Pick-at-source_f1_d1
        :precondition (and (not (at-target)) (not (zero balls-at-source)) (not (zero free-grippers)) (stack-index free-grippers d1) (not (stack-in carrying)))
        :effect (and (oneof (zero balls-at-source) (not (zero balls-at-source))) (oneof (zero free-grippers) (not (zero free-grippers))) (not (zero carrying)) (not (counter d1 b0)) (not (counter d1 b1)) (not (counter d1 b2)) (not (counter d1 b3)) (not (counter d1 b4)) (not (counter d2 b0)) (not (counter d2 b1)) (not (counter d2 b2)) (not (counter d2 b3)) (not (counter d2 b4)) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (not (counter d3 b3)) (not (counter d3 b4)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Pick-at-source_f1_d2
        :precondition (and (not (at-target)) (not (zero balls-at-source)) (not (zero free-grippers)) (stack-index free-grippers d2) (not (stack-in carrying)))
        :effect (and (oneof (zero balls-at-source) (not (zero balls-at-source))) (oneof (zero free-grippers) (not (zero free-grippers))) (not (zero carrying)) (not (counter d2 b0)) (not (counter d2 b1)) (not (counter d2 b2)) (not (counter d2 b3)) (not (counter d2 b4)) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (not (counter d3 b3)) (not (counter d3 b4)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Pick-at-source_f1_d3
        :precondition (and (not (at-target)) (not (zero balls-at-source)) (not (zero free-grippers)) (stack-index free-grippers d3) (not (stack-in carrying)))
        :effect (and (oneof (zero balls-at-source) (not (zero balls-at-source))) (oneof (zero free-grippers) (not (zero free-grippers))) (not (zero carrying)) (not (counter d3 b0)) (not (counter d3 b1)) (not (counter d3 b2)) (not (counter d3 b3)) (not (counter d3 b4)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Pick-at-source_f1_d4
        :precondition (and (not (at-target)) (not (zero balls-at-source)) (not (zero free-grippers)) (stack-index free-grippers d4) (not (stack-in carrying)))
        :effect (and (oneof (zero balls-at-source) (not (zero balls-at-source))) (oneof (zero free-grippers) (not (zero free-grippers))) (not (zero carrying)) (not (counter d4 b0)) (not (counter d4 b1)) (not (counter d4 b2)) (not (counter d4 b3)) (not (counter d4 b4)))
    )
    (:action Move-to-target
        :precondition (and (not (at-target)))
        :effect (and (at-target))
    )
    (:action Move-back
        :precondition (and (at-target))
        :effect (and (not (at-target)))
    )
)

