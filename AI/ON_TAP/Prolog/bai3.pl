giaithua(0, 1) :- !.
giaithua(X, Y) :- X1 is X - 1, giaithua(X1, Y1), Y is X*Y1.