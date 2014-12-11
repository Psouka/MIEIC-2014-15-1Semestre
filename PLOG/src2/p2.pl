:-use_module(library(clpfd)).

puzzle([S,E,N,D,M,O,R,Y]) :-
domain([S,E,N,D,M,O,R,Y], 0, 9), % passo 1
S#>0, M#>0,
all_different([S,E,N,D,M,O,R,Y]), % passo 2
sum(S,E,N,D,M,O,R,Y),
labeling([], [S,E,N,D,M,O,R,Y]). % passo 3
sum(S, E, N, D, M, O, R, Y) :-
1000*S + 100*E + 10*N + D + 1000*M + 100*O + 10*R + E
#= 10000*M + 1000*O + 100*N + 10*E + Y.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

exactly(_,[],0).
exactly(X,[Y|L],N) :-
X #= Y #<=> B, % B = 1 se a condicao se verificar
N #= M+B,
exactly(X,L,M).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

sumTest:- domain([X,Y],1,10), sum([X,Y],#<,10).

minExample :- domain([A,B],1,10), C in 5..15, minimum(C,[A,B]).


%#\ :Q
%– verdadeira se a restrição Q for falsa
%:P #/\ :Q
%– verdadeira se as restrições P e Q são ambas verdadeiras
%:P #\ :Q
%– verdadeira se exactamente uma das restrições P e Q é verdadeira
%:P #\/ :Q
%– verdadeira se pelo menos uma das restrições P e Q é verdadeira
%:P #=> :Q
%:Q #<= :P
%– verdadeira se a restrição Q é verdadeira ou se a restrição P é falsa
%:P #<=> :Q
%– verdadeira se P e Q são ambas verdadeiras ou ambas falsas


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 elementTest :- element(X,[10,20,30],Y), labeling([],[Y]).  % vai buscar a posiçao X


schedule(Ss, End) :-
Ss = [S1,S2,S3,S4,S5,S6,S7],
Es = [E1,E2,E3,E4,E5,E6,E7],
Tasks = [
task(S1, 1, E1, 2, 1),
task(S2, 1, E2, 9, 2),
task(S3, 1, E3, 3, 3),
task(S4, 1, E4, 7, 4),
task(S5, 1, E5, 10, 5),
task(S6, 1, E6, 1, 6),
task(S7, 1, E7, 11, 7)
],
domain(Ss, 1, 30),
domain(Es, 1, 50),
domain([End], 1, 50),
maximum(End, Es),
cumulative(Tasks, [limit(13)]),
append(Ss, [End], Vars),
labeling([minimize(End)], Vars).







