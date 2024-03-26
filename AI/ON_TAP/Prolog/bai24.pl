add_list([],[],[]) :- !.
add_list([H|T],L2,[H|T1]) :- add_list(T,L2,T1), !.
add_list([],[H|T],[H|T1]) :- add_list([],T,T1).