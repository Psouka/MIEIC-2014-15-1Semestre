:-use_module(library(random)).
:-use_module(library(sockets)).
board(        
[[0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 ['A',' ',0,' ',0,' ',0,' ',0,' ',0,' ','B'],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0]]
).


% para paredes: ' ' se nao tiver, '-' se tive
% 0 para celulas neutras
% A para c�lulas com pe�o do jogador 1 sem parede por baixo
% B para c�lulas com pe�o do jogador 2 sem parede por baixo

%------------------------------------------------------------------------
%BotPlay

% random(+X, +Y, -List)
creatBotC(X,Y,[X,Y]).
creatBotP(X,Y,[[X,Y]]).

checkTopNear(B,X,Y,N):-Ny is Y - 1, elementAt(B,Elem,X,Ny),!,Elem \= 0,!,N is 1.
checkTopNear(_,_,_,0).

checkBotNear(B,X,Y,N):-Ny is Y + 1, elementAt(B,Elem,X,Ny),!,Elem \= 0,!,N is 1.
checkBotNear(_,_,_,0).
            
checkLeftNear(B,X,Y,N):-Nx is X - 1, elementAt(B,Elem,Nx,Y),!,Elem \= 0,!,N is 1.
checkLeftNear(_,_,_,0).

checkRightNear(B,X,Y,N):-Nx is X + 1, elementAt(B,Elem,Nx,Y),!,Elem \= 0,!,N is 1.
checkRightNear(_,_,_,0).

% checkNear(+B, +B,+Y)
checkNear(B,X,Y):-checkTopNear(B,X,Y,N1),checkBotNear(B,X,Y,N2),checkLeftNear(B,X,Y,N3),checkRightNear(B,X,Y,N4), NFinal is N1+N2+N3+N4, NFinal < 2,!.

% botPlay(+B,+BotP,+NrP,-NewB,-NewBotP,-NewNrP,+BotSymbol)
botPlay(B,BotP,NrP,NewB,NewBotP,NewNrP,BotSymbol):- random(1,6,Play), Play \= 1,!, botMov(B,BotP,NrP,NewB,NewBotP,NewNrP,BotSymbol).
botPlay(B,BotP,NrP,NewB,NewBotP,NewNrP,BotSymbol):- botCreat(B,BotP,NrP,NewB,NewBotP,NewNrP,5,BotSymbol),!.
botPlay(B,BotP,NrP,NewB,NewBotP,NewNrP,BotSymbol):-botMov(B,BotP,NrP,NewB,NewBotP,NewNrP,BotSymbol).

checkNotIsol(N):- N >1.

botMovAux(B,X,Y,NewX,NewY,NewB,Count,BotSymbol):- Count > 0, !,random(0,7,NewX2),NewX is NewX2*2,
        random(0,7,NewY2),NewY is NewY2 * 2,
        random(1,5,Wall),
        (checkNear(B,X,Y) ->checkMov(BotSymbol,B,X,Y,X,Y, Wall, NewB)
        ;checkMov(BotSymbol,B,X,Y, NewX, NewY, Wall, NewB)),!.

botMovAux(B,X,Y,NewX,NewY,NewB,Count,BotSymbol):- NewCount is Count-1, botMovAux(B,X,Y,NewX,NewY,NewB,NewCount,BotSymbol).

% botMov(+B,+BotP,+NrP,-NewB,-NewBotP,+NrP,+BotSymbol)
botMov(B,BotP,NrP,NewB,NewBotP,NrP,BotSymbol):- random(0,NrP,P),elementAt(BotP,Play,P),elementAt(Play,X,0),elementAt(Play,Y,1),!,
        checkArea(NrA,NrB,X,Y,B, _), !,NrPeoes is NrA + NrB,checkNotIsol(NrPeoes), !,botMovAux(B,X,Y,NewX,NewY,NewB,15,BotSymbol),creatBotC(NewX,NewY,NewP),
        replace(BotP,P, NewP,NewBotP).

