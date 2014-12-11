:-use_module(library(clpfd)).
:-use_module(library(lists)).

%Criar matriz
criaMulAux2(_,_,[]).
criaMulAux2(Size,Line,[X|Y]):- NewLine is Line-1, length(X,Size), criaMulAux2(Size,NewLine,Y).
criaMulAux([H|_],Line,[X|Y]):- NewLine is Line-1 , length(H,Size),length(X,Size), criaMulAux2(Size,NewLine,Y).     
criaMul(Custo,Mul):- length(Custo,Leng),length(Mul,Leng), criaMulAux(Custo,Leng,Mul).

checkFabric([],[]).
checkFabric([HF|TF],[HMul|TMul]) :-
sum(HMul,#=<,HF), checkFabric(TF,TMul)
.

checkClient([],[]). 
checkClient([HC|TC],[HMul|TMul]) :-
sum(HMul,#=,HC), checkClient(TC,TMul)
.

domainMul([],[]).
domainMul([HF|TF],[HMul|TMul]):-
domain(HMul, 0, HF),
domainMul(TF,TMul)
.

custo([],[],0).
custo([HC|TC],[HMul|TMul],Custo):-
        custo(TC,TMul,NewCusto),scalar_product(HC,HMul,#=,Value),Custo #= Value + NewCusto
        .

frig(Clientes,Fabricas,Custos,Mul1) :-
        criaMul(Custos,Mul1),
        domainMul(Fabricas,Mul1),
        checkFabric(Fabricas,Mul1),
        transpose(Mul1, Mul2),
        checkClient(Clientes,Mul2),
        append(Mul1,List),
        custo(Custos,Mul1,Custo),
        labeling([minimize(Custo)], List)
        .