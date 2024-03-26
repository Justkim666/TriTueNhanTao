ptu(H, [H|_]) :- !.
ptu(H, [_|T]:- ptu(H, T).