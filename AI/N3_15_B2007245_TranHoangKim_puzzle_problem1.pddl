(define (problem hard1)
    (:domain strips-sliding-title)
        (:objects t1 t2 t3 t4 t5 t6 t7 t8 x1 x2 x3 y1 y2 y3)
        (:init   (title t1) (title t2) (title t3) (title t4) (title t5)
                 (title t6) (title t7) (title t8)
                 (position x1) (position x2) (position x3)
                 (position y1) (position y2) (position y3)
                 (inc x1 x2) (inc x2 x3) (dec x3 x2) (dec x2 x1)
                 (inc y1 y2) (inc y2 y3) (dec y3 y2) (dec y2 y1)
                 (blank x1 y2) (at t8 x1 y1) (at t7 x2 y1) (at t6 x3 y1) (at t4 x2 y2)
                 (at t1 x3 y2) (at t2 x1 y3) (at t5 x2 y3) (at t3 x3 y3))
        (:goal (and (at t1 x2 y1) (at t2 x3 y1) (at t3 x1 y2) (at t4 x2 y2)
                     (at t5 x3 y2) (at t6 x1 y3) (at t7 x2 y3) (at t8 x3 y3))))