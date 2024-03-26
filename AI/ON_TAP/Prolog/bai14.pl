noids([],[],[]) :- !.
noids([H|T],L2,[H|T1]) :- noids(T,L2,T1).
noids([],[H|T],[H|T1]) :- noids([],T,T1).