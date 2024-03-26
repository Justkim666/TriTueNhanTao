ptn([H|_], 1, H) :- !.
ptn([_|T], N, X) :- N1 is N - 1, ptn(T, N1, X).