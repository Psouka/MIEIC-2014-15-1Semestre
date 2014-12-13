:-use_module(library(clpfd)).
:-use_module(library(lists)).

%Criar matriz
criaMatrixAux([],_).
criaMatrixAux([H|T],Cols):-length(H,Cols),criaMatrixAux(T,Cols).     
criaMatrix(Fabricas,Clientes,Matrix):- length(Fabricas,Leng),length(Matrix,Leng),
        length(Clientes,Cols), criaMatrixAux(Matrix,Cols).

checkFabric([],[]).
checkFabric([HF|TF],[HMatrix|TMatrix]) :-
sum(HMatrix,#=<,HF), checkFabric(TF,TMatrix)
.

checkClient([],[]). 
checkClient([HC|TC],[HMatrix|TMatrix]) :-
sum(HMatrix,#=,HC), checkClient(TC,TMatrix)
.

domainMatrix([],[]).
domainMatrix([HF|TF],[HMatrix|TMatrix]):-
domain(HMatrix, 0, HF),
domainMatrix(TF,TMatrix)
.

custo([],[],0).
custo([HC|TC],[HMatrix|TMatrix],Custo):-
        custo(TC,TMatrix,NewCusto),scalar_product(HC,HMatrix,#=,Value),Custo #= Value + NewCusto
        .

frig(Clientes,Fabricas,Custos,Matrix1,Custo) :-
        criaMatrix(Fabricas,Clientes,Matrix1),
        domainMatrix(Fabricas,Matrix1),
        checkFabric(Fabricas,Matrix1),
        transpose(Matrix1, Matrix2),
        checkClient(Clientes,Matrix2),
        append(Matrix1,List),
        custo(Custos,Matrix1,Custo),
        labeling([minimize(Custo)], List)
        .

test(Matriz,Custo) :- frig([10,30,20],[20,20,20],[[10,20,15],[5,25,10],[5,5,30]],Matriz,Custo).