divide(N, P) :- P mod N =:= 0.
divide(N, P) :- P mod N \= 0, N*N < P, N1 is N+1, divide(N1, P).
prime(P) :- \+divide(2, P).