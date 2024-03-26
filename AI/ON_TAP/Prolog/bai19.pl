gcd(A,0,A) :- !.
gcd(A, B, D) :- R is A mod B, gcd(B, R, D).