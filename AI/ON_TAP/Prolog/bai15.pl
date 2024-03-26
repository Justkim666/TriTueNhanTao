tongptle([],0) :- !.
tongptle([H|T], X) :- H mod 2 =:= 1, tongptle(T, X1), X is X1 + H, !.
tongptle([_|T], X) :- tongptle(T, X).