botMov(B,BotP,NrP,NewB,NewBotP,NewNrP,BotSymbol):- botMov(B,BotP,NrP,NewB,NewBotP,NewNrP,BotSymbol).

% botCreat(+B,+BotP,+NrP,-NewB,-NewBotP,-NewNrP,+Count,+BotSymbol)
botCreat(B,BotP,NrP,NewB,NewBotP,NewNrP,Count,BotSymbol):-Count > 0,!,random(0,7,X),X2 is X *2,random(0,7,Y),Y2 is Y*2,
        checkMov(BotSymbol,B,X2,Y2),!, NewNrP is NrP +1,replace(B,X2,Y2,BotSymbol,NewB), creatBotP(X2,Y2,PList),append(BotP,PList,NewBotP).

botCreat(B,BotP,NrP,NewB,NewBotP,NewNrP,Count,BotSymbol):- Count > 0,!,Count2 is Count -1,botCreat(B,BotP,NrP,NewB,NewBotP,NewNrP,Count2,BotSymbol).

%---------------------------------------------------------------------------Oun-
%print lists
printline([]).
printline([H|T]):- write(H), printline(T).


%----------------------------------------------------------------------------
%printBoard
printline([]).
printline([H|T]):- write(H), printline(T).



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


printBoardAux2([_|T],C):- C < 6,!,NewC is C+1,printBoardAux(T,NewC).
printBoardAux2(_,_).

printBoardAux([H|T],C):- C < 7,!, H \=[],!,write(' |'), printUp(H),write(C),write('|'),printMid(H),write(' |'),printDown(H,T),printBoardAux2(T,C).
printBoardAux([],_).
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


getWallPos(X,Y,1,NewX,NewY):-NewX is X, NewY is Y-1.
getWallPos(X,Y,2,NewX,NewY):-NewX is X, NewY is Y+1.
getWallPos(X,Y,3,NewX,NewY):-NewX is X -1, NewY is Y.
getWallPos(X,Y,4,NewX,NewY):-NewX is X +1, NewY is Y.


getWallPos(_,_,_,_,_).

writeWall(B,X,Y,NewB):- mod(Y,2) =:= 0,!,replace(B,X,Y,'|',NewB).
writeWall(B,X,Y,NewB):-replace(B,X,Y,'-',NewB).


checkMovAux(0,1).
checkMovAux(1,0).
checkMovAux(A,B):- A > 0, B > 0.
checkMovAux(A1,B1,A2,B2) :- checkMovAux(A1,B1), checkMovAux(A2,B2).


nextPlayer('B',P):-P = 'A'.
nextPlayer('A',P):-P = 'B'.

checkMov(P,B,Xinicial,Yinicial,Xfinal,Yfinal,Wall,FinalB) :-elementAt(B, Elem, Xinicial, Yinicial), Elem == P,!,
        checkArea(Nr_A,Nr_B, Xinicial, Yinicial,B, _),!,nextPlayer(P,Ptest),checkMovAux(Ptest,Nr_A,Nr_B),!,
        elementAt(B, Elem2, Xfinal, Yfinal), Elem2 == 0, !,
        checkCurve(B,Xinicial, Yinicial, Xfinal, Yfinal,R),!, R \= 0,!,
        getWallPos(Xfinal,Yfinal,Wall,Wx,Wy),!,
        elementAt(B,Elem3,Wx,Wy), Elem3 == ' ',!,
        replace(B,Xfinal,Yfinal,P,NewB),
        replace(NewB,Xinicial,Yinicial,0,NewB2),
        writeWall(NewB2,Wx,Wy,TestB),!,
        (
           mod(Wy,2) =:= 0 -> Wx1 is Wx+1,Wx2 is Wx -1,checkArea(NrA1,NrB1,Wx1,Wy,TestB,_),checkArea(NrA2,NrB2,Wx2,Wy,TestB,_)
        ,checkMovAux(NrA1,NrB1,NrA2,NrB2)
        ;
        Wy1 is Wy+1,Wy2 is Wy-1,
                              checkArea(NrA1,NrB1,Wx,Wy1,TestB,_),checkArea(NrA2,NrB2,Wx,Wy2,TestB,_),!,
         checkMovAux(NrA1,NrB1,NrA2,NrB2)
           ),
        FinalB = TestB
        .
