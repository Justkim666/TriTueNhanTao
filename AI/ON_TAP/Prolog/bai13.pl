thempt([],X,[X]) :- !.
thempt([H|T],X,[H|T1]) :- thempt(T,X,T1).