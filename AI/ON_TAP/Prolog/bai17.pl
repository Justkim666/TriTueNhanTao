male(jamesI).
male(charleI).
male(charleII).
male(jameII).
male(georgeI).
female(catherine).
female(elizabeth).
female(sophia).
parent(jamesI, charlesI).
parent(jamesI, elizabeth).
parent(charlesI, catherine).
parent(charlesI, charlesII).
parent(charlesI, jamesII).
parent(elizabeth, sophia).
parent(sophia, georgeI).
mother(M, X) :- parent(M, X), female(M).
father(F, X) :- parent(F, X), male(F).
sibling(X, Y) :- parent(Z, X), parent(Z, Y).