checkMov(_,B,_,_,_,_,_,B) :- fail.


%colocar um peao


checkMovAux('A',0,NrB):- NrB >1.
checkMovAux('A',NrA,0):- NrA >1.
checkMovAux('A',NrA,NrB):- NrA == 0, NrB \=1.
checkMovAux('A',NrA,NrB):- NrA \= 0, NrB ==1.
checkMovAux('A',NrA,NrB):-NrA \= 0, NrB \= 1.

checkMovAux('B',0,NrB):- NrB >1.
checkMovAux('B',NrA,0):- NrA >1.
checkMovAux('B',NrA,NrB):- NrA == 1, NrB \=0.
checkMovAux('B',NrA,NrB):- NrA \= 1, NrB ==0.
checkMovAux('B',NrA,NrB):-NrA \= 1, NrB \= 0.

checkMov('A',B,X,Y) :- elementAt(B, Elem, X, Y),Elem == 0, !,checkArea(NrA,NrB,X,Y,B,_),!,
        checkMovAux('A',NrA,NrB),!.
        
checkMov('B',B,X,Y) :- elementAt(B, Elem, X, Y),Elem == 0, !,checkArea(NrA,NrB,X,Y,B,_),!,
       checkMovAux('B',NrA,NrB).



%Check EndGame
checkEndGame(T,12,10):- checkArea(NrA,NrB,12,10,T,_),!,NrA + NrB <2,!.

checkEndGame(T,12,Y):- Y < 12, !, checkArea(NrA,NrB,12,Y,T,Visited),!,NrA + NrB <2,!,Ny is Y+2,Nx is 0, checkEndGame(Visited,Nx,Ny).

checkEndGame(T,X,Y):-
        checkArea(NrA,NrB,X,Y,T,Visited),!,
        NrA + NrB <2,!, Nx is X +2,checkEndGame(Visited,Nx,Y).

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

getWinnerAux(NrA,NrB,Winner):-NrA>NrB,!,Winner = 'A'.
getWinnerAux(NrA,NrB,Winner):-NrA<NrB,!,Winner = 'B'.
getWinnerAux(_,_,Winner):- Winner = 'No one'.

getWinnerAux2('A',NrA,NrB,NrP,NrA2,NrB2):-NrA2 is NrA +NrP, NrB2 is NrB.
getWinnerAux2('B',NrA,NrB,NrP,NrA2,NrB2):-NrB2 is NrB +NrP, NrA2 is NrA.
getWinnerAux2(_,NrA,NrB,_,NrA2,NrB2):-NrA2 is NrA, NrB2 is NrB.

getWinner(B,12,10,NrA,NrB,Winner):-  checkSizeArea(NrP,Symbol,12,10,B,_),
        getWinnerAux2(Symbol,NrA,NrB,NrP,NrA2,NrB2),getWinnerAux(NrA2,NrB2,Winner).

getWinner(B,12,Y,NrA,NrB,Winner):-  Y < 12,!,checkSizeArea(NrP,Symbol,12,Y,B,Visited),
        getWinnerAux2(Symbol,NrA,NrB,NrP,NrA2,NrB2),Ny is Y+2,Nx is 0,getWinner(Visited,Nx,Ny,NrA2,NrB2,Winner).

