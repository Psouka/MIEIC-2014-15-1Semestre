:-use_module(library(random)).
board(        
[['A',' ',0,'|',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ','-',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 ['B',' ',0,' ',0,' ',0,' ',0,' ',0,' ','B'],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0]]
).


% para paredes: ' ' se nao tiver, '-' se tiver
% 0 para celulas neutras
% A para células com peão do jogador 1 sem parede por baixo
% B para células com peão do jogador 2 sem parede por baixo

%----------------------------------------------------------------------------
% check mov limit
checkLimit(Xinicial, Yinicial, Xfinal, Yfinal):-
        Xinicial > -1,
        Xinicial < 7,
        Xfinal > -1,
        Xfinal < 7,
        Yinicial > -1,
        Yinicial < 7,
        Yfinal > -1,
        Yfinal < 7.

checkLimit(X,Y):-
       X > -1,
        X < 13,
       Y> -1,
       Y< 13.



%----------------------------------------------------------------------------
%print lists
printline([]).
printline([H|T]):- write(H), printline(T).


%----------------------------------------------------------------------------
%printBoard
printBoard(B):- nl
                    ,write('    0     1     2     3     4     5     6  \n')
                    ,write('  _____ _____ _____ _____ _____ _____ _____'),nl,printBoardAux(B,0).

drawSymb(0):- write('     ').
drawSymb('|'):-write('|').
drawSymb(' '):-write(' ').
drawSymb(C) :- write('  '),write(C),write('  ').

printAuxUp('|'):-write('|').
printAuxUp(' '):-write(' ').
printAuxUp(_):- write('     ').

printUp([]):-write('|\n').
printUp([H|T]) :-printAuxUp(H), printUp(T).

printMid([]):-write('|\n').
printMid([H|T]):-drawSymb(H),printMid(T).

printAuxDown('|',' '):-write('|').
printAuxDown(' ',' '):-write(' ').
printAuxDown(_,' '):-write('     ').
printAuxDown(_,'-'):-write('_____').

printAuxDown('|'):-write('|').
printAuxDown(' '):-write(' ').
printAuxDown(_):-write('_____').


printDownAux([],[]):-write('|\n').
printDownAux([H|T],[X|Z]):- printAuxDown(H,X),printDownAux(T,Z).

printDown([H|T],[]):- H\= [],!,printAuxDown(H),printDown(T,[]).
printDown([],[]):-write('|\n').
printDown(Up,[H|_]):-printDownAux(Up,H).


printBoardAux([],_).

printBoardAux2([_|T],C):- C < 6,!,NewC is C+1,printBoardAux(T,NewC).
printBoardAux2(_,_).

printBoardAux([H|T],C):- C < 7,!, H \=[],!,write(' |'), printUp(H),write(C),write('|'),printMid(H),write(' |'),printDown(H,T),printBoardAux2(T,C).
printBoardAux(_,_).

%----------------------------------------------------------------------------
% Returns Element as the element of the list of lists at [Yindex][Xindex]     
elementAt([], _, -1):-!,fail.

elementAt([Elem|_], Elem, 0).

elementAt([_|T], Elem, X):-
        elementAt(T, Elem, NX),
        X is NX+1.
        
elementAt([], _, _, -1):-!, fail.

elementAt([H|_], Elem, X, 0):-
        elementAt(H, Elem, X).

%X = Col, Y = Line
elementAt([_|T], Elem, X, Y):-
          elementAt(T, Elem, X, NY),
          Y is NY+1.


%----------------------------------------------------------------------------
% Change player turn

changeActivePlayer(P, P1) :-
    P = 1,
    P1 is 2.
changeActivePlayer(P, P1) :-
    P = 2,
    P1 is 1.

%----------------------------------------------------------------------------
% Writes Turn
print_turn(1):-
        write('Blue turn: '),
        nl.
print_turn(2):-
        write('Red turn: '),
        nl.

%----------------------------------------------------------------------------
% Replaces the value of the element in the index Index to Elem 
replace([_|T], 0, Elem, [Elem|T]).

replace([H|T], Index, Elem, [H|R]):- 
        Index > -1, 
        NIndex is Index-1, 
        replace(T, NIndex, Elem, R), 
        !.

replace(List, _, _, List).


% Replaces the value of the element in (IndexX, IndexY) to Elem
replace([H|T], IndexX, 0, Elem, [X|T]):-
        replace(H, IndexX, Elem, X).
                                          
replace([H|T], IndexX, IndexY, Elem, [H|R]):-
        IndexY > -1, 
        NIndexY is IndexY-1, 
        replace(T, IndexX, NIndexY, Elem, R), 
        !.
        
replace(List, _, _,_, List).            


%---------------------------------------------------------------
%check move

%(   If1 -> Then1
%;   If2 -> Then2
%;   ...
%;   otherwise
%).

checkInLine(B,Xinicial, Yinicial, Xfinal, Yfinal,R):-
        (
           Xinicial > Xfinal, checkWall(B,Xinicial,Yinicial,-1,0),
           TestX is Xinicial -2,elementAt(B,Elem1,TestX,Yinicial),
           Elem1 == 0
        -> Nx is Xinicial - 2, checkInLine(B,Nx, Yinicial, Xfinal, Yfinal,R)
        ;  Xinicial < Xfinal, checkWall(B,Xinicial,Yinicial,1,0),
        TestX2 is Xinicial +2,elementAt(B,Elem2,TestX2,Yinicial),
           Elem2 == 0
        -> Nx is Xinicial + 2, checkInLine(B,Nx, Yinicial, Xfinal, Yfinal,R)
        ; Xinicial == Xfinal, Yinicial \= Yfinal
        -> checkInCol(B,Xinicial, Yinicial, Xfinal, Yfinal,R1), R is R1
        ; Xinicial == Xfinal, Yinicial == Yfinal -> R is 1
        ;R is 0
        )
        .

checkInLine(_,_,_,_,_,_).       
        
checkInCol(B,Xinicial, Yinicial, Xfinal, Yfinal,R):-
        (
           Yinicial > Yfinal, checkWall(B,Xinicial,Yinicial,0,-1),
        TestY1 is Yinicial -2,elementAt(B,Elem1,Xinicial,TestY1),
           Elem1 == 0
        -> Ny is Yinicial - 2, checkInCol(B,Xinicial, Ny, Xfinal, Yfinal,R)
        ;  Yinicial < Yfinal, checkWall(B,Xinicial,Yinicial,0,1),
        TestY2 is Yinicial +2,elementAt(B,Elem2,Xinicial,TestY2),
           Elem2 == 0
        -> Ny is Yinicial + 2, checkInCol(B,Xinicial, Ny, Xfinal, Yfinal,R)
        ; Xinicial \= Xfinal, Yinicial == Yfinal
        -> checkInLine(B,Xinicial, Yinicial, Xfinal, Yfinal,R1), R is R1
        ; Xinicial == Xfinal, Yinicial == Yfinal -> R is 1
        ;R is 0
        )
        .

checkInCol(_,_,_,_,_,_).  

checkCurve(B,Xinicial, Yinicial, Xfinal, Yfinal,R):-
    checkInLine(B,Xinicial, Yinicial, Xfinal, Yfinal,R3), checkInCol(B,Xinicial, Yinicial, Xfinal, Yfinal,R4), R is  R3 + R4
.
        
getWallPos(X,Y,Wall,NewX,NewY):- (
Wall == 1 -> NewX is X, NewY is Y-1,!
;   Wall == 2 -> NewX is X, NewY is Y+1,!
;   Wall == 3 -> NewX is X -1, NewY is Y,!
;   Wall == 4 -> NewX is X +1, NewY is Y,!
).

getWallPos(_,_,_,_,_).

writeWall(B,X,Y,NewB):- mod(Y,2) =:= 0,!,replace(B,X,Y,'|',NewB).
writeWall(B,X,Y,NewB):-replace(B,X,Y,'-',NewB).


checkMov(P,B,Xinicial,Yinicial,Xfinal,Yfinal,Wall,FinalB) :- elementAt(B, Elem, Xinicial, Yinicial), Elem == P,!,
        elementAt(B, Elem2, Xfinal, Yfinal), Elem2 == 0, !,
        checkCurve(B,Xinicial, Yinicial, Xfinal, Yfinal,R),!, R \= 0,!,
        getWallPos(Xfinal,Yfinal,Wall,Wx,Wy),
        elementAt(B,Elem3,Wx,Wy), Elem3 == ' ',!,
        replace(B,Xfinal,Yfinal,P,NewB),
        replace(NewB,Xinicial,Yinicial,0,NewB2),
        writeWall(NewB2,Wx,Wy,TestB),!,
        (
           mod(Wy,2) =:= 0 -> Wx1 is Wx+1,Wx2 is Wx -1,checkArea(NrA1,NrB1,Wx1,Wy,TestB,_),checkArea(NrA2,NrB2,Wx2,Wy,TestB,_)
        ,
                             (
                                NrA1 == 0, NrB1 > 1-> fail
                             ;  NrB1 == 0, NrA1 > 1-> fail
                             ;  NrA1 == 0, NrB1 == 0 -> fail
                             ;  NrA2 == 0, NrB2 > 1-> fail
                             ;  NrB2 == 0, NrA2 > 1-> fail
                             ;  NrA2 == 0, NrB2 == 0 -> fail
                             ;true
                                )
        ;
        Wy1 is Wy+1,Wy2 is Wy-1,
                              checkArea(NrA1,NrB1,Wx,Wy1,TestB,_),checkArea(NrA2,NrB2,Wx,Wy2,TestB,_),
         (
                                NrA1 == 0, NrB1 > 1-> fail
                             ;  NrB1 == 0, NrA1 > 1-> fail
                             ;  NrA1 == 0, NrB1 == 0 -> fail
                             ;  NrA2 == 0, NrB2 > 1-> fail
                             ;  NrB2 == 0, NrA2 > 1-> fail
                             ;  NrA2 == 0, NrB2 == 0 -> fail
                             ;true
                                )
           ),
        FinalB = TestB
        .
checkMov(_,B,_,_,_,_,_,B) :- fail.


%colocar um peao
checkMov(P,B,X,Y) :- elementAt(B, Elem, X, Y),Elem == 0, !,checkArea(NrA,NrB,X,Y,B,_),
        (
           P == 'A', NrA == 0, NrB == 1 -> fail
        ;P == 'B', NrA == 1, NrB == 0 -> fail
        ;true
           ).


%Check EndGame
checkEndGame(T,X,Y):-
        checkArea(NrA,NrB,X,Y,T,Visited),!,
        NrA + NrB <2,!,
        (
        Y \=12, X \= 12 -> Nx is X +2,checkEndGame(Visited,Nx,Y)
        ;X == 12,Y == 10 -> true
        ;   X == 12, Y <12 -> Ny is Y+2,Nx is 0, checkEndGame(Visited,Nx,Ny)
).

checkEndGame(_,_,_):-fail.

addNrP('A',NrA,NrB) :- NrA is 1, NrB is 0.
addNrP('B',NrA,NrB) :- NrA is 0, NrB is 1.
addNrP(_,NrA,NrB) :- NrA is 0, NrB is 0.

checkWall(B,X,Y,Xx,Yy) :- Nx is X + Xx, Ny is Y + Yy,  elementAt(B,Elem,Nx,Ny), Elem == ' '.


checkArea(NrA,NrB,X,Y,ToVisit,Visited):- elementAt(ToVisit,Elem,X,Y), Elem \= 'X',!,addNrP(Elem,NrAI,NrBI),
        replace(ToVisit,X,Y,'X',V0),
        ( checkWall(V0,X,Y,1,0)->
           Nx is X+2,
        checkArea(NrA1,NrB1,Nx,Y,V0,V1) ;
                  V1 = V0,
                  NrA1 is 0,
                  NrB1 is 0), 
        ( checkWall(V0,X,Y,0,1)->
           Ny is Y +2,
        checkArea(NrA2,NrB2,X,Ny,V1,V2) ;
                  V2 = V1,
                  NrA2 is 0,
                  NrB2 is 0),
         ( checkWall(V0,X,Y,-1,0)->
           Nx2 is X-2,
        checkArea(NrA3,NrB3,Nx2,Y,V2,V3) ;
                  V3 = V2,
                  NrA3 is 0,
                  NrB3 is 0),
        ( checkWall(V0,X,Y,0,-1)->
           Ny2 is Y -2,
        checkArea(NrA4,NrB4,X,Ny2,V3,V4) ;
                  V4 = V3,
                  NrA4 is 0,
                  NrB4 is 0),
        Visited = V4,
        NrA is NrAI + NrA1 + NrA2 + NrA3 + NrA4,
        NrB is NrBI + NrB1 + NrB2 + NrB3 + NrB4
        .

checkArea(0,0, _, _, T, T).


%getWinner
%------------------------------------------------------
getWinner(B,X,Y,NrA,NrB,Winner):-
        checkSizeArea(NrP,Symbol,X,Y,B,Visited),
        (
         Symbol == 'A' -> NrA2 is NrA +NrP, NrB2 is NrB
        ;Symbol == 'B' -> NrB2 is NrB +NrP, NrA2 is NrA
        ;NrA2 is NrA, NrB2 is NrB
           )
        ,
        (
        Y \=12, X \= 12 -> Nx is X +2,getWinner(Visited,Nx,Y,NrA2,NrB2,Winner)
        ;X == 12,Y == 10 -> (
         NrA >NrB -> Winner = 'A'
        ;NrB >NrA -> Winner = 'B'
        ;Winner = 'No one'
           )
        ;X == 12, Y <12 -> Ny is Y+2,Nx is 0,getWinner(Visited,Nx,Ny,NrA2,NrB,Winner)
)
         
        .

checkSizeArea(NrP,Symbol,X,Y,ToVisit,Visited):- elementAt(ToVisit,Elem,X,Y),
        (Elem \= 'X' ->
        ( Elem \= 0, Symbol = Elem
        ;true),
        replace(ToVisit,X,Y,'X',V0),
        ( checkWall(V0,X,Y,1,0)->
           Nx is X+2,
        checkSizeArea(NrP1,Symbol,Nx,Y,V0,V1) ;
                  V1 = V0,
                  NrP1 is 0), 
        ( checkWall(V0,X,Y,0,1)->
           Ny is Y +2,
        checkSizeArea(NrP2,Symbol,X,Ny,V1,V2) ;
                  V2 = V1,
                  NrP2 is 0),
         ( checkWall(V0,X,Y,-1,0)->
           Nx2 is X-2,
       checkSizeArea(NrP3,Symbol,Nx2,Y,V2,V3) ;
                  V3 = V2,
                  NrP3 is 0),
        ( checkWall(V0,X,Y,0,-1)->
           Ny2 is Y -2,
        checkSizeArea(NrP4,Symbol,X,Ny2,V3,V4) ;
                  V4 = V3,
                  NrP4 is 0),
        Visited = V4,
        NrP is 1 + NrP1 + NrP2 + NrP3 + NrP4
        ;NrP = 0, Visited = ToVisit
        )
        .

checkSizeArea(0,_,_,_, T, T).

%-----------------------------------------------------------------------
%input para a jogada
getMov(P,B,Xi,Yi,Xf,Yf,NewB) :- nl,
                        print('Coluna da peca a mover '),read(Xi),
                        print('Linha da peca a mover '),read(Yi),
                        print('Coluna da casa destino '),read(Xf),
                        print('Linha da casa destino '),read(Yf),
                        Xi2 is Xi *2,
                        Xf2 is Xf *2,
                        Yi2 is Yi *2,
                        Yf2 is Yf *2,
                        print('\nParede em:\n[1]Cima\n[2]Baixo\n[3]Lado Esquerdo\n[4]Lado Direito\n'), read(Wall)
                        ,checkMov(P,B,Xi2,Yi2,Xf2,Yf2,Wall,NewB), !
                         .


getMov(P,B,Xi,Yi,Xf,Yf,NewB) :- nl,write('Jogada nao permitida'),getMov(P,B,Xi,Yi,Xf,Yf,NewB).

getPiece(P,B,X,Y,NewB):-  print('\nColuna da peca: '),read(X),
                        print('\nLinha da peca: '),read(Y),
                        X2 is X *2, Y2 is Y*2,checkMov(P,B,X2,Y2), !, replace(B,X2,Y2,P,NewB).

getPiece(P,B,_,_,NewB) :- nl,write('Posicao nao permitida'),getPiece(P,B,_,_,NewB).

mov(P,B,1,NewB) :- getPiece(P,B,_,_,NewB).
mov(P,B,2,NewB) :- getMov(P,B,_,_,_,_,NewB).
mov(P,B,_,NewB) :- selectMov(P,B,_,NewB).
    

selectMov(P,B,R,NewB) :- print('[1]Colocar peao\n[2]Mover peao\n[3]Exit\n'),read(R),R \= 3,!, mov(P,B,R,NewB).
selectMov(_,_,3,_) :-write('\nBye!!').

%-----------------------------------------------------------------------
%into
getIntro(P) :- write('\n        Turno do jogador: '), write(P), nl.

%------------------------------------------------------------------------
%creat Random Start
randomPlayer(P) :- random(1, 3,NrP), NrP == 1,!, P = 'A'. 
randomPlayer(P) :- P = 'B'.

%-----------------------------------------------------------------------
%Start
play :-  board(B), printBoard(B).

% ---------------------------------MAIN MENU------------------------------------
fines:-
        mainMenu,
        read(X),
        mainMenuOption(X).

mainMenu:-
        nl,nl,
        write('----------------------------------------'),nl,
        write('Fines Game'),nl,nl,
        write('1- Play'), nl,
        write('2- Exit'), nl.

mainMenuOption(X):-
        (
                X = 1 -> play;
                X = 2 -> write('Goodbye!');
                (write('Wrong command!'),nl,fines)
        ).

not(true):-fail.
not(fail):-true.

play(B,P,R) :- 
        (
        checkEndGame(B,0,0) -> getWinner(B,0,0,0,0,Winner),write('The Winner is '),write(Winner), R is 3
        ; getIntro(P), printBoard(B), !,selectMov(P,B,R,NewB)),
        (
        R == 3 -> print('\nGame Over')
        ;P =='A' -> play(NewB,'B',_)
        ;P == 'B' -> play(NewB,'A',_)
        )
        .

start:-  board(B), randomPlayer(P),play(B,P,_).

test:- board(B), checkMov('B',B,12,6,12,0,2,NewB), printBoard(NewB).

testV :- A = 'B', A = 'B', write(A).
test7:- board(B),checkArea(NrA,NrB,12,12,B,Visited), write(NrA),write(NrB),printBoard(Visited).
test5:- board(B), checkSizeArea(NrP,Symbol,12,12,B,C), printBoard(C) ,write(NrP),write(Symbol).
test6 :- board(B),getWinner(B,0,0,0,0,Winner), write(Winner).
test4:- board(B), getMov('A',B,0,3,1,3,NewB), printBoard(NewB).
test3:- board(B), checkEndGame(B,0,0).
test2:- board(B),checkInCol(B,0,4,0,12,R),write(R).

draw:- board(B), printBoard(B).