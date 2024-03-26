tong([],0) :- !.
tong([H|T], X) :- tong(T, X1), X is X1 + H.