:-use_module(library(clpfd)).
:-use_module(library(lists)).

%criaMatrix(-Fabricas,-Clientes,+Matrix)
criaMatrixAux([],_).
criaMatrixAux([H|T],Cols):-length(H,Cols),criaMatrixAux(T,Cols).     
criaMatrix(Fabricas,Clientes,Matrix):- length(Fabricas,Leng),length(Matrix,Leng),
        length(Clientes,Cols), criaMatrixAux(Matrix,Cols).

%checkFabric(-Fabricas,-Matriz)
checkFabric([],[]).
checkFabric([HF|TF],[HMatrix|TMatrix]) :-
sum(HMatrix,#=<,HF), checkFabric(TF,TMatrix)
.

%checkClient(-Clientes,-Matriz) 
checkClient([],[]).
checkClient([HC|TC],[HMatrix|TMatrix]) :-
sum(HMatrix,#=,HC), checkClient(TC,TMatrix)
.

%domainMatrix(-Fabricas,-Matriz)
domainMatrix([],[]).
domainMatrix([HF|TF],[HMatrix|TMatrix]):-
domain(HMatrix, 0, HF),
domainMatrix(TF,TMatrix)
.

%custo(-Clientes,-Matriz,+Custo).
custo([],[],0).
custo([HC|TC],[HMatrix|TMatrix],Custo):-
        custo(TC,TMatrix,NewCusto),scalar_product(HC,HMatrix,#=,Value),Custo #= Value + NewCusto
        .
% frig(-Clientes,-Fabricas,-Custos,+Matriz,+Custo)
frig(Clientes,Fabricas,Custos,Matrix1,Custo) :-
        criaMatrix(Fabricas,Clientes,Matrix1),
        domainMatrix(Fabricas,Matrix1),
        checkFabric(Fabricas,Matrix1),
        transpose(Matrix1, Matrix2),
        checkClient(Clientes,Matrix2),
        append(Matrix1,List),
        custo(Custos,Matrix1,Custo),
        reset_stats,
        labeling([minimize(Custo)], List),
        print_stats,
        fd_statistics
        .
reset_stats :- statistics(walltime,_).  
print_stats :- statistics(walltime,[_,T]),
        TS is ((T//10)*10)/1000,
        nl, write('Time: '), write(TS), write('s'), nl
        .

test(Matriz,Custo) :- frig([10,30,20],[20,20,20],[[10,20,15],[5,25,10],[5,5,30]],Matriz,Custo).