getWinner(B,X,Y,NrA,NrB,Winner):-
        checkSizeArea(NrP,Symbol,X,Y,B,Visited),
        getWinnerAux2(Symbol,NrA,NrB,NrP,NrA2,NrB2)
        ,Nx is X +2,getWinner(Visited,Nx,Y,NrA2,NrB2,Winner)
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
                        print('Linha da peca: '),read(Y),
                        X2 is X *2, Y2 is Y*2,checkMov(P,B,X2,Y2), !, replace(B,X2,Y2,P,NewB).

getPiece(P,B,_,_,NewB) :- nl,write('Posicao nao permitida'),getPiece(P,B,_,_,NewB).

mov(P,B,1,NewB) :- getPiece(P,B,_,_,NewB).
mov(P,B,2,NewB) :- getMov(P,B,_,_,_,_,NewB).
mov(P,B,_,NewB) :- selectMov(P,B,_,NewB).
    

selectMov(P,B,R,NewB) :- print('[1]Colocar peao\n[2]Mover peao\n[3]Exit\n'),read(R),R \= 3,!, mov(P,B,R,NewB).
selectMov(_,_,3,_) :-write('\nBye!!').

%-----------------------------------------------------------------------
%into
getIntro(P) :- write('\n             Turno do jogador: '), write(P), nl.
getIntroBot(P) :-write('\n              Turno do Bot: '), write(P),nl.
%------------------------------------------------------------------------
%creat Random Start
randomPlayer(P) :- random(1, 3,NrP), NrP == 1,!, P = 'A'. 
randomPlayer(P) :- P = 'B'.

% ---------------------------------MAIN MENU------------------------------------
fines:-
        mainMenu,
        read(X),
        gameModeMenu,
        read(Y),
        mainMenuOption(X, Y).

mainMenu:-
        nl,nl,
        write('----------------------------------------'),nl,
        write('Fines Game'),nl,nl,
        write('1- Play'), nl,
        write('2- Exit'), nl.

gameModeMenu:- 
        nl,nl,
        write('Game Mode: '), nl, nl,
        write('1 - Player vs Player'), nl,
        write('2 - Bot vs Player'), nl,
        write('3 - Bot vs Bot'), nl.

difficultyMenu:-
        nl,nl,
        write('Difficulty: '), nl, nl,
        write('1 - Easy'), nl,
        write('2 - Hard'), nl.

mainMenuOption(1, 1):- playerVsPlayer.

mainMenuOption(1, 2):- difficultyMenu, read(Z), mainMenuBot(Z).

mainMenuBot(Z):- Z = true.


play(B,'A',R) :- R \= 3,!,
        (
        checkEndGame(B,0,0) -> getWinner(B,0,0,0,0,Winner),write('The Winner is '),write(Winner), NewR is 3
        ; getIntro('A'), printBoard(B), !,selectMov('A',B,NewR,NewB)),
        play(NewB,'B',NewR)
        .

play(B,'B',R) :-R \= 3,!,
        (
        checkEndGame(B,0,0) -> getWinner(B,0,0,0,0,Winner),write('The Winner is '),write(Winner), NewR is 3
        ; getIntro('B'), printBoard(B), !,selectMov('B',B,NewR,NewB)),
        play(NewB,'A',NewR)
        .

play(_,_,3):- print('\nGame Over').

playerVsPlayer:-  board(B), randomPlayer(P),play(B,P,1).


playVsBot(B,'A',BotPs,NrPBots,R) :- R \= 3,!,
        (
        checkEndGame(B,0,0) -> getWinner(B,0,0,0,0,Winner),write('The Winner is '),write(Winner), NewR is 3
        ; getIntroBot('A'), getIntro('A'), printBoard(B), !,selectMov('A',B,NewR,NewB)),
        playVsBot(NewB,'B',BotPs,NrPBots,NewR)
        .

