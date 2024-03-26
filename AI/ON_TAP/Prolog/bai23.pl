push_back(X, [], [X]) :- !.
push_back(X, [H|T], [H|T1]) :- push_back(X, T, T1).