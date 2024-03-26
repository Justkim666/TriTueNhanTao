like(mary, food).
like(mary, wine).
like(john, wine).
like(john, mary).
like(john, X) :- like(mary, X).
like(john, X) :- like(X, wine).
like(john, X) :- like(X, X).