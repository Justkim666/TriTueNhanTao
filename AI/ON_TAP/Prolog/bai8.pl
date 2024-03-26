dem([],0) :- !.
dem([_|T], X) :- dem(T, X1), X is X1+1.