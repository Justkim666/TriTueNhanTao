person(marcus).
pompeian(marcus).
lama(X) :- pompeian(X).
lord(ceasar).
trytokill(X, Y) :- lama(X), notloyalty(X, Y).
notloyalty(marcus, ceasar).