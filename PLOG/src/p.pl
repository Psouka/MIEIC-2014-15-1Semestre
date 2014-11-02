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


% para paredes: ' ' se nao tiver, '-' se tiver
% 0 para celulas neutras
% A para células com peão do jogador 1 sem parede por baixo
% B para células com peão do jogador 2 sem parede por baixo

%input para a jogada     
getMov(Xi,Yi,Xf,Yf) :-
                        print('\nCoordenada X da peca a mover : '),read(Yi),
                        print('\nCoordenada Y da peca a mover : '),read(Xi),
                        print('\nCoordenada X da casa destino : '),read(Yf),
                        print('\nCoordenada Y da casa destino : '),read(Xf).


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

%----------------------------------------------------------------------------
%print lists
printline([]).
printline([H|T]):- write(H), printline(T).


%----------------------------------------------------------------------------

%print board
drawWalls([H|T],C):- write('  |'), printline(H), write('|'), nl, draw(T,C).
drawWalls([],C).
draw([H|T],C):-  write(C), NewC is C+1,write('.|'), printline(H), write('|'), nl,drawWalls(T,NewC).
draw([],C).
drawBoard(B):- printline(['   ',0,' ',1,' ',2,' ',3,' ',4,' ',5, ' ',6]), nl,
        printline(['   ','-','-','-','-','-','-','-','-','-','-','-', '-','-']),
        nl, draw(B,0),
        printline(['   ','-','-','-','-','-','-','-','-','-','-','-', '-','-']).


%----------------------------------------------------------------------------
% Index is invalid, (index > size)
elementAt([],_,-1).

elementAt([Element|_], 0, Element).
 
 
% Returns Element as the element of the list in index Index
elementAt([_|T], Index, Element):-
        NIndex = Index-1,
        elementAt(T, NIndex, Element). 

% Returns Element as the element of the list of lists at [Yindex][Xindex]     
elementAt(Board, Xindex, Yindex, Element):-
        elementAt(Board, Yindex, Linha),
        elementAt(Linha, Xindex, Element).

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



%Start
play :-  board(B), drawBoard(B).
