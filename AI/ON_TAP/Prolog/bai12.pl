ptle([],[]) :- !.
ptle([H|T], [H|T1]) :- H mod 2 =:= 1, ptle(T, T1).
ptle([_|T], T1) :- ptle(T, T1).