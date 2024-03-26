food(ga).
food(tao).
food(Y) :- alive(X), eat(X, Y).
eat(bill,dauphong).
eat(john, Y) :- food(Y).
eat(sue, Y) :- eat(bill, Y).
alive(bill).