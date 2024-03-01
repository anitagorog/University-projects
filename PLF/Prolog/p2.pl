% 6.

% a. Determine the product of a number represented as digits in a list to a given digit.
% Eg.: [1 9 3 5 9 9] * 2 => [3 8 7 1 9 8]

% b. For a heterogeneous list, formed from integer numbers and list of numbers,
% write a predicate to replace every sublist with the position of the
% maximum element from that sublist. [1, [2, 3], [4, 1, 4], 3, 6, [7,
% 10, 1, 3, 9], 5, [1, 1, 1], 7] => [1, [2], [1, 3], 3, 6, [2], 5, [1,
% 2, 3], 7]


% a


% my_append(l1...ln, nr_to_append) =
%	[nr_to_append], n = 0
%	l1 + my_append(l2...ln), otherwise

% my_append(List:list, Nr_to_append:number, Result:list)
% (i, i, o)

my_append([], Nr_to_append, [Nr_to_append]).
my_append([Head | Tail], Nr_to_append, [Head | Result]) :-
    my_append(Tail, Nr_to_append, Result).


% inverse_list(l1...ln) =
%	[], n = 0
%	my_append(inverse_list(l2...ln), l1), otherwise

% inverse_list(List:list, Result:list)
% (i, o)

inverse_list([], []).
inverse_list([Head | Tail], Result) :-
    inverse_list(Tail, Result1),
    my_append(Result1, Head, Result).


% product(l1...ln, multiplier, remainder) =
%	[remainder], n = 0
%	((l1*multiplier + remainder) % 10)  +
%         product(l2...ln, multiplier, ((l1*multiplier+remainder)/10)),
%                  , otherwise

% product(List:list, Multiplier:number, Remainder:number, Result:list)
% (i, i, i, o)

product([], _, 0, []).
product([], _, Remainder, [Remainder]) :- Remainder =\= 0.
product([Head | Tail], Multiplier, Remainder, [Head_result | Result]) :-
    Head_result is (Head * Multiplier + Remainder) mod 10,
    New_remainder is (Head * Multiplier + Remainder - Head_result) / 10,
    product(Tail, Multiplier, New_remainder, Result).


% product_list(List:list, Multiplier:number, Result:list)
% (i, i, o)

product_list(List, Multiplier, Result) :-
    inverse_list(List, List_inverse),
    product(List_inverse, Multiplier, 0, Result_inverse),
    inverse_list(Result_inverse, Result).



% b


% max_number(a, b) =
%	a, a >= b
%	b, a < b

% max_number(A:number, B:number, Bigger_nr:number)
% (i, i, o)

max_number(A, B, A) :- A >= B.
max_number(A, B, B) :- A < B.


% max_in_list(l1...ln) =
%	l1, n = 1
%	max_number(l1, max_in_list(l2...ln))

% max_in_list(List:list, Result:number)
% (i, o)

max_in_list([Head], Head).
max_in_list([Head | Tail], Result) :-
    max_in_list(Tail, Current_max),
    max_number(Head, Current_max, Result).


% replace_position(l1...ln, max_nr, position) =
%	[], n = 0
%       position + replace_position(l2...ln, max_nr, position + 1),
%         , l1=max_nr
%       replace_position(l2...ln, max_nr, position + 1), l1 != max_nr

% replace_position(List:list, Max_nr:number, Position:number,Result:list)
% (i, i, i, o)

replace_position([], _, _, []).
replace_position([Head | Tail], Max_nr, Position, [Position | Result]) :-
    Head =:= Max_nr, !,
    Curr_pos is Position + 1,
    replace_position(Tail, Max_nr, Curr_pos, Result).
replace_position([Head | Tail], Max_nr, Position, Result) :-
    Head =\= Max_nr,
    Curr_pos is Position + 1,
    replace_position(Tail, Max_nr, Curr_pos, Result).


% heter_list(l1...ln) =
%	[], n = 0
%	replace_position(l1, max_in_list(l1), 1) + heter_list(l2...ln),
%         , is_list(l1) = True
%	l1 + heter_list(l2...ln), otherwise

% heter_list(List:list, Result:list)
% (i, o)

heter_list([], []).
heter_list([Head | Tail], [Head_result | Result]) :- is_list(Head), !,
    max_in_list(Head, Max_nr),
    replace_position(Head, Max_nr, 1, Head_result),
    heter_list(Tail, Result).
heter_list([Head | Tail], [Head | Result]) :-
    heter_list(Tail, Result).


















