member1(X, [X|_]) :- !.
member1(X, [Y|L]) :- X \= Y, member1(X, L).