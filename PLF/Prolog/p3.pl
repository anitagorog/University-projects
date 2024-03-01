% 6.

% Generate the list of all arrangements of K elements of a given list.
% Eg: [2, 3, 4] K=2 => [[2,3], [3,2], [2,4], [4,2], [3,4], [4,3]] (not necessary
% in this order)


% insert(l1...ln, Element) =
%	[Element], n = 0
%	Element + l1...ln, n >= 1
%	l1 + insert(l2...ln, Element), otherwise

% insert(List:list, Element:number, Result:list)
% (i, i, o)

insert([], Element, [Element]).
insert([Head | Tail], Element, [Element,Head | Tail]).
insert([Head | Tail], Element, [Head | Result]) :- % for perm to be able to put in
                                                   % every position
   insert(Tail, Element, Result).


% permutation(l1...ln) =
%	[], n = 0
%	insert(permutation(l2...ln), l1), otherwise

% permutation(List:list, Result:list)
% (i, o)

permutation([], []).
permutation([Head | Tail], Result) :-
    permutation(Tail, PartialResult),     % call permut untill []
    insert(PartialResult, Head, Result).  % insert elems untill a perm


% combination(l1...ln, k) =
%	[], k = 0
%	l1 + combination(l2...ln, k - 1), k > 0
%	combination(l2...ln, k), k > 0

% combination(List:list, K:number, Result:list)
% (i, i, o)

combination(_, 0, []).
combination([Head | Tail], K, [Head | Result]) :- % when we put head in combinat.
    K > 0,
    NewK is K - 1,
    combination(Tail, NewK, Result).
combination([_|Tail], K, Result) :- % when do not (combination shorter than List)
    K > 0,
    combination(Tail, K, Result).

% arrangement(List:list, K:number, Result:list)
% (i, i, o)

arrangement(List, K, Result) :-
    combination(List, K, CombinationResult), % first the combination
    permutation(CombinationResult, Result).  % then we permute it -> arrangements



% allSolutions(List:list, Number:number, Result:list)
% (i, i, o)

allSolutions(List, Number, Result) :-
   findall(PartialResult, arrangement(List, Number, PartialResult), Result).

% findall - puts PartialResult in Result for all arrangement(..)



lengthof([],0).
lengthof([_|T], R) :-
   lengthof(T, R1),
   R is R1+1.

myappend([], [], []).
myappend([], [H|T], [H|R]) :-
   myappend([], T, R).
myappend([H|T],L,[H|R]) :-
   myappend(T, L, R).

allSolutions2(List, Number, R) :-
    lengthof(List, Length),
    Number =< Length,
    findall(PartialResult, arrangement(List, Number, PartialResult), Result),
    Number2 is Number+1,
    allSolutions2(List, Number2, PrevResult),
    %append(Result, PrevResult, R).
    myappend(Result, PrevResult, R).
allSolutions2(List,Number,Result) :-
   lengthof(List, Length),
   Number =:= Length,
   findall(PartialResult, arrangement(List, Number, PartialResult), Result).