playVsBot(B,'B',BotPs,NrPBots,R) :-R \= 3,!,
        (
        checkEndGame(B,0,0) -> getWinner(B,0,0,0,0,Winner),write('The Winner is '),write(Winner), NewR is 3
        ; getIntroBot('B'), botPlay(B,BotPs,NrPBots,NewB,NewBotPs,NewNrPBots,'B'),NewR is 4),
        playVsBot(NewB,'A',NewBotPs,NewNrPBots,NewR)
        .

playVsBot(_,_,_,_,3):- print('\nGame Over').


playerVsBot:- board(B),creatBotP(12,6,BotPs), playVsBot(B,'A',BotPs,1,1).



botAvsBotB(B,'A',BotPs1,NrBotsP1,BotPs2,NrBotsP2,R) :- R \= 3,!,
        (
        checkEndGame(B,0,0) -> getWinner(B,0,0,0,0,Winner),write('The Winner is '),write(Winner), NewR is 3
        ; botPlay(B,BotPs1,NrBotsP1,NewB,NewBotPs1,NewNrBotsP1,'A'),NewR is 4),printBoard(NewB),
        botAvsBotB(NewB,'B',NewBotPs1,NewNrBotsP1,BotPs2,NrBotsP2,NewR)
        .

botAvsBotB(B,'B',BotPs1,NrBotsP1,BotPs2,NrBotsP2,R) :-R \= 3,!,
        (
        checkEndGame(B,0,0) -> getWinner(B,0,0,0,0,Winner),write('The Winner is '),write(Winner), NewR is 3
        ; botPlay(B,BotPs2,NrBotsP2,NewB,NewBotPs2,NewNrPBots2,'B'),NewR is 4),printBoard(NewB),
        botAvsBotB(NewB,'A',BotPs1,NrBotsP1,NewBotPs2,NewNrPBots2,NewR)
        .

botAvsBotB(_,_,_,_,_,_,3):-print('\nGame Over').

botVsBot:- board(B),creatBotP(12,6,BotPs2),creatBotP(0,6,BotPs1),randomPlayer(P),botAvsBotB(B,P,BotPs1,1,BotPs2,1,0).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%                 Sockets                   %%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

port(60070).

% launch me in sockets mode
server:-
  port(Port),
  socket_server_open(Port,Socket),
  socket_server_accept(Socket, _Client, Stream, [type(text)]),
  write('Accepted connection'), nl,
  server_loop(Stream),
  socket_server_close(Socket).

% wait for commands
server_loop(Stream) :-
  repeat,
  read(Stream, ClientMsg),
  write('Received: '), write(ClientMsg), nl,
  parse_input(ClientMsg, MyReply),
  format(Stream, '~q.~n', [MyReply]),
  write('Wrote: '), write(MyReply), nl,
  flush_output(Stream),
  (ClientMsg == quit; ClientMsg == end_of_file), !.

parse_input([addPiece, Board, Player, Column, Row], MyReply):-
 checkMov(Player,Board,Column,Row), !, MyReply is 1.

parse_input([addPiece, Board, Player, Column, Row], 0).


parse_input([movePiece, Board, Player, Xinicial,Yinicial,Xfinal,Yfinal,Wall],MyReply):-
checkMov(Player,Board,Xinicial,Yinicial,Xfinal,Yfinal,Wall,FinalB), !, MyReply is 1.

parse_input([movePiece, Board, Player, Xinicial,Yinicial,Xfinal,Yfinal,Wall],0).


parse_input([gameOver, Board], MyReply):-
  checkEndGame(Board,0,0),!, getWinner(Board,0,0,0,0,MyReply),!.

parse_input([gameOver, Board], 0).

parse_innput([playBoy,Board,NrPBots,NrP],MyReply):-
botPlay(Board,NrPBots,NrP,MyReply,_,_,'B'), !.

 parse_innput([playBoy,Board,NrPBots,NrP],Board).

parse_input(quit, ok-bye):- !.


test :- board(B),botPlay(B,1,2,MyReply,T,C,'B').