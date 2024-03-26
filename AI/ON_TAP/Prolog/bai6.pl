  gt(0,1):-!.
  gt(N,Kq):-N1=N-1,gt(N1,Kq1),Kq=N*Kq1.
  tohop(N,K,C):-gt(N,Ngt),gt(K,Kgt),
  Nk=N-K,gt(Nk,Nkgt),C=Ngt/(Kgt*Nkgt).